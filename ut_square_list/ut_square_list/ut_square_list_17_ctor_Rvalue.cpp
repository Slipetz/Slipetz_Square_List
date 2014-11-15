/**	@file ut_square_list_17_ctor_Rvalue.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for an R-value constructor.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <vector>



#if TEST_PHASE >= 17

/** Test square_list<T>::square_list(square_list &&) */
BOOST_AUTO_TEST_CASE( ut_ctor_Rvalue_empty ) {
	square_list<double> s;
	decltype(s) copy( std::move(s) );
	BOOST_CHECK(s.empty());
	BOOST_CHECK( std::equal( s.begin(), s.end(), copy.begin() ) );
	BOOST_CHECK( copy.empty() );
	BOOST_CHECK( copy.size() == s.size() );
}



BOOST_AUTO_TEST_CASE( ut_ctor_Rvalue_singleton ) {
	square_list<double> s;
	s.insert(3.14);
	decltype(s) copy = std::move(s);				// this invokes copy construction

	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == 1 );
	BOOST_CHECK( *copy.begin() == 3.14 );
}



BOOST_AUTO_TEST_CASE( ut_ctor_Rvalue_small ) {
	square_list<double> s;
	for (int i = 0; i < 10; ++i)
		s.insert(i);

	decltype(s) copy( std::move(s) );
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == 10 );

	// this should crash if you didn't write your copy constructor properly
	while (!copy.empty())
		copy.erase(copy.begin());			
}



BOOST_AUTO_TEST_CASE( ut_ctor_Rvalue_strings ) {
	std::vector<std::string> words{ "one", "two", "three", "four", "five" };
	square_list<std::string> sorted;
	for (auto word : words)
		sorted.insert(word);

	std::sort(words.begin(), words.end());
	decltype(sorted) copy( std::move(sorted) );
	BOOST_CHECK(sorted.empty());
	BOOST_CHECK( std::equal( words.begin(), words.end(), copy.begin() ) );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == words.size() );

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