#include "DCMImpl.h"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>

using namespace cea2045;
class CTA2045Translator{
    private:
        char port[50];
        CEA2045SerialPort* SerialPort;
        ResponseCodes response;
        MSTimer timer;
        DCMImpl dcm;
        ICEA2045DeviceUCM *dev;
#ifdef USE_DEBUG
        char* ResCodes[(int)cea2045::ResponseCode::NAK]; // Because NAK code is the greatest (gives the length of the enum)
#endif
    public:
        CTA2045Translator(); // constructor
        CTA2045Translator(ICEA2045DeviceUCM*,CEA2045SerialPort*); // overloaded constructor
        CTA2045Translator(char*);// overloaded contructor
        ~CTA2045Translator();// destructor
        void ResponseCodeMap(cea2045::ResponseCode code,char*);
        bool connect();
        bool disconnect();
#if USE_DEBUG
        void InitResponseCodes();
#endif

};