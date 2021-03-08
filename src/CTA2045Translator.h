#include "DCMImpl.h"
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/device/DeviceFactory.h>

using namespace cea2045;

# define IDLE_NORM 0 
# define RUN_NORM 1
# define RUN_CURT 2
# define RUN_HIEIGH 3 
# define IDLE_GRID 4
# define SGD_ERR 5
# define CHAR_SIZE 100
typedef enum{
    shed_state = RUN_CURT,
    endshed_state = IDLE_NORM,
    loadup_state = RUN_NORM
}grid_state_map;

class CTA2045Translator{
    private:
        char port_[CHAR_SIZE];
        CEA2045SerialPort* serial_port_;
        ResponseCodes DER_response_;
        MSTimer DER_response_timer_;
        DCMImpl* DER_response_handler_;
        ICEA2045DeviceUCM* device_;
        bool emulated_;
        bool connected_;
        bool check_operation(int op);
        bool state_transition(int cmd,int new_state);
        bool check_response(ResponseCodes res,MSTimer tm);
        // grid_function* FDT[FDT_SIZE];
        // void init_FDT();
        // void display_message(int lvl,const char* message);
        
#ifdef USE_DEBUG
        void InitCodes();
        char response_code_map_[(int)cea2045::ResponseCode::NAK + 1][CHAR_SIZE]; // Because NAK code is the greatest (gives the length of the enum)
        char op_states_[SGD_ERR+1][CHAR_SIZE];
#endif
    public:
        CTA2045Translator(); // constructor
        CTA2045Translator(ICEA2045DeviceUCM*,CEA2045SerialPort*,DCMImpl& handler); // overloaded constructor
        CTA2045Translator(char*);// overloaded contructor

        ~CTA2045Translator();// destructor
        void ResponseCodeMap(cea2045::ResponseCode code,char*);
        bool connect();
        bool disconnect();
        bool shed();
        bool endshed();
        bool loadup();
};