/**	@file ut_square_list_29_ctor_compare.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for compare constructors.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <vector>
using std::vector;

#if TEST_PHASE >= 29

template <class T>
class RuntimeCmp
{
public:
	enum cmp_mode { normal, reverse };
private:
	cmp_mode mode;
public:
	RuntimeCmp( cmp_mode m = normal ) : mode(m) { }
	bool operator()(T const& t1, T const& t2) const { return mode == normal ? t1 < t2 : t2 < t1; }
	bool operator==( RuntimeCmp const& rc ) { return mode == rc.mode; }
};



/** Test square_list<T>::square_list() */
BOOST_AUTO_TEST_CASE( ut_ctor_compare_def ) {
	square_list<double,RuntimeCmp<double>> s;
	vector<double> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	for (auto x : data)
		s.insert(x);

	BOOST_CHECK( std::equal( s.begin(), s.end(), data.begin() ) );
}



BOOST_AUTO_TEST_CASE( ut_ctor_compare_passed ) {
	RuntimeCmp<double> rc(RuntimeCmp<double>::reverse);
	square_list<double,RuntimeCmp<double>> s(rc);
	vector<double> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	for (auto x : data)
		s.insert(x);

	BOOST_CHECK( std::equal( s.begin(), s.end(), data.rbegin() ) );
}



BOOST_AUTO_TEST_CASE( ut_ctor_compare_iterator_passed ) {
	vector<double> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	RuntimeCmp<double> rc(RuntimeCmp<double>::reverse);
	square_list<double,RuntimeCmp<double>> s(data.begin(),data.end(),rc);
	
	BOOST_CHECK( std::equal( s.begin(), s.end(), data.rbegin() ) );
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