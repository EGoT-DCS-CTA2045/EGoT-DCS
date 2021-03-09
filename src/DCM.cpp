#include <iostream>
#include <string>
#include "CTA2045Translator.h"
#include "easylogging++.h"
//INITIALIZE_EASYLOGGINGPP
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
using namespace cea2045;

int main(int argc, char * argv[])
{
    MSTimer timer;
	bool shutdown = false;

	CEA2045SerialPort sp("/dev/ttyUSB0");
	UCMImpl ucm;
	ResponseCodes responseCodes;

	if (!sp.open())
	{
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
		return 0;
	}

	ICEA2045DeviceUCM *device = DeviceFactory::createUCM(&sp, &ucm);

	device->start();

	timer.reset();

	responseCodes = device->querySuportDataLinkMessages().get();

	LOG(INFO) << "  query data link elapsed time: " << timer.getElapsedMS();

	timer.reset();

	responseCodes = device->queryMaxPayload().get();

	LOG(INFO) << "  query max payload elapsed time: " << timer.getElapsedMS();

	timer.reset();

	responseCodes = device->querySuportIntermediateMessages().get();

	LOG(INFO) << "  query intermediate elapsed time: " << timer.getElapsedMS();

	timer.reset();

	responseCodes = device->intermediateGetDeviceInformation().get();

	LOG(INFO) << "  device info elapsed time: " << timer.getElapsedMS();

	LOG(INFO) << "startup complete";

	while (!shutdown)
	{
		char c = getchar();

		switch (c)
		{
			case 'c':
				device->basicCriticalPeakEvent(5).get();
				break;

			case 'e':
				device->basicEndShed(0).get();
				break;

			case 'g':
				device->basicGridEmergency(5).get();
				break;

			case 'l':
				device->basicLoadUp(5).get();
				break;

			case '\n':
				break;

			case 'n':
				device->basicNextRelativePrice(153).get(); // approx 4x
				break;

			case 'o':
				device->basicOutsideCommConnectionStatus(OutsideCommuncatonStatusCode::Found);
				break;

			case 'p':
				device->basicPowerLevel(63).get();		// approx 50%
				break;

			case 'q':
				shutdown = true;
				break;

			case 'r':
				device->basicPresentRelativePrice(101).get();	// approx twice
				break;

			case 's':
				device->basicShed(5).get();
				break;

			case 'C':
				device->intermediateGetCommodity().get();
				break;

			case 'O':
				device->intermediateGetTemperatureOffset().get();
				break;

			case 'S':
				device->intermediateGetSetPoint().get();
				break;

			case 'T':
				device->intermediateGetPresentTemperature().get();
				break;

			default:
				LOG(WARNING) << "invalid command";
				break;
		}
	}

	device->shutDown();

	delete (device);

	return 0;
}
