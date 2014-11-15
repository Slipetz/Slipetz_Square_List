/** @file ut_square_list_05_reverse_iter.cpp
	@author Garth Santor
	@date 2014-05-02
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> unit test for reverse iterators.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <iterator>
#include <vector>
using std::vector;


#if TEST_PHASE >= 5



/** Test square_list<>::reverse_iterator */
BOOST_AUTO_TEST_CASE(ut_types_reverse_iterator_type) {
	BOOST_CHECK(typeid(square_list<double>::reverse_iterator::value_type) == typeid(double));
	BOOST_CHECK(typeid(square_list<std::string>::reverse_iterator::value_type) == typeid(std::string));
}



BOOST_AUTO_TEST_CASE(ut_reverse_iterator_category) {
	BOOST_CHECK(typeid(std::iterator_traits<square_list<double>::reverse_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag));
	BOOST_CHECK(typeid(std::iterator_traits<square_list<long>::reverse_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag));
}



/** Test square_list<>::rbegin, rend */
BOOST_AUTO_TEST_CASE(ut_reverse_iterator_empty) {
	square_list<int> di;
	BOOST_CHECK(di.size() == 0);
	BOOST_CHECK(di.empty());
	BOOST_CHECK(di.rbegin() == di.rend());
}



/** Test square_list<>::reverse_iterator single element */
BOOST_AUTO_TEST_CASE(ut_reverse_iterator_one) {
	square_list<int> sl;
	sl.insert(1);
	BOOST_CHECK(sl.size() == 1);
	BOOST_CHECK(!sl.empty());

	auto p = sl.rbegin();
	BOOST_CHECK(p != sl.rend());
	BOOST_CHECK_EQUAL(*p, 1);
}



/** Test square_list<>::reverse_iterator using increment operators */
BOOST_AUTO_TEST_CASE(ut_reverse_iterator_increment) {
	size_t limit = 33;
	vector<size_t> v;
	square_list<size_t> sl;


	BOOST_CHECK(sl.empty());
	for (size_t i = 0; i < limit; ++i) {
		v.push_back(i);
		sl.insert(i);
		BOOST_CHECK_EQUAL(sl.size(), v.size());

		// check the full list using post-increment
		auto slp = sl.rbegin();
		auto vlp = v.rbegin();
		while (slp != sl.rend()) {
			BOOST_CHECK(vlp != v.rend());
			auto lhs = *slp++;
			auto rhs = *vlp++;
			BOOST_CHECK_EQUAL(lhs, rhs);
		}
		BOOST_CHECK(slp == sl.rend());

		slp = sl.rbegin();
		vlp = v.rbegin();
		for (size_t i = 1; i < v.size(); ++i) {
			BOOST_CHECK_EQUAL(*(++slp), *(++vlp));
		}
		BOOST_CHECK(++slp == sl.rend());
		BOOST_CHECK(std::distance(sl.rbegin(), sl.rend()) == sl.size());
	}
}



/** Test square_list<>::reverse_iterator using decrement operators */
BOOST_AUTO_TEST_CASE(ut_reverse_iterator_decrement) {
	size_t limit = 33;
	vector<size_t> v;
	square_list<size_t> sl;


	BOOST_CHECK(sl.empty());
	for (size_t i = 0; i < limit; ++i) {
		v.push_back(i);
		sl.insert(i);
		BOOST_CHECK_EQUAL(sl.size(), v.size());

		// check the full list using post-increment
		auto slp = sl.rend();
		auto vlp = v.rend();
		while (slp != sl.rbegin()) {
			BOOST_CHECK(vlp != v.rbegin());
			auto lhs = *--slp;
			auto rhs = *--vlp;
			BOOST_CHECK_EQUAL(lhs, rhs);
		}
		BOOST_CHECK(slp == sl.rbegin());

		slp = --sl.rend();
		vlp = --v.rend();
		while (slp != sl.rbegin()) {
			BOOST_CHECK_EQUAL(*slp--, *vlp--);
		}
		BOOST_CHECK(slp == sl.rbegin());
		BOOST_CHECK(std::distance(sl.rbegin(), sl.rend()) == sl.size());
	}
}



#endif // TEST_PHASE 6


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