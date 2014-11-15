/** @file ut_square_list_04_bidirectional_iter.cpp
	@author Garth Santor
	@date 2014-05-02
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> unit test for bidirectional iterators.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <vector>
using std::vector;



#if TEST_PHASE >= 4



/** Test square_list<>::difference_type */
BOOST_AUTO_TEST_CASE(ut_types_difference_type) {
	BOOST_CHECK(typeid(square_list<double>::difference_type) == typeid(std::ptrdiff_t));
	BOOST_CHECK(typeid(square_list<std::string>::difference_type) == typeid(std::ptrdiff_t));
}



/** Test bidirectional iterators */
BOOST_AUTO_TEST_CASE(ut_bidirectional_iterator) {
	size_t limit = 33;
	vector<size_t> v;
	square_list<size_t> sl;


	BOOST_CHECK(sl.empty());
	for (size_t i = 0; i < limit; ++i) {
		v.push_back(i);
		sl.insert(i);
		BOOST_CHECK_EQUAL(sl.size(), v.size());

		// check the full list using post-increment
		auto slp = sl.end();
		auto vlp = v.end();
		while (slp != sl.begin()) {
			BOOST_CHECK(vlp != v.begin());
			auto lhs = *--slp;
			auto rhs = *--vlp;
			BOOST_CHECK_EQUAL(lhs, rhs);
		}
		BOOST_CHECK(slp == sl.begin());

		slp = --sl.end();
		vlp = --v.end();
		while (slp != sl.begin()) {
			BOOST_CHECK_EQUAL(*slp--, *vlp--);
		}
		BOOST_CHECK(slp == sl.begin());
		BOOST_CHECK(std::distance(sl.begin(), sl.end()) == sl.size());
	}
}



#endif // TEST_PHASE 4



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