/**	@file ut_square_list_21_move_assignment.cpp
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



#if TEST_PHASE >= 21



/** Test square_list<T>::operator=(&&) */
BOOST_AUTO_TEST_CASE( ut_assignment_move_empty ) {
	square_list<double> s, t;
	t = std::move(s);
	BOOST_CHECK( std::equal( s.begin(), s.end(), t.begin() ) );
	BOOST_CHECK( t.empty() );
	BOOST_CHECK( t.size() == s.size() );
}



BOOST_AUTO_TEST_CASE( ut_assignment_move_empty_to_populated ) {
	square_list<double> s, t;
	BOOST_CHECK( t.empty() );
	s.insert(3.14);
	BOOST_CHECK( !s.empty() );

	s = std::move(t);

	BOOST_CHECK( s.empty() );
	BOOST_CHECK( t.empty() );
}



BOOST_AUTO_TEST_CASE( ut_assignment_move_populated_to_empty ) {
	square_list<double> s, t;
	for (int i = 0; i < 10; ++i)
		s.insert(i);

	t = std::move(s);
	BOOST_CHECK( s.empty() );
	BOOST_CHECK( !t.empty() );
	BOOST_CHECK( t.size() == 10 );

	// this should crash if you didn't write your copy constructor properly
	while (!t.empty())
		t.erase(t.begin());			
}



BOOST_AUTO_TEST_CASE( ut_assignment_populated_to_populated ) {
	square_list<char> a, b;

	std::string s = "abcde", t = "fghi";
	for (auto ch : s)
		a.insert(ch);
	for (auto ch : t)
		b.insert(ch);

	BOOST_CHECK( a.size() == s.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), s.begin() ) );

	BOOST_CHECK( b.size() == t.size() );
	BOOST_CHECK( std::equal( b.begin(), b.end(), t.begin() ) );

	a = std::move(b);

	BOOST_CHECK( a.size() == t.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), t.begin() ) );

	BOOST_CHECK( b.empty() );
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