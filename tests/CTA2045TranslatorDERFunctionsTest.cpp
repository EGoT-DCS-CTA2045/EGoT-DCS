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
    // expecting QOS call
    EXPECT_CALL(dev,basicQueryOperationalState())
        .Times(AtLeast(1))
        .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));
       
    EXPECT_TRUE(tr.connect());
}
TEST(LoadUp,LOADUP_SUCCESS){
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

TEST(LoadUp,LOADUP_SUCCESS_ALREADY_IN_LOADUP){
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

TEST(Shed,SHED_SUCCESS){
    // translator
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicShed)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(ENDSHED_STATE))
        .WillOnce(Return(SHED_STATE));
    
    bool ret = trans.shed();
    ASSERT_EQ(ret,true);   
}

TEST(Shed,SHED_SUCCESS_ALREAD_IN_SHED){
    // translator
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicShed)
        .Times(0);
        
    EXPECT_CALL(dcm,get_op_state)
        .Times(1)
        .WillOnce(Return(SHED_STATE));
    
    bool ret = trans.shed();
    ASSERT_EQ(ret,true);   
}

TEST(Shed,SHED_FAIL_DIFFERENT_STATE){
    // translator
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicShed)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

        
    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(ENDSHED_STATE))
        .WillOnce(Return(ENDSHED_STATE));
    
    bool ret = trans.shed();
    ASSERT_EQ(ret,false);   
}

TEST(EndShed,ENDSHED_SUCCESS){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicEndShed)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

        
    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(LOADUP_STATE))
        .WillOnce(Return(ENDSHED_STATE));
    
    bool ret = trans.endshed();
    ASSERT_EQ(ret,true);   
}

TEST(EndShed,ENDSHED_SUCCESS_ALREADY_IN_STATE){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicEndShed)
        .Times(0);
        
    EXPECT_CALL(dcm,get_op_state)
        .Times(1)
        .WillOnce(Return(ENDSHED_STATE));
    
    bool ret = trans.endshed();
    ASSERT_EQ(ret,true);   
}

TEST(EndShed,ENDSHED_FAIL_DIFFERENT_STATE){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
    SETUP_STATE(sp,dev,dcm,trans);

     EXPECT_CALL(dev,basicEndShed)
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,OK_RES, NAK_RES)));

        
    EXPECT_CALL(dcm,get_op_state)
        .Times(2)
        .WillOnce(Return(LOADUP_STATE))
        .WillOnce(Return(LOADUP_STATE));
    
    bool ret = trans.endshed();
    ASSERT_EQ(ret,false);   
}

TEST(LoadUp,LOADUP_OP_STATE_FAIL){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
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
    
    EXPECT_CALL(dev,basicQueryOperationalState())
        .Times(2)
        .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));
    
    EXPECT_TRUE(trans.connect());

    EXPECT_CALL(dev,basicLoadUp) // attempts to loadup
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));

    EXPECT_CALL(dcm,get_op_state) // should never check operating state since QOS fails
        .Times(0);

    bool ret = trans.loadup();
    ASSERT_EQ(ret,false);
}

TEST(Shed,SHED_OP_STATE_FAIL){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
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
    
    EXPECT_CALL(dev,basicQueryOperationalState())
        .Times(2)
        .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));
    
    EXPECT_TRUE(trans.connect());

    EXPECT_CALL(dev,basicShed) // attempts to shed
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));

    EXPECT_CALL(dcm,get_op_state) // should never check operating state since QOS fails
        .Times(0);

    bool ret = trans.shed();
    ASSERT_EQ(ret,false);
}

TEST(EndShed,ENDSHED_OP_STATE_FAIL){
    CEA2045SerialPortMock sp("FAKE PORT");
    CEA2045DeviceMock dev;
    DCMImplMock dcm;
    CTA2045Translator trans(&dev,&sp,dcm);
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
    
    EXPECT_CALL(dev,basicQueryOperationalState())
        .Times(2)
        .WillRepeatedly(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));
    
    EXPECT_TRUE(trans.connect());

    EXPECT_CALL(dev,basicEndShed) // attempts to endshed
        .Times(1)
        .WillOnce(Invoke(boost::bind(&CEA2045DeviceMock::Response,&dev,TIMEOUT_RES, NAK_RES)));

    EXPECT_CALL(dcm,get_op_state) // should never check operating state since QOS fails
        .Times(0);

    bool ret = trans.endshed();
    ASSERT_EQ(ret,false);
}