/**	@file ut_square_list_25_count.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 2.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for swap method.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>


#if TEST_PHASE >= 25

/** Test square_list<T>::count() */
BOOST_AUTO_TEST_CASE( ut_count_empty ) {
	square_list<char> a;

	BOOST_CHECK(a.count('a') == 0);
}


BOOST_AUTO_TEST_CASE(ut_count_singleton) {
	square_list<int> sq{ 1 };
	BOOST_CHECK(sq.count(1) == 1);
	BOOST_CHECK(sq.count(2) == 0);
}


BOOST_AUTO_TEST_CASE(ut_count_all_same) {
	square_list<int> sq{ 2, 2, 2, 2, 2 };
	BOOST_CHECK(sq.count(1) == 0);
	BOOST_CHECK(sq.count(2) == sq.size());
}


BOOST_AUTO_TEST_CASE(ut_count_mixed) {
	square_list<int> sq{ 1, 1, 1, 2, 3, 4, 5, 6, 6, 6, 7, 7, 8, 9, 9, 9 };
	BOOST_CHECK(sq.count(1) == 3);
	BOOST_CHECK(sq.count(2) == 1);
	BOOST_CHECK(sq.count(6) == 3);
	BOOST_CHECK(sq.count(7) == 2);
	BOOST_CHECK(sq.count(9) == 3);
	BOOST_CHECK(sq.count(10) == 0);
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