/**	@file ut_square_list_23_relational.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for typedefs.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <vector>
using std::vector;



#if TEST_PHASE >= 23


BOOST_AUTO_TEST_CASE( test_compare_equal ) {
	vector<int> values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	square_list<int> lhs(values.begin(), values.end());
	auto rhs(lhs);

	BOOST_CHECK(lhs == rhs);
	BOOST_CHECK(lhs <= rhs);
	BOOST_CHECK(lhs >= rhs);
}



BOOST_AUTO_TEST_CASE( test_compare_not_equal ) {
	vector<int> values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	square_list<int> lhs(values.begin(), values.end());
	auto rhs(lhs);

	lhs.erase(--lhs.end());
	BOOST_CHECK( lhs != rhs );
	lhs.insert(9);
	BOOST_CHECK( lhs == rhs );
	lhs.insert(10);
	BOOST_CHECK( lhs != rhs );
	rhs.insert(11);
	BOOST_CHECK( lhs != rhs );
}



BOOST_AUTO_TEST_CASE(test_compare_diff) {
	square_list<int> a{ 1, 2, 2, 4, 5 };
	square_list<int> b{ 1, 2, 3, 4, 5 };

	BOOST_CHECK(a < b);
	BOOST_CHECK(a <= b);
	BOOST_CHECK(b > a);
	BOOST_CHECK(b >= a);
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