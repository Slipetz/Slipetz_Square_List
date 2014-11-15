#if !defined(IS_ITERATOR_HPP)
#define IS_ITERATOR_HPP

/*
	File: is_iterator.hpp
	Purpose: This class is used as a compile time check to see if we are using an iterator/pointer for the methods that require it
	Date: August 15, 2013
	Author: Ryan Slipetz
*/

using namespace std;
template <typename T>
struct is_iterator_impl {
	typedef char yes[1];
	typedef char no[2];

	template <typename C>
	static yes& _test(typename C::iterator_category*);

	template <typename>
	static no& _test(...);

	static const bool value = sizeof(_test<T>(0)) == sizeof(yes);
};

template <typename T, bool check = is_iterator_impl<T>::value>
struct is_iterator {

	typedef void type;

};

template <typename T>
struct is_iterator<T, false> {};

template <typename T>
struct is_iterator<T*, false> {
	typedef void type;
};

#endif