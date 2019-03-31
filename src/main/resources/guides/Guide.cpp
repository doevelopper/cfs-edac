//at most 85 letters per line
/***********************************************************************************
   This file is part of Project ***
   (brief description on the Project)
   For the latest info, see  WEBSITE_ADDRESS

   Copyright 2016 Yhgenomics

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   : overview of this file
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/16
* Modifed       : When      | Who       | What
                  2016/2/17 | Ke Yang   | Add function A
                  2016/2/17 | Ke Yang   | Refactor the Class add new interfaces
***********************************************************************************/

// Order of includes
// 1. Related header
// 2. C library
// 3. C++ library
// 3. Other libraries' .h
// 4. Your project's .h
#include "Guide.h"

#include <vector>
#include "Nonmembers.h"

using std::vector;

namespace StyleGuide
{
// Description
// Tricky part about the implements
void ClassStyle::Init( int intpuOne, int inputTwo )
{
	// Use lambda expressions where appropriate. Avoid default lambda captures
	// when capturing this or if the lambda will escape the current scope.
	SomeFunction = [ &intpuOne ] ( bool flag )
		       {
			       if ( flag )
			       {
				       return intpuOne + 1;
			       }
		       };
}

// Description
// Tricky part about the implements
int StyleGuide::ClassStyle::CallFunction( int inputOne )
{
	// meaning of the local variables
	int localInt    = inputOne + 1;

	// use 0 for integers,
	int zeroInt     = 0;

	// 0.0 for reals
	double zerodouble  = 0.0;

	// nullptr (or NULL) for pointers
	int *    nullPointer = nullptr;
	double * test        = nullptr;

	// and '\0' for chars.
	char Str1[ 2 ]   = { '\0', '\0' };

	// ues braced initializer list
	vector< int > localVector = { 1, 2, 3, 4, 5 };

	// Description on i if it's not simple
	for ( int i = 0; i < localInt; ++i )
	{
		if ( 0 == i % 2 )
		{
			i += 3;
		}
	}

	// Important Description if needed
	for ( auto item : localVector )
	{
		// do something with item
		// no add or delete on item
	}

	// Important Description if needed
	for ( auto const & item : localVector )
	{
		// [TODO]
		// @role    : Test Group
		// @deadline: 2016/2/18
		// @issue   : done the perfomace test and point out the bottleneck
	}

	// conditions
	bool condition = true;

	// Important Description if needed
	if ( condition )
	{
		// do something
	}
	else if ( condition )
	{
		// do something
	}
	else
	{
		// do something
	}

	int conditionTest = 1;

	// Important Description if needed
	if ( 0 == conditionTest )
	{

	}

	// Important Description if needed
	switch ( conditionTest )
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
	default:
		break;
	}

	return 0;
}
}
