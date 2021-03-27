// =====================================================================================
// Copyright (c) 2016, Electric Power Research Institute (EPRI)
// All rights reserved.
//
// libcea2045 ("this software") is licensed under BSD 3-Clause license.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// *  Neither the name of EPRI nor the names of its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
// OF SUCH DAMAGE.
//
// This EPRI software incorporates work covered by the following copyright and permission
// notices. You may not use these works except in compliance with their respective
// licenses, which are provided below.
//
// These works are provided by the copyright holders and contributors "as is" and any express or
// implied warranties, including, but not limited to, the implied warranties of merchantability
// and fitness for a particular purpose are disclaimed.
//
// This software relies on the following libraries and licenses:
//
// #########################################################################################
// Boost Software License, Version 1.0
// #########################################################################################
//
// * catch++ v1.2.1 (https://github.com/philsquared/Catch)
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// #########################################################################################
// MIT Licence
// #########################################################################################
//
// * easylogging++ Copyright (c) 2017 muflihun.com
//   https://github.com/easylogging/easyloggingpp
//   https://easylogging.muflihun.com
//   https://muflihun.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/*
 * IUCM.h
 *
 *  Created on: Aug 24, 2015
 *      Author: dupes
 */

#ifndef CEA2045_CEA2045_PROCESSMESSAGE_IUCM_H_
#define CEA2045_CEA2045_PROCESSMESSAGE_IUCM_H_

#include "../message/ConvertEnums.h"
#include "../message/CEA2045MessageDeviceInfoResponse.h"
#include "../message/CEA2045MessageCommodityResponse.h"
#include "../message/CEA2045MessageBasic.h"
#include "../message/CEA2045MessageIntermediateResponse.h"
#include "../message/CEA2045MessageGetTemperatureOffsetResponse.h"
#include "../message/CEA2045MessageGetSetpointsResponse.h"
#include "../message/CEA2045MessageGetPresentTemperatureResponse.h"
#include "../message/CEA2045MessageGetUTCTimeResponse.h"

namespace cea2045 {

class IUCM
{
public:
	IUCM() {};
	virtual ~IUCM() {};

	virtual bool isMessageTypeSupported(MessageTypeCode messageType) = 0;
	virtual MaxPayloadLengthCode getMaxPayload() = 0;

	virtual void processMaxPayloadResponse(MaxPayloadLengthCode maxPayload) = 0;
	virtual void processDeviceInfoResponse(cea2045DeviceInfoResponse *message) = 0;
	virtual void processCommodityResponse(cea2045CommodityResponse *message) = 0;
	virtual void processSetEnergyPriceResponse(cea2045IntermediateResponse *message) = 0;
	virtual void processSetTemperatureOffsetResponse(cea2045IntermediateResponse *message) = 0;
	virtual void processGetTemperatureOffsetResponse(cea2045GetTemperateOffsetResponse *message) = 0;
	virtual void processGetSetpointsResponse(cea2045GetSetpointsResponse2 *message) = 0;
	virtual void processGetSetpointsResponse(cea2045GetSetpointsResponse1 *message) = 0;
	virtual void processSetSetpointsResponse(cea2045IntermediateResponse *message) = 0;
	virtual void processStartCyclingResponse(cea2045IntermediateResponse *message) = 0;
	virtual void processTerminateCyclingResponse(cea2045IntermediateResponse *message) = 0;
	virtual void processGetPresentTemperatureResponse(cea2045GetPresentTemperatureResponse *message) = 0;
	virtual void processGetUTCTimeResponse(cea2045GetUTCTimeResponse *message) = 0;
	virtual void processAckReceived(MessageCode messageCode) = 0;
	virtual void processNakReceived(LinkLayerNakCode nak, MessageCode messageCode) = 0;

	virtual void processAppAckReceived(cea2045Basic *message) = 0;
	virtual void processAppNakReceived(cea2045Basic *message) = 0;
	virtual void processOperationalStateReceived(cea2045Basic *message) = 0;
	virtual void processAppCustomerOverride(cea2045Basic *message) = 0;

	virtual void processIncompleteMessage(const unsigned char *buffer, unsigned int numBytes) = 0;
};

} /* namespace cea2045 */

#endif /* CEA2045_CEA2045_PROCESSMESSAGE_IUCM_H_ */
