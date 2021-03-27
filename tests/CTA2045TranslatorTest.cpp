#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "../src/UCMImpl.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"
#include<boost/bind.hpp>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;

// test device failure due to NULL serial port
TEST(Translator, SerialPortNULL) {
    
    CEA2045DeviceMock dev;
    
    CTA2045Translator translator(&dev,0);
    
    EXPECT_FALSE(translator.connect());
}

// test device failure due to serial port failure
TEST(Translator, SerialPortFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;

    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(false));

    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

// test device failure due to Device.start failure
TEST(Translator, DeviceStartFail) {
    
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev,start()).Times(AtLeast(1)).WillOnce(Return(false));
    
    CTA2045Translator translator(&dev,&sp);
    
    EXPECT_FALSE(translator.connect());
}

// test device failure due to SupportDataLink Query failure
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

// test device failure due to MaxPayload Query failure
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

// test device failure due to SupportIntermediate Query failure
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

// test device failure due to DeviceInfo Query failure
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

// test successful device connection
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

// test successful device connection & disconnection
TEST(Translator, SuccessfulDiconnect){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    CTA2045Translator translator(&dev,&sp);
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev, start()).Times(AtLeast(1)).WillOnce(Return(true));

    EXPECT_CALL(dev, querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, intermediateGetDeviceInformation())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_TRUE(translator.connect());
    EXPECT_CALL(dev, shutDown()).Times(AtLeast(1));
    EXPECT_TRUE(translator.disconnect());
}

// test NULL device (non existent)
TEST(Translator, DiconnectFail){
    CEA2045SerialPortMock sp("FAKE PORT");
    
    CTA2045Translator translator(NULL,&sp); 
    
    EXPECT_FALSE(translator.disconnect());
}

// test double disconnect 
TEST(Translator, DoubleDiconnectFail){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    CTA2045Translator translator(&dev,&sp); 
    
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev, start()).Times(AtLeast(1)).WillOnce(Return(true));

    EXPECT_CALL(dev, querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_CALL(dev, intermediateGetDeviceInformation())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,0,7)));

    EXPECT_TRUE(translator.connect());
    EXPECT_CALL(dev, shutDown()).Times(AtLeast(1));
    
    EXPECT_TRUE(translator.disconnect());
    EXPECT_FALSE(translator.disconnect());
    
}