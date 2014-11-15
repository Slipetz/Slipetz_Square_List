/** @file ut_square_list_07_erase_concept.cpp
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
#include <iostream>



#if TEST_PHASE >= 7


/** Test square_list<int>::erase() of a list of scrambled integers. */
BOOST_AUTO_TEST_CASE(ut_erase_scrambled_int) {
	std::vector<int> data{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	std::set<int> sortedData(data.begin(), data.end());


	square_list<int> sqi;
	for (auto datum : data)
		sqi.insert(datum);

	// remove the data from the list in the scrambled order of the first vector.
	while (!sqi.empty() && !sortedData.empty()) {
		size_t idx = rand() % sqi.size();
		auto sdLoc = sortedData.begin();
		std::advance(sdLoc, idx);
		auto sqLoc = sqi.begin();
		while (idx-- > 0)
			++sqLoc;

		sortedData.erase(sdLoc);
		sqi.erase(sqLoc);
		BOOST_CHECK(std::equal(sqi.begin(), sqi.end(), sortedData.begin()));
		BOOST_CHECK(sqi.size() == sortedData.size());
	}
	BOOST_CHECK(sqi.empty());
	BOOST_CHECK(sortedData.empty());
}



/** Test square_list<int>::erase() front to back */
BOOST_AUTO_TEST_CASE(ut_erase_ramped_int) {
	square_list<size_t> sqi;
	std::set<size_t> si;

	size_t limit = 1000;
	for (size_t i = 0; i < limit; ++i) {
		sqi.insert(i);
		si.insert(i);
	}

	do {
		BOOST_CHECK(std::equal(sqi.begin(), sqi.end(), si.begin()));
		BOOST_CHECK(sqi.size() == si.size());
		sqi.erase(sqi.begin());
		si.erase(si.begin());
	} while (!sqi.empty() && !si.empty());
}


/** Test square_list<int>::erase() back to front. */
BOOST_AUTO_TEST_CASE(ut_erase_reversed_int) {
	square_list<size_t> sqi;
	std::set<size_t> si;

	size_t limit = 1000;
	for (size_t i = 0; i < limit; ++i) {
		sqi.insert(i);
		si.insert(i);
	}

	do {
		BOOST_CHECK(std::equal(sqi.begin(), sqi.end(), si.begin()));
		BOOST_CHECK(sqi.size() == si.size());
		auto sqLoc = sqi.end();
		auto siLoc = si.end();
		--sqLoc;
		--siLoc;
		sqi.erase(sqLoc);
		si.erase(siLoc);
	} while (!sqi.empty() && !si.empty());
}


BOOST_AUTO_TEST_CASE(ut_erase_big_random_double) {
#if defined(NDEBUG)
	size_t limit = 100000;
#else
	size_t limit = 1000;
#endif


	std::set<double> sortedData;
	double x = -20.0;
	square_list<double> sqd;
	for (size_t i = 0; i < limit; ++i) {
		sortedData.insert(x);
		sqd.insert(x);
		x += 0.5;
	}

	// remove the data from the list in the scrambled order of the first vector.
	while (!sqd.empty() && !sortedData.empty()) {
		size_t n = sqd.size();
		size_t idx = rand() % sqd.size();
		auto sdLoc = sortedData.begin();
		advance(sdLoc, idx);
		auto sqLoc = sqd.begin();
		std::advance(sqLoc, idx);

#if defined(NDEBUG)
		if (sqd.size() % 5000 == 0)
			std::cout << "Size = " << sqd.size() << std::endl;
#endif

		sortedData.erase(sdLoc);
		sqd.erase(sqLoc);
		BOOST_CHECK(std::equal(sqd.begin(), sqd.end(), sortedData.begin()));
		BOOST_CHECK_EQUAL(sqd.size(), sortedData.size());
	}
	BOOST_CHECK(sqd.empty());
	BOOST_CHECK(sortedData.empty());
}


#endif // TEST_PHASE 7


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