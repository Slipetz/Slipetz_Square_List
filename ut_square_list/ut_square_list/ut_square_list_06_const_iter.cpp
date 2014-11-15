/** @file ut_square_list_04_bidirectional_iter.cpp
	@author Garth Santor
	@date 2014-08-06
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> unit test for constant iterators.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <vector>
using std::vector;



/** Test constant iterators */
BOOST_AUTO_TEST_CASE(ut_const_iterator) {
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	square_list<int> sq;
	for (auto e : v)
		sq.insert(e);

	auto csq = ((square_list<int> const&)sq).begin();
	BOOST_CHECK(typeid(csq) == typeid(square_list<int>::const_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, *csq++);
	}
	BOOST_CHECK(csq == ((square_list<int> const&)sq).end());

	auto acsq = sq.cbegin();
	BOOST_CHECK(typeid(acsq) == typeid(square_list<int>::const_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, *acsq++);
	}
	BOOST_CHECK(acsq == sq.cend());
}



/** Test constant iterators */
BOOST_AUTO_TEST_CASE(ut_const_reverse_iterator) {
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
	square_list<int> sq;
	for (auto e : v)
		sq.insert(e);
	std::reverse(v.begin(), v.end());


	auto csq = ((square_list<int> const&)sq).rbegin();
	BOOST_CHECK(typeid(csq) == typeid(square_list<int>::const_reverse_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, *csq++);
	}
	BOOST_CHECK(csq == ((square_list<int> const&)sq).rend());

	auto acsq = sq.crbegin();
	BOOST_CHECK(typeid(acsq) == typeid(square_list<int>::const_reverse_iterator));
	for (auto e : v) {
		BOOST_CHECK_EQUAL(e, *acsq++);
	}
	BOOST_CHECK(acsq == sq.crend());
}

/*============================================================================

Revision History

Version 1.0.0: 2014-08-06

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