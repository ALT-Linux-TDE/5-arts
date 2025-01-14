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

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "object.h"
#include "factory.h"
#include <list>

#include "arts_export.h"

/*
 * BC - Status (2002-03-08): ObjectManager
 *
 * Keep binary compatible (since accessible via ::the()), use d ptr when
 * changing it.
 */

namespace Arts {

class Object;
class ObjectManagerPrivate;

class ARTS_EXPORT ObjectManager {
private:
	ObjectManagerPrivate *d;

protected:
	static ObjectManager *_instance;
	std::list<Factory *> factories;
	std::list<std::string> referenceNames;

public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager *the();
	Object_skel *create(const std::string& name);

	bool addGlobalReference(Object object, const std::string& name);
	std::string getGlobalReference(const std::string& name);
	void removeGlobalReferences();
	void removeExtensions();
	void shutdownExtensions();

	void registerFactory(Factory *factory);
	void removeFactory(Factory *factory);

	void provideCapability(const std::string& capability);
	void removeCapability(const std::string& capability);
};

}

#endif /* OBJECTMANAGER_H */
