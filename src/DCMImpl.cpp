# include "DCMImpl.h"
#include "easylogging++.h"


using namespace std;

// sets port number to default values
DCMImpl::DCMImpl()
{
}
DCMImpl::~DCMImpl()
{
    // no dynamic mem so far
}

// =============================== abstract funcs to be implemented ============================

bool DCMImpl::isMessageTypeSupported(cea2045::MessageTypeCode messageType)
{

	LOG(INFO) << "message type supported received: " << (int)messageType;
	if (messageType == cea2045::MessageTypeCode::NONE)
		return false;
	return true;
}
void DCMImpl::processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message){

	LOG(INFO) << "device type: " << message->getDeviceType();
	LOG(INFO) << "vendor ID: " << message->getVendorID();

	LOG(INFO) << "firmware date: "
			<< 2000 + (int)message->firmwareYear20xx << "-" << (int)message->firmwareMonth << "-" << (int)message->firmwareDay;
}