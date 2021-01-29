#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "../src/UCMImpl.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::ReturnPointee;

TEST(Translator, CanConenct) {
    
    UCMImpl ucm;
    CEA2045SerialPort sp("/dev/ttyS6");
    
    // ResponseCodes *res = new ResponseCodes();//::OK,LinkLayerNakCode::NONE);
    // res->responesCode = ResponseCode::OK;
    // res->nak = LinkLayerNakCode::NONE;
    CEA2045DeviceMock *dev = new CEA2045DeviceMock();
    
    EXPECT_CALL(*dev, start()).Times(AtLeast(1)).WillOnce(Return(true));
    // ON_CALL(*dev, querySuportDataLinkMessages()).WillByDefault(ReturnPointee(*res));
    EXPECT_CALL(*dev, querySuportDataLinkMessages()).Times(AtLeast(1));
    EXPECT_CALL(*dev, queryMaxPayload()).Times(AtLeast(1));
    EXPECT_CALL(*dev, querySuportIntermediateMessages()).Times(AtLeast(1));
    EXPECT_CALL(*dev, intermediateGetDeviceInformation()).Times(AtLeast(1));
    EXPECT_CALL(*dev, shutDown()).Times(AtLeast(1));
    CTA2045Translator translator(dev,&sp);
    translator.connect();
}