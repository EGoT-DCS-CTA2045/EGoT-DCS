#include "CTA2045Translator.h"
#include "easylogging++.h"

// using namespace cea2045;

INITIALIZE_EASYLOGGINGPP

#include <cea2045/util/MSTimer.h>

CTA2045Translator::CTA2045Translator():device_(0),emulated_(false){
    strncpy(port,"/dev/ttyS6",sizeof(port)-1); // go with default
    serial_port_ = new CEA2045SerialPort(port);
#ifdef USE_DEBUG
    InitResponseCodes();
#endif
}
CTA2045Translator::CTA2045Translator(char* p):serial_port_(0),device_(0),emulated_(false){
    // copy port
    strncpy(port,"/dev/",sizeof(port)-1);
    strncat(port,p,sizeof(port)-1);
    port[sizeof(port)-1] = '\0';
    serial_port_ = new CEA2045SerialPort(port);
#ifdef USE_DEBUG
    InitResponseCodes();    
#endif
}
CTA2045Translator::CTA2045Translator(ICEA2045DeviceUCM* dev,CEA2045SerialPort* port):serial_port_(port),emulated_(true){
    device_ = dev;
#ifdef USE_DEBUG
    InitResponseCodes();
#endif
}
CTA2045Translator::~CTA2045Translator(){
    // no dynamic mem so far
    if (device_ && !emulated_)
    {
        device_->shutDown();
        delete device_; // free device
        device_ = 0;
    }
    if (serial_port_ && !emulated_){
        delete serial_port_;
        serial_port_ = 0;
    }
}
bool CTA2045Translator::disconnect(){
    if (!device_)
    {
        LOG(INFO) <<" device diconnected: FAILED";
        LOG(INFO) <<" device already diconnected"<<endl;
        return false;
    }
    // disconnect & free
    device_->shutDown();
    LOG(INFO) <<" device diconnected: SUCCESS"<<endl;
    if (!emulated_) // clean up
        delete device_;
    device_ = 0;
    return true;
}
#ifdef USE_DEBUG
void CTA2045Translator::InitResponseCodes()
{
    response_code_map_[(int)ResponseCode::OK] = (char*)"OK";
    response_code_map_[(int)ResponseCode::TIMEOUT] = (char*)"TIMEOUT";
    response_code_map_[(int)ResponseCode::BAD_CRC] = (char*)" BAD_CRC";
    response_code_map_[(int)ResponseCode::INVALID_RESPONSE] = (char*)"INVALID_RESPONSE";
    response_code_map_[(int)ResponseCode::NO_ACK_RECEIVED] = (char*)"NO_ACK_RECEIVED";
    response_code_map_[(int)ResponseCode::NAK] = (char*)"NAK";
    return;
}
#endif
bool CTA2045Translator::connect(){

    char res[100];
	if (!serial_port_ || !serial_port_->open()){
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
		return false;
	}
    if(!device_)
	    device_ = DeviceFactory::createUCM(serial_port_, &DER_response_handler_);
	if(!device_->start()){
        LOG(ERROR) << "failed to start device: " << strerror(errno);
		return false;
    }  

	LOG(INFO) << "==> Query data link ";
	DER_response_timer_.reset();
	DER_response_ = device_->querySuportDataLinkMessages().get();
#ifdef USE_DEBUG
    LOG(INFO) <<"--> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms";
        return false;
    }

	LOG(INFO) << "==> Query max payload";
	DER_response_timer_.reset();
	DER_response_ = device_->queryMaxPayload().get();
#ifdef USE_DEBUG
    LOG(INFO) <<"--> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms";
        return false;
    }

	LOG(INFO) << "==> Query intermediate";
	DER_response_timer_.reset();
	DER_response_ = device_->querySuportIntermediateMessages().get();
#ifdef USE_DEBUG
    LOG(INFO) <<"--> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms"<<endl;
        return false;
    }

	LOG(INFO) << "==> Query Device Information ";
	DER_response_timer_.reset();
	DER_response_ = device_->intermediateGetDeviceInformation().get();
#ifdef USE_DEBUG
    LOG(INFO) <<"--> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms"<<endl;
        return false;
    }
    LOG(INFO) << " SUCESS";
    return true;
}