/**	@file ut_square_list_26_front_back.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 2.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for swap method.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>


#if TEST_PHASE >= 26

/** Test square_list<T>::front() */
BOOST_AUTO_TEST_CASE(ut_front_back_singleton) {
	square_list<int> sq{ 1 };
	BOOST_CHECK_EQUAL(sq.front(), 1);
	BOOST_CHECK_EQUAL(sq.back(), 1);
}


BOOST_AUTO_TEST_CASE(ut_front_back_multi) {
	square_list<int> sq{ 1, 2 };
	BOOST_CHECK_EQUAL(sq.front(), 1);
	BOOST_CHECK_EQUAL(sq.back(), 2);
}


#endif



/*============================================================================

Revision History

Version 1.0.0: 2013-12-30

Version 0.0.0: 2006-10-16

==============================================================================
Copyright Garth Santor, 2006-2014

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/