    /*

    Copyright (C) 2000-2002 Stefan Westerfeld
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

#ifndef TYPE_H
#define TYPE_H

#include "arts_export.h"
#include "buffer.h"

/*
 * BC - Status (2002-03-08): Type
 *
 * Keep binary compatible. DO NOT TOUCH, DO NOT CHANGE.
 */

namespace Arts {

/**
 * Base class for the IDL mapping of struct-like types
 */
class ARTS_EXPORT Type {
private:
	static long _staticTypeCount;

public:
	inline static long _typeCount() { return _staticTypeCount; }
	/**
	 * constructor
	 */
	inline Type()
	{
		_staticTypeCount++;
	}

	/**
	 * copy constructor
	 */
	inline Type(const Type&)
	{
		_staticTypeCount++;
	}

	/**
	 * virtual destructor (since we have virtual functions and this stuff
	 */
	virtual ~Type();

	/**
	 * read the type from a stream
	 */
	virtual void readType(Buffer& stream) = 0;

	/**
	 * write the type to a stream
	 */
	virtual void writeType(Buffer& stream) const = 0;

	/**
	 * type name
	 */
	virtual std::string _typeName() const = 0;
};

}

#endif
