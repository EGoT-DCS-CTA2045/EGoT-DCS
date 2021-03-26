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
 * LinkLayerUnitTest.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: rgause
 */


#include "ProcessMessageMock.h"

#include <cea2045/device/CEA2045DeviceUCM.h>
#include <cea2045/util/Checksum.h>

#include "LinkLayerMock.h"
#include <time.h>

#include "../../catch.hpp"
#include "../../mocks/request/MessageMock.h"

//======================================================================================

using namespace cea2045;

//======================================================================================

SCENARIO("LinkLayer.SendRequest")
{
	LinkLayerMock linkLayerMock;

	ProcessMessageMock processMessage;

	CEA2045DeviceUCM ucm(&linkLayerMock, &processMessage);

	std::future<ResponseCodes> responseCode =
			ucm.queueRequest(new RequestMock(MessageCode::NONE));

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("BASIC MESSAGE RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x1, 0x0, 0x2, 0x1, 0x1, 0xA, 0x3E };
		linkLayerMock.bufferResponse(buffer, sizeof(buffer));

		ucm.processNextRequest();

		THEN("SHOULD PROCESS BASIC MESSAGE")
		{
			REQUIRE(processMessage.basicCount == 1);
			REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
			REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::OK);
		}
	}

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("INVALID CRC RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x1, 0x0, 0x2, 0x1, 0x1, 0xA, 0x3F };

		linkLayerMock.bufferResponse(buffer, sizeof(buffer), false);

		ucm.processNextRequest();

		THEN("SHOULD SEND CRC NAK")
		{
			REQUIRE(linkLayerMock.sendLinkLayerNakCount == 1);
			REQUIRE(linkLayerMock.nak == LinkLayerNakCode::CHECKSUM_ERROR);
			REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
			REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::BAD_CRC);
		}
	}

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("LINK LAYER ACK/NAK RECEIVED")
	{
		SECTION("ACK RECEIVED")
		{
			unsigned char buffer[] = { 0x06, 0x00 };

			linkLayerMock.bufferResponse(buffer, sizeof(buffer), false, false);

			ucm.processNextRequest();

			THEN("SHOULD PROCESS LINK LAYER ACK/NAK")
			{
				REQUIRE(processMessage.ackNakCount == 1);
			}
		}

		// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

		SECTION("NAK RECEIVED")
		{
			unsigned char buffer[] = { 0x15, 0x05 };

			linkLayerMock.bufferResponse(buffer, sizeof(buffer), false, false);

			ucm.processNextRequest();

			THEN("SHOULD PROCESS LINK LAYER ACK/NAK")
			{
				REQUIRE(processMessage.ackNakCount == 1);
				REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
				REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::NAK);
			}
		}
	}

	WHEN("ACK NOT RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x1, 0x0, 0x2, 0x1, 0x1, 0xA, 0x3E };
		linkLayerMock.bufferResponse(buffer, sizeof(buffer), true, false);

		ucm.processNextRequest();

		THEN("SHOULD PROCESS BASIC MESSAGE")
		{
			REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::NO_ACK_RECEIVED);
		}
	}
}

SCENARIO("LinkLayer.RequestReceived")
{
	LinkLayerMock linkLayerMock;

	ProcessMessageMock processMessage;

	CEA2045DeviceUCM ucm(&linkLayerMock, &processMessage);

	ReceiveBuffer receiveBuffer(4096);

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("MESSAGE TYPE SUPPORTED RECEIVED")
	{

		unsigned char buffer[] = { 0x08, 0x01, 0x00, 0x00, 0x7e, 0xcd };

		linkLayerMock.bufferResponse(buffer, sizeof(buffer), true, false);

		ucm.recvOne(receiveBuffer);

		THEN("SHOULD PROCESS MESSAGE TYPE SUPPORTED")
		{
			REQUIRE(processMessage.messageTypeSupportedCount == 1);
			REQUIRE(receiveBuffer.getNumBytes() == 0);
		}

	}

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("DATA LINK MESSAGE RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x3, 0x0, 0x2, 0x18, 0x0, 0xBA, 0x75 };

		linkLayerMock.bufferResponse(buffer, sizeof(buffer), true, false);

		ucm.recvOne(receiveBuffer);

		THEN("SHOULD PROCESS DATA LINK")
		{
			REQUIRE(processMessage.dataLinkCount == 1);
			REQUIRE(receiveBuffer.getNumBytes() == 0);
		}

	}

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("INTERMEDIATE MESSAGE RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x2, 0x0, 0x2, 0x1, 0x1, 0x4, 0x43 };

		linkLayerMock.bufferResponse(buffer, sizeof(buffer), true, false);

		ucm.recvOne(receiveBuffer);

		THEN("SHOULD PROCESS INTERMEDIATE")
		{
			REQUIRE(processMessage.intermediateCount == 1);
			REQUIRE(receiveBuffer.getNumBytes() == 0);
		}
	}

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("INVALID MESSAGE RECEIVED")
	{
		ReceiveBuffer receiveBuffer(4096);

		// nonsense message with valid CRC and length
		unsigned char buffer[] = { 0x8, 0x32, 0x0, 0x2, 0x1, 0x1, 0xe2, 0x34 };

		unsigned short checksum = Checksum::calculate(buffer, sizeof(buffer) - 2);

		linkLayerMock.bufferResponse(buffer, sizeof(buffer), false, false);

		ucm.recvOne(receiveBuffer);

		THEN("SHOULD PROCESS INVALID MESSAGE")
		{
			REQUIRE(processMessage.invalidCount == 1);
			REQUIRE(receiveBuffer.getNumBytes() == 0);
		}
	}
}

//======================================================================================


SCENARIO("LinkLayer.QueryMessageTypeSupported")
{
	LinkLayerMock linkLayerMock;

	ProcessMessageMock processMessage;

	CEA2045Device ucm(&linkLayerMock, &processMessage);

	std::future<ResponseCodes> responseCode =
			ucm.queueRequest(new RequestMock(MessageCode::SUPPORT_DATALINK_MESSAGES));

	WHEN("MESSAGE TYPE SUPPORTED SENT")
	{
		SECTION("ACK RECEIVED")
		{
			unsigned char buffer[] = { 0x06, 0x00 };

			linkLayerMock.bufferResponse(buffer, sizeof(buffer), false, false);

			ucm.processNextRequest();

			THEN("SHOULD PROCESS LINK LAYER ACK/NAK")
			{
				REQUIRE(processMessage.ackNakCount == 1);
				REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
				REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::OK);
			}
		}

		// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

		SECTION("NAK RECEIVED")
		{
			unsigned char buffer[] = { 0x15, 0x05 };

			linkLayerMock.bufferResponse(buffer, sizeof(buffer), false, false);

			ucm.processNextRequest();

			THEN("SHOULD PROCESS LINK LAYER ACK/NAK")
			{
				REQUIRE(processMessage.ackNakCount == 1);
				REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);

				ResponseCodes response = responseCode.get();
				REQUIRE(response.responesCode == cea2045::ResponseCode::NAK);
				REQUIRE(response.nak == LinkLayerNakCode::MESSAGE_TIMEOUT);
			}
		}
	}
}

//======================================================================================

SCENARIO("LinkLayer.Timeout")
{
	LinkLayerMock linkLayerMock;

	ProcessMessageMock processMessage;

	// set the receive timeout to 0 to cause the recv loop to timeout
	// on the first call if a complete message isn't received
	CEA2045Device ucm(&linkLayerMock, &processMessage, 0);

	std::future<ResponseCodes> responseCode =
			ucm.queueRequest(new RequestMock(MessageCode::NONE));

	// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

	WHEN("INCOMPLETE MESSAGE RECEIVED")
	{
		unsigned char buffer[] = { 0x8, 0x2, 0x0 };

		linkLayerMock.bufferResponse(buffer, sizeof(buffer));

		ucm.processNextRequest();

		THEN("SHOULD TIMEOUT")
		{
			REQUIRE(processMessage.incompleteCount == 1);
			REQUIRE(responseCode.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
			REQUIRE(responseCode.get().responesCode == cea2045::ResponseCode::TIMEOUT);
		}
	}
}