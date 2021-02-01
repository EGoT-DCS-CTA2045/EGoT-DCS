#include "CEA2045DeviceMock.h"
#include "CEA2045SerialPortMock.h"
#include "../src/UCMImpl.h"
#include "../src/CTA2045Translator.h"
#include "gtest/gtest.h"
#include<boost/bind.hpp>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Invoke;

TEST(Translator, CanConenct) {
    
    UCMImpl ucm;
    CEA2045SerialPortMock sp("dummy");
    
    CEA2045DeviceMock *dev = new CEA2045DeviceMock();
    
    EXPECT_CALL(*dev, start()).Times(AtLeast(1)).WillOnce(Return(true));

    ON_CALL(*dev, querySuportDataLinkMessages()).WillByDefault(Invoke(boost::bind(&CEA2045DeviceMock::Response,dev,0,7)));
    EXPECT_CALL(*dev, querySuportDataLinkMessages()).Times(AtLeast(1));//WillOnce(Return(dev->CEA2045DeviceMock::GoodResponse()));

    ON_CALL(*dev, queryMaxPayload()).WillByDefault(Invoke(boost::bind(&CEA2045DeviceMock::Response,dev,0,7)));
    EXPECT_CALL(*dev, queryMaxPayload()).Times(AtLeast(1));
    
    ON_CALL(*dev, querySuportIntermediateMessages()).WillByDefault(Invoke(boost::bind(&CEA2045DeviceMock::Response,dev,0,7)));
    EXPECT_CALL(*dev, querySuportIntermediateMessages()).Times(AtLeast(1));

    
    ON_CALL(*dev, intermediateGetDeviceInformation()).WillByDefault(Invoke(boost::bind(&CEA2045DeviceMock::Response,dev,0,7)));
    EXPECT_CALL(*dev, intermediateGetDeviceInformation()).Times(AtLeast(1));

    EXPECT_CALL(sp,open()).Times(AtLeast(1)).WillOnce(Return(true));
    
    CTA2045Translator translator(dev,&sp);
    translator.connect();
    delete dev;
}