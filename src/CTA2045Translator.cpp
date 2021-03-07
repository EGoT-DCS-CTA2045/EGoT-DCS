#include "CTA2045Translator.h"
#include "easylogging++.h"

// using namespace cea2045;

INITIALIZE_EASYLOGGINGPP

#include <cea2045/util/MSTimer.h>

CTA2045Translator::CTA2045Translator():device_(0),emulated_(false){
    strncpy(port_,"/dev/ttyS6",sizeof(port_)-1); // go with default
    serial_port_ = new CEA2045SerialPort(port_);
#ifdef USE_DEBUG
    InitCodes();
#endif
}
CTA2045Translator::CTA2045Translator(char* p):serial_port_(0),device_(0),emulated_(false){
    // copy port
    strncpy(port_,"/dev/",sizeof(port_)-1);
    strncat(port_,p,sizeof(port_)-1);
    port_[sizeof(port_)-1] = '\0';
    serial_port_ = new CEA2045SerialPort(port_);
#ifdef USE_DEBUG
    InitCodes();    
#endif
}
CTA2045Translator::CTA2045Translator(ICEA2045DeviceUCM* dev,CEA2045SerialPort* port):serial_port_(port),emulated_(true){
    device_ = dev;
#ifdef USE_DEBUG
    InitCodes();
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
    LOG(INFO) <<"|=> diconnected: SUCCESS"<<endl;
    if (!emulated_) // clean up
        delete device_;
    device_ = 0;
    return true;
}
#ifdef USE_DEBUG
void CTA2045Translator::InitCodes(){
    // initialize response codes
    strcpy(response_code_map_[(int)ResponseCode::OK], "OK");
    strcpy(response_code_map_[(int)ResponseCode::TIMEOUT],"TIMEOUT");
    strcpy(response_code_map_[(int)ResponseCode::BAD_CRC] , " BAD_CRC");
    strcpy(response_code_map_[(int)ResponseCode::INVALID_RESPONSE] , "INVALID_RESPONSE");
    strcpy(response_code_map_[(int)ResponseCode::NO_ACK_RECEIVED] , "NO_ACK_RECEIVED");
    strcpy(response_code_map_[(int)ResponseCode::NAK] , "NAK");
    // initialize state codes
    strcpy(op_states_[IDLE_NORM], "IDLE NORMAL");
    strcpy(op_states_[RUN_NORM] , "RUNNING NORMAL");
    strcpy(op_states_[RUN_CURT] , "RUNNING CURTAILED GRID");
    strcpy(op_states_[RUN_HIEIGH] , "RUNNING HEIGHTENED GRID");
    strcpy(op_states_[IDLE_GRID] , "IDLE GRID");
    strcpy(op_states_[SGD_ERR] , "SGD ERROR CONDITION");
    return;
}
#endif
bool CTA2045Translator::connect(){
    char res[100];
    connected_ = false;
	if (!serial_port_ || !serial_port_->open()){
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
        return connected_;
	}
    if(!device_)
	    device_ = DeviceFactory::createUCM(serial_port_, &DER_response_handler_);
	if(!device_->start()){
        LOG(ERROR) << "failed to start device: " << strerror(errno);
        return connected_;
    }  

	LOG(INFO) << "==> Query data link ";
	DER_response_timer_.reset();
	DER_response_ = device_->querySuportDataLinkMessages().get();
#ifdef USE_DEBUG
    LOG(WARNING) <<"> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms";
        return connected_;
    }

	LOG(INFO) << "==> Query max payload";
	DER_response_timer_.reset();
	DER_response_ = device_->queryMaxPayload().get();
#ifdef USE_DEBUG
    LOG(WARNING) <<"> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms";
        return connected_;
    }

	LOG(INFO) << "==> Query intermediate";
	DER_response_timer_.reset();
	DER_response_ = device_->querySuportIntermediateMessages().get();
#ifdef USE_DEBUG
    LOG(WARNING) <<"> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms"<<endl;
        return connected_;
    }

    LOG(INFO) << "==> Query Device Information ";
	DER_response_timer_.reset();
	DER_response_ = device_->intermediateGetDeviceInformation().get();
#ifdef USE_DEBUG
    LOG(WARNING) <<"> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
#endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << " Connection FAILED. Query took: "<<DER_response_timer_.getElapsedMS()<<" ms"<<endl;
    }
    
    LOG(INFO) << "|=> connection: SUCESS"<<endl;
    connected_ = true;
    return connected_;
}

// TODO: use a message formatter to avoid code replication!


bool CTA2045Translator::shed(){
    bool success = false;
    LOG(INFO) << "==> Shed";
    success=state_transition(LOADUP);
    if (!success){
        LOG(INFO) << "|=> shed: FAILED";
        return success;
    }
    LOG(INFO) << "|=> Shed: SUCCESS";
    return success;
}

bool CTA2045Translator::endshed(){
    bool success = false;
    LOG(INFO) << "==> Endshed";
    success=state_transition(LOADUP);
    if (!success){
        LOG(INFO) << "|=> endshed: FAILED";
        return success;
    }
    LOG(INFO) << "|=> endshed: SUCCESS";
    return success;
}

bool CTA2045Translator::loadup(){
    bool success = false;
    LOG(INFO) << "==> Loadup";
    success=state_transition(LOADUP);
    if (!success){
        LOG(INFO) << "|=> loadup: FAILED";
        return success;
    }
    LOG(INFO) << "|=> loadup: SUCCESS";
    return success;
}


bool CTA2045Translator::check_operation(int new_state){
    int state = -1;
    DER_response_ = device_->basicQueryOperationalState().get();
 #ifdef USE_DEBUG
     LOG(WARNING) <<"> Response: " <<response_code_map_[(int)DER_response_.responesCode]<<endl;
 #endif
    if (DER_response_.responesCode > ResponseCode::OK){
        LOG(ERROR) << "failed to get the Qeury Op State ack from DER" << strerror(errno);
        return false;
    }
    state = DER_response_handler_.get_op_state();
 #ifdef USE_DEBUG
    LOG(WARNING) <<"> Recieved state: "<<state<<" -- "<<op_states_[state]<<endl;
 #endif
    return state == new_state;
}
bool CTA2045Translator::state_transition(int new_state){
    bool transitioned = false;
    
    cout<<"HERE\n";
    if (!connected_)
        return false;
    if(!(new_state == SHED || END_SHED || LOADUP))
        return transitioned;
    // check if already in state
    transitioned = check_operation(new_state);
    if (transitioned)
        return transitioned;
    // send a transition
    //use FDT to avoid code replication
    // check state again
    transitioned = check_operation(new_state);
    return transitioned;
}