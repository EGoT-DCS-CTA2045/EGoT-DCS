#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "../src/UCMImpl.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"
#include<boost/bind.hpp>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;


TEST(Translator, SerialPortFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(false));

    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, DeviceStartFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(false));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, SupportDataLinkFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,1,7)));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, MaxPayloadFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,1,7)));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, SupportIntermediateFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,1,7)));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, DeviceInfoFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));
    EXPECT_CALL(dev,intermediateGetDeviceInformation())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,1,7)));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

TEST(Translator, SuccessfulConenct) {
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    // serial port expectation
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));

    // start function expectation
    EXPECT_CALL(dev, start()).Times(AtLeast(1)).WillOnce(Return(true));

    // querySuportDataLinkMessages expectation
    EXPECT_CALL(dev, querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    // queryMaxPayload expectation
    EXPECT_CALL(dev, queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    // querySuportIntermediateMessages expectation
    EXPECT_CALL(dev, querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    // intermediateGetDeviceInformation expectation
    EXPECT_CALL(dev, intermediateGetDeviceInformation())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    // create translator object
    CTA2045Translator translator(&dev,&sp);
    // expectation of unit
    EXPECT_TRUE(translator.connect());
}