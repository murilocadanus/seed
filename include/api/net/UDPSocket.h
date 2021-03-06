/*
* Copyright (c) 2012, Seed Developers
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 4. A credit line is required in the game credits, as the following line:
*    Powered by Seed Framework
* 5. A Seed Framework logo should be displayed within a splash screen, or in
*    the case where the game haven't or cannot have a splash, a logo should be
*    displayed somewhere in the game (eg. menu, credits, other place).
*
* THIS SOFTWARE IS PROVIDED BY SEED DEVELOPERS ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SEED DEVELOPERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "../../Defines.h"
#include "Address.h"

#if defined(__WINDOWS__)
	#if !defined(_MSC_VER)
		#define NOUSER
	#else
		#define _OLE2_H_ // I love windows _|_
	#endif
#include <winsock2.h>
#undef GetObject
	#if defined(_MSC_VER)
	#pragma comment( lib, "wsock32.lib" )
	#endif
#elif defined(__APPLE_CC__) || defined(__linux__)
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#if defined(__linux__)
#include <unistd.h>
#endif
#endif

namespace Seed { namespace Net
{

class SEED_CORE_API UDPSocket
{
	SEED_DISABLE_COPY(UDPSocket)

	public:
		UDPSocket();
		~UDPSocket();

		bool Open(u32 port);
		void Close();
		bool IsOpen() const;

		bool Send(const Address &destination, const void *data, u32 size);
		u32 Receive(Address &sender, void *data, u32 size);

	private:
		Address cAddress;
		u32 iHandle;
		bool bIsOpen : 1;
};

}} // namespace

#endif // __SOCKET_H__
