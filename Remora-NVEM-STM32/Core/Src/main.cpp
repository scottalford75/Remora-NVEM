/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <inttypes.h>
#include <cstring>

#include "configuration.h"
#include "remora.h"

// Flash storage
#include "flash_if.h"

// Ethernet
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "tftpserver.h"

// libraries
#include <sys/errno.h>
#include "lib/ArduinoJson6/ArduinoJson.h"

// drivers
#include "drivers/pin/pin.h"

// interrupts
#include "interrupt/irqHandlers.h"
#include "interrupt/interrupt.h"

// threads
#include "thread/pruThread.h"
#include "thread/createThreads.h"

// modules
#include "modules/module.h"
#include "modules/blink/blink.h"
#include "modules/comms/RemoraComms.h"
#include "modules/debug/debug.h"
#include "modules/pwm/spindlePWM.h"
#include "modules/pwm/softPWM.h"
#include "modules/stepgen/stepgen.h"
#include "modules/digitalPin/digitalPin.h"
#include "modules/nvmpg/nvmpg.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
UART_HandleTypeDef huart2;
IWDG_HandleTypeDef hiwdg;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_USART2_UART_Init(void);

void udpServer_init(void);
void udp_data_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
void udp_mpg_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// re-target printf to UART2 by redeclaring week function in syscalls.c
extern "C" {
	int __io_putchar(int ch)
	{
	  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	  return ch;
	}
}

// network interface
extern struct netif gnetif;

// state machine
enum State {
    ST_SETUP = 0,
    ST_START,
    ST_IDLE,
    ST_RUNNING,
    ST_STOP,
    ST_RESET,
    ST_WDRESET
};

uint8_t resetCnt;
uint32_t base_freq = PRU_BASEFREQ;
uint32_t servo_freq = PRU_SERVOFREQ;

// boolean
volatile bool PRUreset;
bool configError = false;
bool threadsRunning = false;

// pointers to objects with global scope
pruThread* servoThread;
pruThread* baseThread;
RemoraComms* comms;
Module* MPG;

// unions for RX, TX and MPG data
rxData_t rxBuffer;				// temporary RX buffer
volatile rxData_t rxData;
volatile txData_t txData;
mpgData_t mpgData;

// pointers to data
volatile rxData_t*  ptrRxData = &rxData;
volatile txData_t*  ptrTxData = &txData;
volatile int32_t* ptrTxHeader;
volatile bool*    ptrPRUreset;
volatile int32_t* ptrJointFreqCmd[JOINTS];
volatile int32_t* ptrJointFeedback[JOINTS];
volatile uint8_t* ptrJointEnable;
volatile float*   ptrSetPoint[VARIABLES];
volatile float*   ptrProcessVariable[VARIABLES];
volatile uint32_t* ptrInputs;
volatile uint32_t* ptrOutputs;
volatile uint16_t* ptrNVMPGInputs;
volatile mpgData_t* ptrMpgData = &mpgData;


// Json config file stuff

const char defaultConfig[] = DEFAULT_CONFIG;
//const char defaultConfig[] = FULL_CONFIG;

// 512 bytes of metadata in front of actual JSON file
typedef struct
{
  uint32_t crc32;   		// crc32 of JSON
  uint32_t length;			// length in words for CRC calculation
  uint32_t jsonLength;  	// length in of JSON config in bytes
  uint8_t padding[500];
} metadata_t;
#define METADATA_LEN    512

volatile bool newJson;
uint32_t crc32;
FILE *jsonFile;
string strJson;
DynamicJsonDocument doc(JSON_BUFF_SIZE);
JsonObject thread;
JsonObject module;



int8_t checkJson()
{
	metadata_t* meta = (metadata_t*)JSON_UPLOAD_ADDRESS;
	uint32_t* json = (uint32_t*)(JSON_UPLOAD_ADDRESS + METADATA_LEN);

	// Check length is reasonable
	if (meta->length > (USER_FLASH_END_ADDRESS - JSON_UPLOAD_ADDRESS))
	{
		newJson = false;
		printf("JSON Config length incorrect\n");
		return -1;
	}

	// Enable & Reset CRC
	RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
	CRC->CR = 1;

	// Compute CRC
	// Note: __RBIT is used so that CRC will match standard calculation
	for (uint32_t i = 0; i < meta->length; i++) CRC->DR = __RBIT(*(json+i));
	crc32 = __RBIT(CRC->DR) ^ 0xFFFFFFFF;

	printf("Length (words) = %d\n", meta->length);
	printf("JSON length (bytes) = %d\n", meta->jsonLength);
	printf("crc32 = %x\n", crc32);

	// Disable CRC
	RCC->AHB1ENR &= ~RCC_AHB1ENR_CRCEN;

	// Check CRC
	if (crc32 != meta->crc32)
	{
		newJson = false;
		printf("JSON Config file CRC incorrect\n");
		return -1;
	}

	// JSON is OK, don't check it again
	newJson = false;
	printf("JSON Config file received Ok\n");
	return 1;
}


void moveJson()
{
	uint32_t i = 0;
	metadata_t* meta = (metadata_t*)JSON_UPLOAD_ADDRESS;

	uint16_t jsonLength = meta->jsonLength;

	// erase the old JSON config file
	FLASH_If_Erase(JSON_STORAGE_ADDRESS);

	HAL_StatusTypeDef status;

	// store the length of the file in the 0th byte
	status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, JSON_STORAGE_ADDRESS, jsonLength);

    for (i = 0; i < jsonLength; i++)
    {
        if (status == HAL_OK)
        {
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, (JSON_STORAGE_ADDRESS + 4 + i), *((uint8_t*)(JSON_UPLOAD_ADDRESS + METADATA_LEN + i)));
        }
    }

}


void jsonFromFlash(std::string json)
{
    int c;
    uint32_t i = 0;
    uint32_t jsonLength;

    printf("\n1. Loading JSON configuration file from Flash memory\n");

    // read byte 0 to determine length to read
    jsonLength = *(uint32_t*)JSON_STORAGE_ADDRESS;

    if (jsonLength == 0xFFFFFFFF)
    {
    	printf("Flash storage location is empty - no config file\n");
    	printf("Using basic default configuration - 3 step generators only\n");

    	jsonLength = sizeof(defaultConfig);

    	json.resize(jsonLength);

		for (i = 0; i < jsonLength; i++)
		{
			c = defaultConfig[i];
			strJson.push_back(c);
		}
    }
    else
    {
		json.resize(jsonLength);

		for (i = 0; i < jsonLength; i++)
		{
			c = *(uint8_t*)(JSON_STORAGE_ADDRESS + 4 + i);
			strJson.push_back(c);
		}
		printf("\n%s\n", json.c_str());
    }
}

void deserialiseJSON()
{
    printf("\n2. Parsing JSON configuration file\n");

    const char *json = strJson.c_str();

    // parse the json configuration file
    DeserializationError error = deserializeJson(doc, json);

    printf("Config deserialisation - ");

    switch (error.code())
    {
        case DeserializationError::Ok:
            printf("Deserialization succeeded\n");
            break;
        case DeserializationError::InvalidInput:
            printf("Invalid input!\n");
            configError = true;
            break;
        case DeserializationError::NoMemory:
            printf("Not enough memory\n");
            configError = true;
            break;
        default:
            printf("Deserialization failed\n");
            configError = true;
            break;
    }
}


void configThreads()
{
    if (configError) return;

    printf("\n3. Configuring threads\n");

    JsonArray Threads = doc["Threads"];

    // create objects from JSON data
    for (JsonArray::iterator it=Threads.begin(); it!=Threads.end(); ++it)
    {
        thread = *it;

        const char* configor = thread["Thread"];
        uint32_t    freq = thread["Frequency"];

        if (!strcmp(configor,"Base"))
        {
            base_freq = freq;
            printf("Setting BASE thread frequency to %d\n", base_freq);
        }
        else if (!strcmp(configor,"Servo"))
        {
            servo_freq = freq;
            printf("Setting SERVO thread frequency to %d\n", servo_freq);
        }
    }
}

void loadModules()
{
    printf("\n4. Loading modules\n");

	// Ethernet communication monitoring
	comms = new RemoraComms();
	servoThread->registerModule(comms);

    if (configError) return;

    JsonArray Modules = doc["Modules"];

    // create objects from JSON data
    for (JsonArray::iterator it=Modules.begin(); it!=Modules.end(); ++it)
    {
        module = *it;

        const char* thread = module["Thread"];
        const char* type = module["Type"];

        if (!strcmp(thread,"Base"))
        {
            printf("\nBase thread object\n");

            if (!strcmp(type,"Stepgen"))
            {
                createStepgen();
            }
         }
        else if (!strcmp(thread,"Servo"))
        {
        	if (!strcmp(type,"Digital Pin"))
			{
				createDigitalPin();
			}
        	else if (!strcmp(type,"Spindle PWM"))
			{
				createSpindlePWM();
			}
        	else if (!strcmp(type,"NVMPG"))
			{
				createNVMPG();
			}
        }
    }

}

void debugThreadHigh()
{
    Module* debugOnB = new Debug("PC_10", 1);
    baseThread->registerModule(debugOnB);

    Module* debugOnS = new Debug("PC_12", 1);
    servoThread->registerModule(debugOnS);
}

void debugThreadLow()
{
    Module* debugOffB = new Debug("PC_10", 0);
    baseThread->registerModule(debugOffB);

    Module* debugOffS = new Debug("PC_12", 0);
    servoThread->registerModule(debugOffS);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_LWIP_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  enum State currentState;
  enum State prevState;

  currentState = ST_SETUP;
  prevState = ST_RESET;

  printf("\nRemora-NVEM starting\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch(currentState){
	          case ST_SETUP:
	              // do setup tasks
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering SETUP state\n\n");
	              }
	              prevState = currentState;

	              jsonFromFlash(strJson);
	              deserialiseJSON();
	              configThreads();
	              createThreads();
	              //debugThreadHigh();
	              loadModules();
	              //debugThreadLow();
	              udpServer_init();
	              IAP_tftpd_init();

	              currentState = ST_START;
	              break;

	          case ST_START:
	              // do start tasks
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering START state\n");
	              }
	              prevState = currentState;

	              if (!threadsRunning)
	              {
	                  // Start the threads
	                  printf("\nStarting the BASE thread\n");
	                  baseThread->startThread();

	                  printf("\nStarting the SERVO thread\n");
	                  servoThread->startThread();

	                  threadsRunning = true;
	              }

	              currentState = ST_IDLE;

	              break;


	          case ST_IDLE:
	              // do something when idle
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering IDLE state\n");
	              }
	              prevState = currentState;

	              //wait for data before changing to running state
	              if (comms->getStatus())
	              {
	                  currentState = ST_RUNNING;
	              }

	              break;

	          case ST_RUNNING:
	              // do running tasks
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering RUNNING state\n");
	              }
	              prevState = currentState;

	              if (comms->getStatus() == false)
	              {
	            	  currentState = ST_RESET;
	              }

	              break;

	          case ST_STOP:
	              // do stop tasks
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering STOP state\n");
	              }
	              prevState = currentState;


	              currentState = ST_STOP;
	              break;

	          case ST_RESET:
	              // do reset tasks
	              if (currentState != prevState)
	              {
	                  printf("\n## Entering RESET state\n");
	              }
	              prevState = currentState;

	              // set all of the rxData buffer to 0
	              // rxData.rxBuffer is volatile so need to do this the long way. memset cannot be used for volatile
	              printf("   Resetting rxBuffer\n");
	              {
	                  int n = sizeof(rxData.rxBuffer);
	                  while(n-- > 0)
	                  {
	                      rxData.rxBuffer[n] = 0;
	                  }
	              }

	              currentState = ST_IDLE;
	              break;

	          case ST_WDRESET:
	        	  // force a reset
	        	  HAL_NVIC_SystemReset();
	              break;
	  }

	  // do Ethernet tasks
	  ethernetif_input(&gnetif);
	  sys_check_timeouts();

	  if (newJson)
	  {
		  printf("\n\nChecking new configuration file\n");
		  if (checkJson() > 0)
		  {
			  printf("Moving new config file to Flash storage\n");
			  moveJson();

			  // force a reset to load new JSON configuration
			  HAL_NVIC_SystemReset();
		  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


void udpServer_init(void)
{
	// UDP Control Block structure
   struct udp_pcb *upcb, *upcb2;
   err_t err;

   /* 1. Create a new UDP control block  */
   upcb = udp_new();

   /* 2. Bind the upcb to the local port */
   ip_addr_t myIPADDR;
   IP_ADDR4(&myIPADDR, 10, 10, 10, 10);

   err = udp_bind(upcb, &myIPADDR, 27181);  // 27181 is the server UDP port


   /* 3. Set a receive callback for the upcb */
   if(err == ERR_OK)
   {
	   udp_recv(upcb, udp_data_callback, NULL);
   }
   else
   {
	   udp_remove(upcb);
   }


   // Try making a second UDP control block...?

   upcb2 = udp_new();
   err = udp_bind(upcb2, &myIPADDR, 27182);  // 27182 is the server UDP port for NVMPG

   if(err == ERR_OK)
   {
	   udp_recv(upcb2, udp_mpg_callback, NULL);
   }
   else
   {
	   udp_remove(upcb2);
   }
}

void udp_data_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	int txlen = 0;
	struct pbuf *txBuf;

	// copy the UDP payload into the rxData structure
	memcpy(&rxBuffer.rxBuffer, p->payload, p->len);

	if (rxBuffer.header == PRU_READ)
	{
		txData.header = PRU_DATA;
		txlen = BUFFER_SIZE;
		comms->dataReceived();
	}
	else if (rxBuffer.header == PRU_WRITE)
	{
		txData.header = PRU_ACKNOWLEDGE;
		txlen = sizeof(txData.header);
		comms->dataReceived();

		// ensure an atomic access to the rxBuffer
		// disable thread interrupts
		__disable_irq();

		// then move the data
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			rxData.rxBuffer[i] = rxBuffer.rxBuffer[i];
		}

		// re-enable thread interrupts
		__enable_irq();
	}


	// allocate pbuf from RAM
	txBuf = pbuf_alloc(PBUF_TRANSPORT, txlen, PBUF_RAM);

	// copy the data into the buffer
	pbuf_take(txBuf, (char*)&txData.txBuffer, txlen);

	// Connect to the remote client
	udp_connect(upcb, addr, port);

	// Send a Reply to the Client
	udp_send(upcb, txBuf);

	// free the UDP connection, so we can accept new clients
	udp_disconnect(upcb);

	// Free the p_tx buffer
	pbuf_free(txBuf);

	// Free the p buffer
	pbuf_free(p);
}


void udp_mpg_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	// copy the UDP payload into the nvmpg structure
	memcpy(&mpgData.payload, p->payload, p->len);

	// Free the p buffer
	pbuf_free(p);

	if (mpgData.header == PRU_NVMPG)
	{
		// use a standard module interface to trigger the update of the MPG
		MPG->configure();
	}
}
