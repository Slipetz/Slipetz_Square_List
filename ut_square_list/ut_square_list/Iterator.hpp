#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP
#include "Node.hpp"

/*
	File: Iterator.hpp
	Purpose: This class is acting as an iterator for the "square_list<T>" class
	Date: August 15, 2013
	Author: Ryan Slipetz
*/

template <typename NodeValue>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, NodeValue>{

public:
	typedef typename NodeValue							value_type;
	typedef typename Node<value_type>*					node_type;
public:
	node_type											selectedNode;

public:

	Iterator(node_type node) : selectedNode(node) {}
	~Iterator() {  }

	Iterator& operator++() { selectedNode = selectedNode->nextNode; return *this; }
	Iterator operator++(int) { Iterator<value_type> tmpNode(selectedNode); selectedNode = selectedNode->nextNode; return tmpNode; }

	Iterator& operator--() { selectedNode = selectedNode->prevNode; return *this; }
	Iterator operator--(int) { Iterator<value_type> tmpNode(selectedNode); selectedNode = selectedNode->prevNode; return tmpNode; }


	value_type operator *() { return selectedNode->nodeValue; }

	value_type* operator ->() { return &(selectedNode->nodeValue); }

};


template <typename value>
bool operator == (Iterator<value> lhs, Iterator<value> rhs) { return lhs.selectedNode == rhs.selectedNode; }

template <typename value>
bool operator != (Iterator<value> lhs, Iterator<value> rhs) { return !(lhs.selectedNode == rhs.selectedNode); }

template <typename value>
bool operator < (Iterator<value> lhs, Iterator<value> rhs) { return lhs.selectedNode < rhs.selectedNode; }

template <typename value>
bool operator > (Iterator<value> lhs, Iterator<value> rhs) { return rhs.selectedNode < lhs.selectedNode; }

template <typename value>
bool operator <= (Iterator<value> lhs, Iterator<value> rhs) { return !(lhs.selectedNode > rhs.selectedNode); }

template <typename value>
bool operator >= (Iterator<value> lhs, Iterator<value> rhs) { return !(lhs.selectedNode < rhs.selectedNode); }




#endif