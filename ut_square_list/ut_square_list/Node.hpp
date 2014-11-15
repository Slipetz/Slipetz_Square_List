#ifndef NODE_HPP
#define NODE_HPP

#include <iterator>
#include <iostream>
#include <memory>

/*
	Class Name: Node
	Purpose: Defines the individual nodes of our square_list class
	Notes: This class is templated, just as the "square_list" class, to allow them to hold any particular value
			This class also makes use of shared/unique_ptr -> helps to control memory leak issues.
*/
template <typename T_>
class Node {

//Types/typedefs
public:
	typedef typename T_												value_type;
	typedef typename std::size_t									size_type;
	typedef typename value_type&									reference;
	typedef typename value_type const&								const_reference;
	typedef typename Node<value_type>*								pointer;
	typedef typename Node<value_type>*	const						const_pointer;

//Data Members - User should not see this class, allows us to make them public for easier use within the square_list
public:
	pointer prevNode;
	pointer nextNode;
	value_type nodeValue;

	//If required: header attributes
	pointer prevHeader;
	pointer nextHeader;
	size_type listCount;


//Constructors
public:
	Node(value_type const& item) : nodeValue(item) {
		prevNode = nextNode = prevHeader = nextHeader = nullptr;
		listCount = 1;
	}

	Node(value_type && item) : nodeValue(std::move(item)) {
		prevNode = nextNode = prevHeader = nextHeader = nullptr;
		listCount = 1;
		item = std::move(value_type());
	}

	Node(Node<value_type> const& rhs) : prevNode(rhs.prevNode), nextNode(rhs.nextNode), prevHeader(rhs.prevHeader), nextHeader(rhs.nextHeader), listCount(rhs.listCount), nodeValue(rhs.nodeValue) {}

	Node(Node<value_type> && rhs) : prevNode(std::move(rhs.prevNode)), nextNode(std::move(rhs.nextNode)),
		prevHeader(std::move(rhs.prevHeader)), nextHeader(std::move(rhs.nextHeader)), listCount(std::move(rhs.listCount)), nodeValue(std::move(rhs.nodeValue)) {}

	Node() : listCount(0) {
		prevNode = nextNode = prevHeader = nextHeader = nullptr;
	}
	~Node() {  }

//Method/Functionality
public:
	//Methods
	bool hasNext() const { return !(nextNode == nullptr); }
	bool hasNextHeader() const { return !(nextHeader == nullptr); }
	bool hasPrevious() const { return !(prevNode == nullptr); }

	//Relational Operators to value_type
	inline bool operator == (value_type const& rhs)		{ return nodeValue == rhs; }
	inline bool operator != (value_type const& rhs)		{ return !(nodeValue == rhs); }
	inline bool operator < (value_type const& rhs)		{ return nodeValue < rhs; }
	inline bool operator <= (value_type const& rhs)		{ return !(nodeValue > rhs); }
	inline bool operator > (value_type const& rhs)		{ return rhs < nodeValue; }
	inline bool operator >= (value_type const& rhs)		{ return !(nodeValue < rhs); }

	//Relational Operators to Node<value_type>
	inline bool operator == (Node<value_type> const& rhs) { return nodeValue == rhs.nodeValue; }
	inline bool operator != (Node<value_type> const& rhs) { return !(nodeValue == rhs.nodeValue); }
	inline bool operator < (Node<value_type> const& rhs) { return nodeValue < rhs.nodeValue; }
	inline bool operator <= (Node<value_type> const& rhs) { return !(nodeValue > rhs.nodeValue); }
	inline bool operator > (Node<value_type> const& rhs) { return rhs.nodeValue < nodeValue; }
	inline bool operator >= (Node<value_type> const& rhs) { return !(nodeValue < rhs.nodeValue); }


	//HELPER METHODS
	void resetHeaders() {
		this->nextHeader = nullptr;
		this->prevHeader = nullptr;
		this->listCount = 1;
	}

	Node<value_type>& copyHeaders(Node<value_type>& other) {
		Node<value_type> temp;
		
		//NextHeader
		this->nextHeader = std::move(other.nextHeader);
		//PrevHeader
		this->prevHeader = std::move(other.prevHeader);

		return *this;
	}
};

//Output operator for the node class
template <typename T_>
std::ostream& operator << (std::ostream& out, Node<T_> const& rhs) { out << "Node->nodeValue: " << rhs.nodeValue; return out; }


#endif