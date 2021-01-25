#include "DCMImpl.h"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>

class CTA2045Translator{
    private:
        char port[50];
        cea2045::CEA2045SerialPort* SerialPort;
        cea2045::ResponseCodes response;
        cea2045::MSTimer timer;
        DCMImpl dcm;
        cea2045::ICEA2045DeviceUCM *dev;
#ifdef USE_DEBUG
        char* ResponseCodes[(int)cea2045::ResponseCode::NAK]; // Because NAK code is the greatest (gives the length of the enum)
#endif
    public:
        CTA2045Translator(); // constructor
        ~CTA2045Translator();// destructor
        CTA2045Translator(char*);// overloaded contructor
        void ResponseCodeMap(cea2045::ResponseCode code,char*);
        bool connect();
        bool disconnect();
#if USE_DEBUG
        void InitResponseCodes();
#endif

};