/** @file ut_square_list_01_concept.cpp
	@author Garth Santor
	@date 2014-07-25
	@version 1.0.0
	@note C++ 11/vc12
	@brief square_list<> proof of concept unit test.
	*/

#include "ut_square_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <string>
#include <vector>
using namespace std;

#if TEST_PHASE >= 1



/** Test fundamental concept by storing and retrieving 0..9 */
BOOST_AUTO_TEST_CASE(ut_concept_0_to_9) {
	vector<long> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto shuffle = v;
	random_shuffle(shuffle.begin(), shuffle.end());

	square_list<long> sl;
	for (auto x : shuffle)
		sl.insert(x);

	auto it = sl.begin();
	for (auto x : v) {
		BOOST_CHECK_EQUAL(*it, x);
		++it;
	}
}



/** Test fundamental concept by storing and retrieving A..Z */
BOOST_AUTO_TEST_CASE(ut_concept_A_to_Z) {
	string s = "Hello, world!";

	square_list<string::value_type> sl;
	for (auto ch : s)
		sl.insert(ch);

	sort(s.begin(), s.end());

	auto it = sl.begin();
	for (auto ch : s) {
		BOOST_CHECK_EQUAL(*it, ch);
		++it;
	}
}



/** Test fundamental concept by storing and retrieving strings */
BOOST_AUTO_TEST_CASE(ut_concept_strings) {
	vector<string> words{ "Sunna", "Mona", "Tiw", "Woden", "Thunor", "Frige", "Saturn" };
	square_list<string> sl;
	for (auto ch : words)
		sl.insert(ch);

	sort(words.begin(), words.end());

	auto it = sl.begin();
	for (auto word : words) {
		BOOST_CHECK_EQUAL(*it, word);
		++it;
	}
}



/** Test square_list<>::value_type */
BOOST_AUTO_TEST_CASE(ut_concept_value_type) {
	BOOST_CHECK(typeid(square_list<double>::value_type) == typeid(double));
	BOOST_CHECK(!std::is_const<square_list<double>::value_type>());
	BOOST_CHECK(std::is_floating_point<square_list<double>::value_type>());
	BOOST_CHECK(!std::is_integral<square_list<double>::value_type>());
	BOOST_CHECK(!std::is_reference<square_list<double>::value_type>());
	BOOST_CHECK(!std::is_class<square_list<double>::value_type>());

	BOOST_CHECK(typeid(square_list<std::string>::value_type) == typeid(std::string));
	BOOST_CHECK(!std::is_const<square_list<std::string>::value_type>());
	BOOST_CHECK(!std::is_floating_point<square_list<std::string>::value_type>());
	BOOST_CHECK(!std::is_integral<square_list<std::string>::value_type>());
	BOOST_CHECK(!std::is_reference<square_list<std::string>::value_type>());
	BOOST_CHECK(std::is_class<square_list<std::string>::value_type>());
}



/** Test square_list<>::iterator */
BOOST_AUTO_TEST_CASE(ut_forward_iterator_type) {
	BOOST_CHECK(typeid(square_list<double>::iterator::value_type) == typeid(double));
	BOOST_CHECK(typeid(square_list<std::string>::iterator::value_type) == typeid(std::string));
}


#endif // TEST_PHASE 1



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