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

#include "dispatcher.h"
#include "test.h"

using namespace Arts;
using namespace std;

struct TestDispatcher : public TestCase
{
	TESTCASE(TestDispatcher);

	TEST(newDispatcher) {
		for(int i = 0;i < 10; i++) {
			Dispatcher *dispatcher = new Dispatcher();
			delete dispatcher;
		}
	}
};

TESTMAIN(TestDispatcher);
