/**	@file ut_square_list_09_clear.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for vc11
	@brief square_list<> unit test for clear method.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <type_traits>

#if TEST_PHASE >= 9


/** Test square_list<T>::clear() */
BOOST_AUTO_TEST_CASE( ut_clear ) {
	square_list<double> d;
	BOOST_CHECK( d.empty() );
	BOOST_CHECK( d.size() == 0 );
	BOOST_CHECK( d.begin() == d.end() );

	for (double x = 0; x < 10; ++x)
		d.insert(x);

	BOOST_CHECK( !d.empty() );
	BOOST_CHECK( d.size() == 10 );
	BOOST_CHECK( d.begin() != d.end() );

	d.clear();
	BOOST_CHECK( d.empty() );
	BOOST_CHECK( d.size() == 0 );
	BOOST_CHECK( d.begin() == d.end() );
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