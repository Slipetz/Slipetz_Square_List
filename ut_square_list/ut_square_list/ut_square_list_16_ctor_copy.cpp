/**	@file ut_square_list_16_ctor_copy.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for a copy constructor.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <vector>



#if TEST_PHASE >= 16

/** Test square_list<T>::square_list(square_list const&) */
BOOST_AUTO_TEST_CASE( ut_ctor_copy_empty ) {
	square_list<double> s;
	decltype(s) copy( s );
	BOOST_CHECK( std::equal( s.begin(), s.end(), copy.begin() ) );
	BOOST_CHECK( copy.empty() );
	BOOST_CHECK( copy.size() == s.size() );
}



BOOST_AUTO_TEST_CASE( ut_ctor_copy_singleton ) {
	square_list<double> s;
	s.insert(3.14);
	decltype(s) copy = s;				// this invokes copy construction

	s.erase( s.begin() );
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == 1 );
	BOOST_CHECK( *copy.begin() == 3.14 );
}



BOOST_AUTO_TEST_CASE( ut_ctor_copy_small ) {
	square_list<double> s;
	for (int i = 0; i < 10; ++i)
		s.insert(i);

	decltype(s) copy( s );
	s.clear();
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == 10 );

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());			
}



BOOST_AUTO_TEST_CASE( ut_ctor_copy_strings ) {
	std::vector<std::string> words{ "one", "two", "three", "four", "five" };
	square_list<std::string> sorted;
	for (auto word : words)
		sorted.insert(word);

	decltype(sorted) copy( sorted );
	BOOST_CHECK( std::equal( sorted.begin(), sorted.end(), copy.begin() ) );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == sorted.size() );

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());			
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