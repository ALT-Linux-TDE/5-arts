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

/*
 * BC - Status (2002-03-08): SocketConnection
 *
 * None of these classes is considered part of the public API. Do NOT use it
 * in your apps. No BC guaranteed.
 */

#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include "buffer.h"
#include "iomanager.h"
#include "connection.h"
#include <list>
#include <string>

namespace Arts {

class SocketConnection :public Connection, public IONotify {
protected:
	std::string serverID;
	int fd;
	bool _broken;

	std::list<Buffer *> pending;
	void writeBuffer(Buffer *buffer);

	SocketConnection();

public:
	SocketConnection(int _fd);

	void qSendBuffer(Buffer *buffer);
	void notifyIO(int _fd, int types);

	void drop();
	bool broken();
};

}

#endif /* SOCKETCONNECTION_H */
