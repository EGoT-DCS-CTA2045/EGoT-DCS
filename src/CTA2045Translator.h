#include "DCMImpl.h"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>

using namespace cea2045;
class CTA2045Translator{
    private:
        char port_[50];
        CEA2045SerialPort* serial_port_;
        ResponseCodes DER_response_;
        MSTimer DER_response_timer_;
        DCMImpl DER_response_handler_;
        ICEA2045DeviceUCM* device_;
        bool emulated_;
        bool connected_;

        bool check_operation(int op);
        bool state_transition(int new_state);
        // void display_error(const char* message);
#ifdef USE_DEBUG
        char* response_code_map_[(int)cea2045::ResponseCode::NAK]; // Because NAK code is the greatest (gives the length of the enum)
#endif
    public:
        CTA2045Translator(); // constructor
        CTA2045Translator(ICEA2045DeviceUCM*,CEA2045SerialPort*); // overloaded constructor
        CTA2045Translator(char*);// overloaded contructor
        ~CTA2045Translator();// destructor
        void ResponseCodeMap(cea2045::ResponseCode code,char*);
        bool connect();
        bool disconnect();
        bool shed();
        bool endshed();
        bool levelup();
#ifdef USE_DEBUG
        void InitResponseCodes();
#endif

};