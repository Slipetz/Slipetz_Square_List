/**	@file ut_square_list_28_equal_range.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 2.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for swap method.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <vector>
using std::vector;


#if TEST_PHASE >= 28


BOOST_AUTO_TEST_CASE(ut_equal_range) {
	vector<int> v{ 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 8, 8 };
	square_list<char> sql(v.begin(), v.end());
	
	auto res = sql.equal_range(0);
	BOOST_CHECK(res.first == sql.cend());
	BOOST_CHECK(res.second == sql.cend());

	res = sql.equal_range(1);
	BOOST_CHECK(res.first == sql.cbegin());
	BOOST_CHECK(std::distance(res.first, res.second) == 2);

	res = sql.equal_range(8);
	BOOST_CHECK(res.first == sql.find(8));
	BOOST_CHECK(res.second == sql.end());
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