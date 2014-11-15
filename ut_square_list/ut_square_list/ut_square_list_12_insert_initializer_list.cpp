/**	@file ut_square_list_12_insert_initializer_list.cpp
	@author Garth Santor
	@date 2014-08-06
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for inserting an initializer list.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <algorithm>
#include <set>
#include <iostream>
#include <vector>


#if TEST_PHASE >= 12

/** Test square_list<int>::insert() of an initializer list to an empty square list. */
BOOST_AUTO_TEST_CASE( test_insert_initializer_to_empty ) {
#define LIST { 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 }
	std::vector<int> v = LIST;
	square_list<int> sqi;

	sqi.insert({ 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 });
	std::sort( v.begin(), v.end() );

	BOOST_CHECK( sqi.size() == v.size() );
	BOOST_CHECK( std::equal( sqi.begin(), sqi.end(), v.begin() ) );
#undef LIST
}


/** Test square_list<int>::insert() of an initializer list to a populated square list. */
BOOST_AUTO_TEST_CASE( test_insert_initializer_to_populated ) {
#define LISTA { 2, 4, 5, 3 }
#define LISTB { 1, 6 }

	std::vector<int> v = LISTA;
	v.insert(v.begin(),LISTB);
	std::sort(v.begin(), v.end());

	square_list<int> sqi;

	sqi.insert(LISTA);
	sqi.insert(LISTB);

	BOOST_CHECK( sqi.size() == v.size() );
	BOOST_CHECK( std::equal( sqi.begin(), sqi.end(), v.begin() ) );

#undef LISTA
#undef LISTB
}

#endif



/*============================================================================

Revision History

Version 1.0.0: 2014-08-06

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