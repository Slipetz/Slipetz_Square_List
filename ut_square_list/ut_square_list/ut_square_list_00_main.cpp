/** @file ut_square_list_00_main.cpp
	@author Garth Santor
	@date 2014-05-02
	@version 1.0.0
	@note C++ 11/vc12
	@brief dynarray<> unit test main module.
*/

#define BOOST_TEST_MODULE square_list_unit_test
#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include <iomanip>
using namespace std;
#include "ut_square_list.hpp"
#include "compiler.hpp"


/** Unit test build info. */
BOOST_AUTO_TEST_CASE(ut_build_info) {
	double mscVersion = _MSC_VER / 100.0;
	cout << "ut-square_list<> version " UT_VERSION "\n"
		"TEST PHASE = " << TEST_PHASE << "\n"
		"MSC Version: " << fixed << setprecision(2) << mscVersion << " -> " __GATS_BUILD_TYPE__ "\n"
		"Last Build: " __DATE__ " - "__TIME__ "\n" << endl;
}


/*============================================================================

Revision History

Version 1.0.0: 2014-05-02

==============================================================================
Copyright Garth Santor, 2014

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/