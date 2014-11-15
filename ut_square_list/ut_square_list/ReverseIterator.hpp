#if !defined(REVERSE_ITERATOR_HPP)
#define REVERSE_ITERATOR_HPP
#include "Node.hpp"

/*
	File: ReverseIterator.hpp
	Purpose: This class is acting as a REVERSE iterator for the "square_list<T>" class
	Date: August 15, 2013
	Author: Ryan Slipetz
*/

template <typename T>
class ReverseIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
	typedef typename T									value_type;
	typedef typename Node<value_type>*					node_type;

public:
	node_type selectedNode;
public:
	ReverseIterator(node_type const& node) : selectedNode(node) {}
	~ReverseIterator() {  }


	ReverseIterator& operator++() { selectedNode = selectedNode->prevNode; return *this; }
	ReverseIterator operator++(int) { ReverseIterator<value_type> tmpNode(selectedNode); selectedNode = selectedNode->prevNode; return tmpNode; }

	ReverseIterator& operator--() { selectedNode = selectedNode->nextNode; return *this; }
	ReverseIterator operator--(int) { ReverseIterator<value_type> tmpNode(selectedNode); selectedNode = selectedNode->nextNode; return tmpNode; }

	value_type operator*() { return selectedNode->nodeValue; }

};

template <typename value_type>
inline bool operator == (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs) { return lhs.selectedNode == rhs.selectedNode; }
template <typename value_type>
inline bool operator != (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs)  { return !(lhs.selectedNode == rhs.selectedNode); }
template <typename value_type>
inline bool operator < (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs) { return lhs.selectedNode < rhs.selectedNode; }
template <typename value_type>
inline bool operator > (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs) { return rhs.selectedNode < lhs.selectedNode; }
template <typename value_type>
inline bool operator <= (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs) { return !(lhs.selectedNode > rhs.selectedNode); }
template <typename value_type>
inline bool operator >= (ReverseIterator<value_type> const& lhs, ReverseIterator<value_type> const& rhs) { return !(lhs.selectedNode < rhs.selectedNode); }

#endif