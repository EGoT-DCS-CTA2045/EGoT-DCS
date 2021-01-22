#include "CTA2045Translator.h"
// #include "DCMImpl.h"

#include "easylogging++.h"

// #include <cea2045/device/DeviceFactory.h>


using namespace cea2045;

INITIALIZE_EASYLOGGINGPP

#include <cea2045/util/MSTimer.h>

CTA2045Translator::CTA2045Translator(){
    strncpy(port,"/dev/ttyS5",sizeof(port)-1); // go with default
    SerialPort = new CEA2045SerialPort(port);
    std::cout<<port<<endl;
}
CTA2045Translator::CTA2045Translator(char* p):SerialPort(0){
    // copy port
    strncpy(port,"/dev/",sizeof(port)-1);
    strncat(port,p,sizeof(port)-1);
    port[sizeof(port)-1] = '\0';
    std::cout<<port<<endl;
    SerialPort = new CEA2045SerialPort(port);
}
CTA2045Translator::~CTA2045Translator(){
    // no dynamic mem so far
    if (dev)
    {
        dev->shutDown();
        delete dev; // free device
        dev = 0;
    }
    if (SerialPort){
        delete SerialPort;
        SerialPort = 0;
    }
}
bool CTA2045Translator::disconnect(){
    if (! dev)
    {
        LOG(INFO) <<" device already diconnected"<<endl;
        return false;
    }
    // disconnect & free
    dev->shutDown();
    delete dev;
    dev = 0;
    return true;
}
void CTA2045Translator::ResponseCodeMap(ResponseCode code,char* res)
{
    switch (code)
    {
        case ResponseCode::OK:
            strcpy(res,"OK");
            break;
	    case ResponseCode::TIMEOUT:
            strcpy(res,"TIMEOUT");
            break;
        case ResponseCode::BAD_CRC:
             strcpy(res,"BAD CRC");
            break;
	    case ResponseCode::INVALID_RESPONSE:
            strcpy(res,"INVALID RESPONSE");
            break;
	    case ResponseCode::NO_ACK_RECEIVED:
            strcpy(res,"NO ACK RECEIVED");
            break;
	    case ResponseCode::NAK:
            strcpy(res,"NAK");
            break;
        default:
            strcpy(res,"None!!");
            break;
    }
}
bool CTA2045Translator::connect(){
    char res[100];
	if (!SerialPort || !SerialPort->open()){
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
		return false;
	}

	dev = DeviceFactory::createUCM(SerialPort, &dcm);
	dev->start();


	timer.reset();
	response = dev->querySuportDataLinkMessages().get();
    ResponseCodeMap(response.responesCode,res);
	LOG(INFO) << "  query data link elapsed time --> "<<res;
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " connection failed: "<<timer.getElapsedMS()<<"response code"<<res;
        return false;
    }

	timer.reset();
	response = dev->queryMaxPayload().get();
    ResponseCodeMap(response.responesCode,res);
	LOG(INFO) << "  query max payload elapsed time --> "<<res;
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " connection failed: "<<timer.getElapsedMS()<<"response code"<<res;
        return false;
    }

	timer.reset();
	response = dev->querySuportIntermediateMessages().get();
    ResponseCodeMap(response.responesCode,res);
	LOG(INFO) << "  query intermediate --> " << res;
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " connection failed: "<<timer.getElapsedMS()<<"response code"<<res;
        return false;
    }

	timer.reset();
	response = dev->intermediateGetDeviceInformation().get();
    ResponseCodeMap(response.responesCode,res);
	LOG(INFO) << "  query intermediate (Device Information) --> "<<res;
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " connection failed: "<<timer.getElapsedMS()<<"response code"<<res;
        return false;
    }
    LOG(INFO) << " SUCESS";
    return true;
}