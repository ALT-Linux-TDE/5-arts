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

#ifndef STDSYNTHMODULE_H
#define STDSYNTHMODULE_H

#include "arts_export.h"
#include "artsflow.h"

/*
 * BC - Status (2002-03-08): StdSynthModule
 *
 * This class is intended for public use (inheritance) as it supplies a base
 * for all objects using streams. It will be kept binary compatible.
 */

namespace Arts {

class StdSynthModulePrivate;

class ARTS_EXPORT StdSynthModule : virtual public SynthModule_base {
private:
	StdSynthModulePrivate *d;

protected:
	long samplingRate;
	float samplingRateFloat;

public:
	StdSynthModule();

	void start();
	void stop();

	void streamInit();
	void streamStart();
	void streamEnd();

	AutoSuspendState autoSuspend();

	unsigned long inputConnectionCount(const std::string& portname);
	unsigned long outputConnectionCount(const std::string& portname);
	bool connectionCountChanged();
};
}
#endif /* STDSYNTHMODULE_H */
