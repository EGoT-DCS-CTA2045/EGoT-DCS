#include <cea2045/device/DeviceFactory.h>
#include "gmock/gmock.h"

using namespace cea2045;

class CEA2045DeviceMock : public ICEA2045DeviceUCM {
    public:
        CEA2045DeviceMock():ICEA2045DeviceUCM(){};
        std::future<ResponseCodes> Response(int res,int nak){
            auto ret = std::async(std::launch::async,[res,nak]()->ResponseCodes{
                ResponseCodes r; 
                r.responesCode = (ResponseCode)res;
                r.nak = (LinkLayerNakCode)nak;
                return r;
            });
            return ret;
        }
        MOCK_METHOD0(start,bool());
        MOCK_METHOD0(shutDown,void());
        MOCK_METHOD0(intermediateGetDeviceInformation,std::future<ResponseCodes>());
        MOCK_METHOD0(queryMaxPayload,std::future<ResponseCodes>());
        MOCK_METHOD0(querySuportDataLinkMessages,std::future<ResponseCodes>());
        MOCK_METHOD0(querySuportIntermediateMessages,std::future<ResponseCodes>());

        MOCK_METHOD3(queryMessageTypeSupported,std::future<ResponseCodes>(MessageCode messageCode, unsigned char messageType1, unsigned char messageType2));
        MOCK_METHOD0(intermediateGetCommodity,std::future<ResponseCodes>());
        MOCK_METHOD0(intermediateGetTemperatureOffset,std::future<ResponseCodes>());
        MOCK_METHOD0(intermediateGetSetPoint,std::future<ResponseCodes>());
        MOCK_METHOD0(intermediateGetPresentTemperature,std::future<ResponseCodes>());
        MOCK_METHOD2(intermediateSetTemperatureOffset,std::future<ResponseCodes>(unsigned char temperatureOffset, TemperatureUnits units));
        MOCK_METHOD4(intermediateSetSetpoints,std::future<ResponseCodes>(unsigned short deviceType, TemperatureUnits units, unsigned short setpoint1, unsigned short setpoint2));
        MOCK_METHOD5(intermediateSetEnergyPrice,std::future<ResponseCodes>(unsigned short , unsigned short ,unsigned char , unsigned int ,unsigned short ));
        MOCK_METHOD7(intermediateStartCycling,std::future<ResponseCodes>(unsigned int , unsigned int, unsigned short ,unsigned char , unsigned char, unsigned char,unsigned char ));
        MOCK_METHOD2(intermediateTerminateCycling,std::future<ResponseCodes>(unsigned int eventID, unsigned char endRandomizationInMinutes));
        MOCK_METHOD1(basicEndShed,std::future<ResponseCodes>(unsigned char eventDuration));
        MOCK_METHOD1(basicGridEmergency,std::future<ResponseCodes>(unsigned char eventDuration));
        MOCK_METHOD1(basicLoadUp,std::future<ResponseCodes>(unsigned char eventDuration));
        MOCK_METHOD1(basicOutsideCommConnectionStatus,std::future<ResponseCodes>(OutsideCommuncatonStatusCode code));
        MOCK_METHOD1(basicPresentRelativePrice,std::future<ResponseCodes>(unsigned char relativePriceIndicator));
        MOCK_METHOD1(basicNextRelativePrice,std::future<ResponseCodes>(unsigned char relativePriceIndicator));
        MOCK_METHOD0(basicQueryOperationalState,std::future<ResponseCodes>());
        MOCK_METHOD1(basicShed,std::future<ResponseCodes>(unsigned char eventDuration));
        MOCK_METHOD1(basicPowerLevel,std::future<ResponseCodes>(unsigned char powerLevel));
        MOCK_METHOD1(basicCriticalPeakEvent,std::future<ResponseCodes>(unsigned char powerLevel));

};