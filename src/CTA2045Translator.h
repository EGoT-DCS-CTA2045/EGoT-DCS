#include "DCMImpl.h"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>
// #include <cea2045/message/CEA2045Message.h>

class CTA2045Translator{
    private:
        char port[50];
        cea2045::CEA2045SerialPort* SerialPort;
        cea2045::ResponseCodes response;
        cea2045::MSTimer timer;
        DCMImpl dcm;
        cea2045::ICEA2045DeviceUCM *dev;
    public:
        CTA2045Translator(); // constructor
        ~CTA2045Translator();// destructor
        CTA2045Translator(char*);// overloaded contructor
        void ResponseCodeMap(cea2045::ResponseCode code,char*);
        bool connect();
        bool disconnect();

};