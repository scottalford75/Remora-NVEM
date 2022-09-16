#ifndef REMORACOMMS_H
#define REMORACOMMS_H

#include <cstring>

extern "C"
{
	#include "lwip/api.h"
	#include "lwip/pbuf.h"
	#include "lwip/udp.h"
	#include "lwip/tcp.h"
}

#include "configuration.h"
#include "remora.h"

#include "../module.h"

class RemoraComms : public Module
{
  private:

	bool		data;
	bool		status;

	uint8_t		noDataCount;

  public:

	RemoraComms(void);

	virtual void update(void);
	void dataReceived();
	bool getStatus();
};




#endif
