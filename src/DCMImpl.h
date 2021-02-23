// TODO: LOOK INTO LICENSE!!
//  - what needs to be included?
// TODO: revisit google C++ style guide

#include "UCMImpl.h"

class DCMImpl : public UCMImpl
{
    public:
        DCMImpl(); // constructor
        ~DCMImpl(); // destructor

        // ======== inherited & overloaded(to be implemented) ============== 
        virtual bool isMessageTypeSupported(cea2045::MessageTypeCode messageType);
        virtual void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message);
        virtual void processOperationalStateReceived(cea2045::cea2045Basic *message);
        int get_op_state();
    private:
        int state_;
};