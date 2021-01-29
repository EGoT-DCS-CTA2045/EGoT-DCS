#include <cea2045/communicationport/CEA2045SerialPort.h>
#include "gmock/gmock.h"

using namespace cea2045;

class CEA2045SerialPortMock : public CEA2045SerialPort {
    public:
        CEA2045SerialPortMock(std::string a):CEA2045SerialPort(a){}
        MOCK_METHOD0(open,bool());
};