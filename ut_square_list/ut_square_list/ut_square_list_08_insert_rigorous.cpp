/** @file ut_square_list_08_insert_rigorous.cpp
	@author Garth Santor
	@date 2014-05-02
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> unit test for reverse iterators.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <iterator>
#include <set>
#include <vector>



#if TEST_PHASE >= 8


/** Test square_list<int>::insert() of a list of scrambled integers. */
BOOST_AUTO_TEST_CASE(ut_insert_scrambled_int) {
	std::vector<int> data{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	square_list<int> sqi;
	for (auto datum : data)
		sqi.insert(datum);

	std::sort(data.begin(), data.end());
	BOOST_CHECK(std::equal(sqi.begin(), sqi.end(), data.begin()));
	BOOST_CHECK(sqi.size() == data.size());
}



BOOST_AUTO_TEST_CASE(ut_insert_big_random_double) {
	std::vector<double> vd;
#if defined(_DEBUG)
	size_t limit = 100000;
#else
	size_t limit = 1000;
#endif
	double low = -20;
	for (size_t i = 0; i < limit; ++i)
		vd.push_back(low += 0.5);
	std::random_shuffle(vd.begin(), vd.end());

	square_list<double> sqd;
	for (auto v : vd)
		sqd.insert(v);
	std::sort(vd.begin(), vd.end());
	BOOST_CHECK(std::equal(sqd.begin(), sqd.end(), vd.begin()));
	BOOST_CHECK(sqd.size() == vd.size());
}



/** Test square_list<int>::insert() of a list of ramped integers. */
BOOST_AUTO_TEST_CASE(ut_insert_ramped_int) {
	square_list<size_t> sqi;
	size_t limit = 1000;
	for (size_t i = 0; i < limit; ++i)
		sqi.insert(i);


	BOOST_CHECK(sqi.size() == limit);
	int n = 0;
	for (auto x : sqi) {
		BOOST_CHECK_EQUAL(x, n);
		++n;
	}
}



/** Test square_list<int>::insert() of a list of reversed integers. */
BOOST_AUTO_TEST_CASE(ut_insert_reversed_int) {
	square_list<size_t> sqi;
	size_t limit = 1000;
	for (size_t i = 1000; i > 0; --i)
		sqi.insert(i);

	BOOST_CHECK(sqi.size() == limit);
	int n = 1;
	for (auto x : sqi) {
		BOOST_CHECK_EQUAL(x, n);
		++n;
	}
}



/** Test square_list<int>::insert() of a list of identical integers. */
BOOST_AUTO_TEST_CASE(ut_insert_identical_integers) {
	double const value = 2.3;
	square_list<double> sqd;
	size_t limit = 16;
	for (size_t i = 0; i < limit; ++i)
		sqd.insert(value);

	BOOST_CHECK(sqd.size() == limit);
	for (auto x : sqd) {
		BOOST_CHECK_EQUAL(x, value);
	}
}



#endif // TEST_PHASE 8


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