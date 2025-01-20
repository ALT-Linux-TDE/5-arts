    /*

    Copyright (C) 2000 Stefan Westerfeld
                       stefan@space.twc.de

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
  
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
   
    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

    */

#include "loopback.h"
#include "common.h"

using namespace Arts;
using namespace std;

LoopbackConnection::LoopbackConnection(const std::string& serverID)
{
	setServerID(serverID);
	_connState = established;
}

void LoopbackConnection::qSendBuffer(Buffer *buffer)
{
	assert(buffer->size() >= 12);

	long magic = buffer->readLong();
	assert(magic == MCOP_MAGIC);

	/* messageSize, irrelevant here, since we've got the buffer already */
	buffer->readLong();	
	long messageType = buffer->readLong();

	Dispatcher::the()->handle(this,buffer,messageType);
}

void LoopbackConnection::drop()
{
	assert(false);
}

bool LoopbackConnection::broken()
{
	return false;
}