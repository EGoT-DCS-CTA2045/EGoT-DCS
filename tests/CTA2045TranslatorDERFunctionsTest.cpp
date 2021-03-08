#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "DCMImplMock.h"
// #include "../src/UCMImpl.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"
#include<boost/bind.hpp>

using ::testing::Invoke;
using ::testing::Return;
using ::testing::AtLeast;


void TEST_SUCCESS_LOADUP(CTA2045Translator trans,CEA2045DeviceMock* dev){
    trans.loadup();
    ASSERT_EQ(true,true);
}
void TEST_FAIL_LOADUP(CTA2045Translator trans,CEA2045DeviceMock* dev){
    trans.loadup();

    ASSERT_EQ(true,true);
}
void TEST_SUCCESS_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);    
}
void TEST_FAIL_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    std::cout<<"IN F SHED"<<endl;

    ASSERT_EQ(true,true);
}
void TEST_SUCCESS_END_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}
void TEST_FAIL_END_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);    
}
void TEST_SUCCESS_OP_STATE(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}
void TEST_FAIL_OP_STATE(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}

TEST(Translator, TestRunner){
    // =================== successful connection setup =================
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator translator(&dev,&sp,dcm);
    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    EXPECT_CALL(dev, start()).Times(AtLeast(1)).WillOnce(Return(true));
    // initialize successful setup
    EXPECT_CALL(dev, querySuportDataLinkMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    EXPECT_CALL(dev, queryMaxPayload())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    EXPECT_CALL(dev, querySuportIntermediateMessages())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    EXPECT_CALL(dev, intermediateGetDeviceInformation())
        .Times(AtLeast(1))
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));
    
    // =================== end successful connection setup =================

    EXPECT_TRUE(translator.connect());

    TEST_SUCCESS_OP_STATE(translator,&dev);
    TEST_SUCCESS_LOADUP(translator,&dev);
    TEST_FAIL_LOADUP(translator,&dev);
    
    TEST_SUCCESS_SHED(translator,&dev);
    TEST_FAIL_SHED(translator,&dev);

    
    TEST_SUCCESS_END_SHED(translator,&dev);
    TEST_FAIL_END_SHED(translator,&dev);
    
    TEST_FAIL_OP_STATE(translator,&dev);

    TEST_SUCCESS_OP_STATE(translator,&dev);
    TEST_SUCCESS_LOADUP(translator,&dev);
    TEST_FAIL_LOADUP(translator,&dev);
    
    TEST_SUCCESS_SHED(translator,&dev);
    TEST_FAIL_SHED(translator,&dev);

    
    TEST_SUCCESS_END_SHED(translator,&dev);
    TEST_FAIL_END_SHED(translator,&dev);
    
    TEST_FAIL_OP_STATE(translator,&dev);
    // std::cout<<"DER STATE: "<<translator.operating_state();
    
}