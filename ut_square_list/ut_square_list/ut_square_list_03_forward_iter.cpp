/** @file ut_square_list_03_forward_iter.cpp
@author Garth Santor
@date 2014-07-25
@version 1.0.0
@note C++ 11/vc12
@brief square_list<> unit test for forward iterators.
*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <vector>
using std::vector;


#if TEST_PHASE >= 3



/** Test square_list<>::begin, end, empty constructor */
BOOST_AUTO_TEST_CASE(ut_forward_iterator_empty) {
	square_list<int> di;
	BOOST_CHECK(di.size() == 0);
	BOOST_CHECK(di.empty());
	BOOST_CHECK(di.begin() == di.end());
}



/** Test square_list<>::iterator single element */
BOOST_AUTO_TEST_CASE(ut_forward_iterator_one) {
	square_list<int> di;
	di.insert(1);
	BOOST_CHECK(di.size() == 1);
	BOOST_CHECK(!di.empty());
	
	auto p = di.begin();
	BOOST_CHECK(p != di.end());
	BOOST_CHECK_EQUAL(*p, 1);
}



/** Test square_list<>::iterator for forward iteration */
BOOST_AUTO_TEST_CASE(ut_forward_iterator_loop) {
	size_t limit = 33;
	vector<size_t> v;
	square_list<size_t> sl;


	BOOST_CHECK(sl.empty());
	for (size_t i = 0; i < limit; ++i) {
		v.push_back(i);
		sl.insert(i);
		BOOST_CHECK_EQUAL(sl.size(), v.size());

		// check the full list using post-increment
		auto slp = sl.begin();
		auto vlp = v.begin();
		while (slp != sl.end()) {
			BOOST_CHECK(vlp != v.end());
			auto lhs = *slp++;
			auto rhs = *vlp++;
			BOOST_CHECK_EQUAL(lhs,rhs);
		}
		BOOST_CHECK(slp == sl.end());

		slp = sl.begin();
		vlp = v.begin();
		for (size_t i = 1; i < v.size(); ++i) {
			BOOST_CHECK_EQUAL(*(++slp), *(++vlp));
		}
		BOOST_CHECK(++slp == sl.end());
	}
}



#endif // TEST_PHASE 3


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