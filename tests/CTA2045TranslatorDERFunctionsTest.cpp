#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "DCMImplMock.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"
#include<boost/bind.hpp>

using ::testing::Invoke;
using ::testing::Return;
using ::testing::AtLeast;


// dev_res: device response for Operating State Query
// prev_state: previous state of DER BEFORE receiving loadup request
// new_state: previous state of DER AFTER receiving loadup request
void SETUP_STATE(CEA2045SerialPortMock &sp,CEA2045DeviceMock &dev,DCMImplMock & dcm,CTA2045Translator &tr){ 
   // =================== successful connection setup =================
    // CEA2045SerialPortMock sp("FAKE PORT");
    // CEA2045DeviceMock dev;
    // DCMImplMock dcm;
    // CTA2045Translator tr(&dev,&sp,dcm);
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
    // expecting QPS call
    EXPECT_CALL(dev,basicQueryOperationalState())
        .Times(AtLeast(1))
        .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));
       
    EXPECT_TRUE(tr.connect());
}
TEST(LoadUpTest,LOADUP_SUCCESS){
    // create translator args
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

    // expecting a loadup call
    EXPECT_CALL(dev,basicLoadUp)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));
    
     // expect DCMImpl returns
    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(SHED_STATE)) // starting state
        .WillOnce(Return(LOADUP_STATE));

    // make test less dependent on hard coded der state values
    // use mapping enum in CTA2045Translator insteam of DER state values
    bool ret = trans.loadup();
    ASSERT_EQ(ret,true);
}

TEST(LoadUpTest,LOADUP_SUCCESS_DER_ALREADY_IN_LOADUP){
    // translator
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

    // expect DCMImpl returns
    EXPECT_CALL(dcm,get_op_state)
        .Times(1)
        .WillOnce(Return(LOADUP_STATE));
    
    // does not expect any load up call since the translator checks the state first
    EXPECT_CALL(dev,basicLoadUp)
        .Times(0);
    
    // make test less dependent on hard coded der state values
    // use mapping enum in CTA2045Translator insteam of DER state values
    bool ret = trans.loadup();
    ASSERT_EQ(ret,true);
}

TEST(LoadUp,LOADUP_FAIL_DIFFERENT_STATE){
    // translator
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

    EXPECT_CALL(dev,basicLoadUp)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(SHED_STATE))
        .WillOnce(Return(SHED_STATE));

    bool ret = trans.loadup();
    ASSERT_EQ(ret,false);
}

void TEST_SUCCESS_SHED(CTA2045Translator trans,CEA2045DeviceMock &dev,DCMImplMock &dcm){
    // create translator args
    // CEA2045SerialPortMock sp("FAKE PORT");
    // CEA2045DeviceMock dev;
    // DCMImplMock dcm;
    // CTA2045Translator trans(&dev,&sp,dcm);
    // SETUP_STATE(sp,dev,dcm,trans);

    //  EXPECT_CALL(dev,basicShed)
    // .Times(1)
    // .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    // EXPECT_CALL(dcm,get_op_state)
    // .Times(2)
    // .WillOnce(Return(END_SHED))
    // .WillOnce(Return(SHED_STATE));
    
    // bool ret = trans.shed();
    // ASSERT_EQ(ret,true);   
}
void TEST_FAIL_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}
void TEST_SUCCESS_END_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}
void TEST_FAIL_END_SHED(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);    
}
void TEST_SUCCESS_OP_STATE(CTA2045Translator trans,CEA2045DeviceMock* dev,DCMImplMock* dcm){
    // trans.check_operation(1);
    ASSERT_EQ(true,true);
}
void TEST_FAIL_OP_STATE(CTA2045Translator trans,CEA2045DeviceMock* dev){
    ASSERT_EQ(true,true);
}

// TEST(Translator, TestRunner){
    

    // EXPECT_TRUE(translator.connect());
    // EXPECT_CALL(dev,basicQueryOperationalState())
    // .Times(AtLeast(1))
    // .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    // // TEST_SUCCESS_OP_STATE(translator,&dev,&dcm);
    // TEST_SUCCESS_LOADUP(translator,dev,dcm);
    // TEST_SUCCESS_DER_ALREADY_LOADUP(translator,dev,dcm);
    // TEST_FAIL_LOADUP(translator,dev,dcm);
    
    // TEST_SUCCESS_SHED(translator,&dev);
    // TEST_FAIL_SHED(translator,&dev);

    
    // TEST_SUCCESS_END_SHED(translator,&dev);
    // TEST_FAIL_END_SHED(translator,&dev);
    
    // TEST_FAIL_OP_STATE(translator,&dev);

    // TEST_SUCCESS_OP_STATE(translator,&dev);
    // TEST_SUCCESS_LOADUP(translator,&dev);
    // TEST_FAIL_LOADUP(translator,&dev);
    
    // TEST_SUCCESS_SHED(translator,&dev);
    // TEST_FAIL_SHED(translator,&dev);

    
    // TEST_SUCCESS_END_SHED(translator,&dev);
    // TEST_FAIL_END_SHED(translator,&dev);
    
    // TEST_FAIL_OP_STATE(translator,&dev);
    // std::cout<<"DER STATE: "<<translator.operating_state();
    
// }