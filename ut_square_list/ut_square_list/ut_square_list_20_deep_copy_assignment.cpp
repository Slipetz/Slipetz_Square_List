/**	@file ut_square_list_20_deep_copy_assignment.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for assignment.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <type_traits>
#include <array>



#if TEST_PHASE >= 20

/** Test square_list<T>::operator=() */
BOOST_AUTO_TEST_CASE( ut_copy_assignment_empty ) {
	square_list<double> s, t;
	t = s;
	BOOST_CHECK( std::equal( s.begin(), s.end(), t.begin() ) );
	BOOST_CHECK( t.empty() );
	BOOST_CHECK( t.size() == s.size() );
}



BOOST_AUTO_TEST_CASE( ut_copy_assignment_singleton ) {
	square_list<double> s, t;
	s.insert(3.14);
	t = s;

	s.erase( s.begin() );
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !t.empty() );
	BOOST_CHECK( t.size() == 1 );
	BOOST_CHECK( *t.begin() == 3.14 );

}



BOOST_AUTO_TEST_CASE( ut_copy_assignment_small ) {
	square_list<double> s, t;
	for (int i = 0; i < 10; ++i)
		s.insert(i);

	t = s;
	s.clear();
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !t.empty() );
	BOOST_CHECK( t.size() == 10 );

	// this should crash if you didn't write your copy constructor properly
	while (!t.empty())
		t.erase(t.begin());			
}



BOOST_AUTO_TEST_CASE( ut_copy_assignment_strings ) {
	std::array<std::string,5> words = { "one", "two", "three", "four", "five" };
	square_list<std::string> sorted, copy;
	for (auto word : words)
		sorted.insert(word);

	copy = sorted;
	BOOST_CHECK( std::equal( sorted.begin(), sorted.end(), copy.begin() ) );
	BOOST_CHECK( !copy.empty() );
	BOOST_CHECK( copy.size() == sorted.size() );
	sorted.clear();

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