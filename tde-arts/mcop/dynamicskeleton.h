    /*

    Copyright (C) 2001 Stefan Westerfeld
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

#ifndef ARTS_MCOP_DYNAMICSKELETON_H
#define ARTS_MCOP_DYNAMICSKELETON_H

#include "arts_export.h"

#include "object.h"

/*
 * BC - Status (2002-03-08): DynamicSkeletonBase, DynamicSkeleton
 *
 * Will be kept binary compatible (using d ptr).
 */
namespace Arts {

class DynamicSkeletonData;

class ARTS_EXPORT DynamicSkeletonBase {
private:
	DynamicSkeletonData *d;

protected:
	DynamicSkeletonBase();
	/* <obsolete compatibility code> */
	DynamicSkeletonBase(Object_skel *skel,
			    const std::string& interfacename,
			    const std::string& interfacenameparent);
	/* </obsolete compatibility code> */
	virtual ~DynamicSkeletonBase();

	void _dsInit(Object_skel *skel, const std::string& interfacename,
									   const std::string& interfacenameparent);
	std::string _dsInterfaceName();
	bool _dsIsCompatibleWith(const std::string& interfacename);
	void _dsBuildMethodTable();

public:
	/**
	 * process is called whenever you get a request that you need to implement
	 * dynamically
	 *
	 * @param methodID contains the ID of the method that you need to
	 *                 implement - you can get the full signature by calling
	 *                 getMethodDef
	 *
	 * @param request  contains the marshalled parameters
	 *
	 * @param result   is for the return code - if your method returns a
	 *                 value, you need to write the it in the result Buffer
	 */
	virtual void process(long methodID, Buffer *request, Buffer *result) = 0;
};

/**
 * DynamicSkeleton is used to dynamically implement an interface (i.e. without
 * static type bindings as generated by the MCOP idl compiler.
 *
 * You will always implement a mixed version: mcopidl generated skeletons up
 * to a certain point, and above this, dynamically implemented interfaces.
 * So you'll inherit DynamicSkeleton<Static_skel> and give the interface you
 * want to implement dynamically as argument. Suppose your idl file looks
 * like
 *
 * <pre>
 * interface A { void a(); };
 * interface B : A { void b(); };
 * </pre>
 *
 * And you want to implement interface A "classic" (i.e. with mcopidl generated
 * virtual void a()) and interface B "dynamic", you would do
 *
 * <pre>
 * typedef Arts::DynamicSkeleton<A_skel> A_dskel;   // convenient with typedef
 *
 * class B_impl : public A_dskel {
 * public:
 *   B_impl() : A_dskel("B") {  // we dynamically implement the B interface
 *   }
 *   void a() { // through A_skel
 *     arts_info("a called");
 *   }
 *   void process(long methodID, Arts::Buffer *request, Arts::Buffer *result)
 *   {
 *	   const Arts::MethodDef& methodDef = getMethodDef(methodID);
 *	 
 *	   if(methodDef.name == "b")
 *	     arts_info("b called!");
 *	   else
 *	     arts_fatal("Unknown method '%s' called");
 *	 }
 * };
 * </pre>
 */
template<class Parent_skel>
class DynamicSkeleton : virtual public Parent_skel, public DynamicSkeletonBase
{
public:
	/**
	 * constructor
	 */
	DynamicSkeleton(const std::string& interface)
	{
		_dsInit(this, interface, Parent_skel::_interfaceNameSkel());
	}

	/**
	 * getMethodDef returns a MethodDef structure for a given methodID - it
	 * is quite useful if you implement process
	 *
	 * <pre>
	 * void process(long methodID, Arts::Buffer *request, Arts::Buffer *result)
	 * {
	 *   const Arts::MethodDef& methodDef = getMethodDef(methodID);
	 * 
	 *	 if(methodDef.name == "hello") // the method named hello was called
	 *	   printf("Hello!\n");
	 *	 else                          // method with other name was called
	 *	   arts_fatal("Method '%s' not implemented",methodDef.name.c_str());
	 * }
	 * </pre>
	 */
	const MethodDef& getMethodDef(long methodID) {
		return this->_dsGetMethodDef(methodID);
	}

/*-- reimplemented from Arts::Object_skel: --*/
	std::string _interfaceName() {
		return _dsInterfaceName();
	}

	bool _isCompatibleWith(const std::string& interfacename) {
		if(_dsIsCompatibleWith(interfacename)) return true;
		return Parent_skel::_isCompatibleWith(interfacename);
	}
	void _buildMethodTable() {
		Parent_skel::_buildMethodTable();
		_dsBuildMethodTable();
	}
};

}
#endif /* ARTS_MCOP_DYNAMICSKELETON_H */
