/** @file ut_square_list_10_insert_rvalue.cpp
	@author Garth Santor
	@date 2014-08-06
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> unit test for R-value insert method.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <iterator>
#include <memory>
#include <set>
#include <vector>



#if TEST_PHASE >= 10


/** Test square_list<int>::insert() of a list of scrambled integers. */
BOOST_AUTO_TEST_CASE(ut_Rvalue_insert_scrambled_int) {
	typedef std::unique_ptr<int> UP;
	std::vector<int> data{ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	square_list<UP> sqi;
	for (auto datum : data) {
		sqi.insert(UP(new int(datum)));
	}

	std::sort(data.begin(), data.end());
	std::vector<int> dup;
	for (auto iter = sqi.begin(); iter != sqi.end(); ++iter) {
		dup.push_back(*iter->get());
	}

	std::sort(data.begin(), data.end());
	std::sort(dup.begin(), dup.end());
	BOOST_CHECK(dup.size() == data.size());
	BOOST_CHECK_EQUAL_COLLECTIONS(dup.begin(), dup.end(), data.begin(), data.end());
}


#endif


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