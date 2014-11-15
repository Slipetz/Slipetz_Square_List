/** @file ut_square_list_02_capacity.cpp
@author Garth Santor
@date 2014-05-02
@version 1.0.0
@note C++ 11/vc12
@brief square_list<> unit test for capacity methods.
*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>


#if TEST_PHASE >= 2



/** Test square_list<>::size_type */
BOOST_AUTO_TEST_CASE(ut_concept_size_type) {

	typedef square_list<double>::size_type DST;
	BOOST_CHECK(!std::is_floating_point<DST>());
	BOOST_CHECK(std::is_unsigned<DST>());
	BOOST_CHECK(std::is_integral<DST>());

	typedef square_list<std::string>::size_type SST;
	BOOST_CHECK(!std::is_floating_point<SST>());
	BOOST_CHECK(std::is_unsigned<SST>());
	BOOST_CHECK(std::is_integral<SST>());
}



/** Test square_list<>::empty */
BOOST_AUTO_TEST_CASE(ut_capacity_empty) {

	square_list<int> di;
	BOOST_CHECK(di.empty());
	di.insert(42);
	BOOST_CHECK(!di.empty());

	square_list<double> dd;
	BOOST_CHECK(dd.empty());
	dd.insert(42.1);
	BOOST_CHECK(!dd.empty());
}



/** Test square_list<>::size */
BOOST_AUTO_TEST_CASE(ut_capacity_size) {
	square_list<int>::size_type limit = 100;
	square_list<int> di;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(di.size(), i);
		di.insert(i);
	}

	square_list<double> dd;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(dd.size(), i);
		dd.insert(i);
	}

	square_list<std::string> ds;
	for (decltype(limit) i = 0; i < limit; ++i) {
		BOOST_CHECK_EQUAL(ds.size(), i);
		ds.insert(std::string(i, 'a'));
	}
}



/** Test square_list<>::max_size */
BOOST_AUTO_TEST_CASE(ut_capacity_max_size) {
	
	square_list<int> di;
	BOOST_CHECK(di.max_size() == std::numeric_limits<decltype(di)::size_type>::max());

	square_list<double> dd;
	BOOST_CHECK(dd.max_size() == std::numeric_limits<decltype(dd)::size_type>::max());

	square_list<float> df;
	BOOST_CHECK(df.max_size() == std::numeric_limits<decltype(df)::size_type>::max());

	square_list<std::string> ds;
	BOOST_CHECK(ds.max_size() == std::numeric_limits<decltype(ds)::size_type>::max());
}



#endif // TEST_PHASE 2



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