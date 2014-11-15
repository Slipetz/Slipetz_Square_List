/**	@file ut_square_list_22_initializer_assignment.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for assignment.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <vector>


#if TEST_PHASE >= 22



/** Test square_list<T>::operator=(std::initializer) */
BOOST_AUTO_TEST_CASE( ut_assignment_initializer_empty ) {
	square_list<double> t;
	t = {};
	BOOST_CHECK( t.empty() );
}



BOOST_AUTO_TEST_CASE( ut_assignment_initializer_empty_to_populated ) {
	square_list<double> s;
	s.insert(3.14);
	BOOST_CHECK( !s.empty() );

	s = {};

	BOOST_CHECK( s.empty() );
}



BOOST_AUTO_TEST_CASE( ut_assignment_initializer_populated_to_empty ) {
	square_list<double> t;

	t = { 1.0, 2.0, 3.0 };
	BOOST_CHECK(!t.empty());
	BOOST_CHECK(t.size() == 3);
}



BOOST_AUTO_TEST_CASE( ut_assignment_initializer_populated_to_populated ) {
	square_list<int> a{ 1, 2, 3, 4, 5 };

	a = { 6, 7, 8, 9 };

	BOOST_CHECK( a.size() == 4 );
	std::vector<int> t{ 6, 7, 8, 9 };
	BOOST_CHECK( std::equal( a.begin(), a.end(), t.begin() ) );
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