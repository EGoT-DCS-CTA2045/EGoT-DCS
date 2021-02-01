#include "CTA2045Translator.h"
#include "easylogging++.h"

// using namespace cea2045;

INITIALIZE_EASYLOGGINGPP

#include <cea2045/util/MSTimer.h>

CTA2045Translator::CTA2045Translator():dev(0),emulated(false){
    strncpy(port,"/dev/ttyS6",sizeof(port)-1); // go with default
    SerialPort = new CEA2045SerialPort(port);
#if USE_DEBUG
    InitResponseCodes();
#endif
}
CTA2045Translator::CTA2045Translator(char* p):SerialPort(0),dev(0),emulated(false){
    // copy port
    strncpy(port,"/dev/",sizeof(port)-1);
    strncat(port,p,sizeof(port)-1);
    port[sizeof(port)-1] = '\0';
    SerialPort = new CEA2045SerialPort(port);
#if USE_DEBUG
    InitResponseCodes();    
#endif
}
CTA2045Translator::CTA2045Translator(ICEA2045DeviceUCM* device,CEA2045SerialPort* port):SerialPort(port),emulated(true){
    dev = device;
}
CTA2045Translator::~CTA2045Translator(){
    // no dynamic mem so far
    if (dev && !emulated)
    {
        dev->shutDown();
        delete dev; // free device
        dev = 0;
    }
    if (SerialPort && !emulated){
        delete SerialPort;
        SerialPort = 0;
    }
}
bool CTA2045Translator::disconnect(){
    if (! dev || emulated)
    {
        LOG(INFO) <<" device already diconnected"<<endl;
        return true;
    }
    // disconnect & free
    dev->shutDown();
    delete dev;
    dev = 0;
    return true;
}
#ifdef USE_DEBUG
void CTA2045Translator::InitResponseCodes()
{
    ResCodes[(int)ResponseCode::OK] = (char*)"OK";
    ResCodes[(int)ResponseCode::TIMEOUT] = (char*)"TIMEOUT";
    ResCodes[(int)ResponseCode::BAD_CRC] = (char*)" BAD_CRC";
    ResCodes[(int)ResponseCode::INVALID_RESPONSE] = (char*)"INVALID_RESPONSE";
    ResCodes[(int)ResponseCode::NO_ACK_RECEIVED] = (char*)"NO_ACK_RECEIVED";
    ResCodes[(int)ResponseCode::NAK] = (char*)"NAK";
    return;
}
#endif
bool CTA2045Translator::connect(){
    char res[100];
	if (!SerialPort || !SerialPort->open()){
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
		return false;
	}
    if(!dev)
	    dev = DeviceFactory::createUCM(SerialPort, &dcm);
	dev->start();    

	LOG(INFO) << "==> Query data link ";
	timer.reset();
	response = dev->querySuportDataLinkMessages().get();
#if USE_DEBUG
    LOG(INFO) <<"--> Response: " <<ResCodes[(int)response.responesCode]<<endl;
#endif
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<timer.getElapsedMS()<<" ms";
        return false;
    }

	LOG(INFO) << "==> Query max payload";
	timer.reset();
	response = dev->queryMaxPayload().get();
#if USE_DEBUG
    LOG(INFO) <<"--> Response: " <<ResCodes[(int)response.responesCode]<<endl;
#endif
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<timer.getElapsedMS()<<" ms";
        return false;
    }

	LOG(INFO) << "==> Query intermediate";
	timer.reset();
	response = dev->querySuportIntermediateMessages().get();
#if USE_DEBUG
    LOG(INFO) <<"--> Response: " <<ResCodes[(int)response.responesCode]<<endl;
#endif
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<timer.getElapsedMS()<<" ms"<<endl;
        return false;
    }

	LOG(INFO) << "==> Query Device Information ";
	timer.reset();
	response = dev->intermediateGetDeviceInformation().get();
#if USE_DEBUG
    LOG(INFO) <<"--> Response: " <<ResCodes[(int)response.responesCode]<<endl;
#endif
    if (response.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<timer.getElapsedMS()<<" ms"<<endl;
        return false;
    }
    LOG(INFO) << " SUCESS";
    return true;
}