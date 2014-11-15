#if !defined(SQUARE_LIST_HPP)
#define SQUARE_LIST_HPP

/*
	Class: square_list.hpp
	Purpose: Contains the code for the square_list class. STL-esque container that is totally awesome because it's coded from hand. 
	Author: Ryan Slipetz
	Date: (Finished) -> August 14, 2014. Started-> Probably around July 31?
*/

#include <cassert>
#include <functional> //FOR std::less<>
#include "Node.hpp"
#include "Iterator.hpp"
#include "ReverseIterator.hpp"
#include "is_iterator.hpp"

template <typename T_, typename COMP = std::less<T_> >
class square_list {
	
//Types
public:
	typedef typename T_												value_type;
	typedef typename value_type										key_type;
	typedef typename value_type const								const_reference;
	typedef typename std::size_t									size_type;
	typedef typename Node<value_type> *								pointer;
	typedef typename Node<value_type> *	 const						const_pointer;
	typedef typename Iterator<value_type>							iterator;
	typedef typename Iterator<value_type> const						const_iterator;
	typedef typename ReverseIterator<value_type>					reverse_iterator;
	typedef typename ReverseIterator<value_type> const				const_reverse_iterator;
	typedef typename std::ptrdiff_t									difference_type;

//Data
private:
	pointer beginPtr;
	pointer endPtr;
	size_type _count;
	size_type _headerCount;
	COMP compare;

//Methods
public:
	
	/*
		Method Name: square_list() -> default constructor
		Purpose: Creates a default square_list object
		Input: None - called via the code -> Can be utilized to over-ride the default comparison
		Result: Returns/Creates a default square_list object based on the value_type
	*/
	square_list(COMP const& c = COMP()) : _count(0), _headerCount(0) {
		beginPtr = endPtr = nullptr;
		compare = c;
	}

	/*
		Method Name: square_list(square_list const&) -> copy constructor
		Purpose: Creates a copy of the given square_list object
		Input: Another square_list of the same value type that this list will emulate
		Result: Creates/returns a square_list that is a deep-copy of the other list
	*/
	square_list(square_list<value_type> const& item, COMP const& c = COMP()) {
		compare = c;
		beginPtr = endPtr = nullptr;
		this->copy(item);
	}

	/*
		Method Name: square_list(square_list &&) -> RValue constructor
		Purpose: Creates a copy of the other square_list, and removes the information from the other square list
		Input: Another square_list this object will emulate
		Result: Clears the input square_list and creates a deep-copied version of the given list
	*/
	square_list(square_list<value_type> && item, COMP const& c = COMP()) {
		compare = c;
		beginPtr = endPtr = nullptr;
		this->copy(std::move(item));
		item.clear();
	}

	/*
		Method Name: square_list(iter, iter) -> Iterator Constructor
		Purpose: Creates a square_list with the values given in the range of iterators
		Input: A range of two iterators -> this method will only be called if the "is_iterator" condition is satisfied
		Result: Returns/Creates a square_list based on the values between the two iterators
	*/
	template <typename InputIterator>
	square_list(InputIterator begin, InputIterator end, COMP const& c = COMP(), typename is_iterator<InputIterator>::type* dummy = 0) : _count(0), _headerCount(0) {
		//Give it the starting parameters
		beginPtr = endPtr = nullptr;
		compare = c;
		this->insert(begin, end);
	}

	/*
		Method Name: square_list({...}) -> Initializer list constructor
		Purpose: Creates a square_list object based on the values given in the {...} (initializer list)
		Input: An initializer list of given values
		Result: Returns/Creates a square_list with the values given in the initializer list
	*/
	square_list(std::initializer_list<value_type> initList, COMP const& c = COMP()) : _count(0), _headerCount(0) {
		//Give it the starting parameters
		endPtr = beginPtr = nullptr;

		this->insert(initList.begin(), initList.end());
	}

	/*
		Method Name: ~square_list() -> Destructor
		Purpose: Clears the node-values in a controlled manner to destroy this object
		Input: None - called when object goes out of scope
		Result: Object goes bye bye!
	*/
	~square_list() { destroyList(); }


	//Begin() -> Returns the first node in the list, provided there is at least one node
	iterator begin() {
		if (beginPtr != nullptr && beginPtr->nextNode) {
			return iterator(beginPtr->nextNode);
		}
		return iterator(beginPtr);
	}

	//End() -> Returns a reference to the node that is one passed the final value
	iterator end() { return iterator(endPtr); }

	//Rbegin() -> Returns a reference to the "last value node" in the list. Used for the reverse_iterators
	reverse_iterator rbegin() {
		if (endPtr != nullptr && endPtr->prevNode) {
			return reverse_iterator(endPtr->prevNode);
		}
		return reverse_iterator(endPtr);
	}

	//Rend() -> Returns a reference to beginPtr, the node passed the "last" node in the reverse_iterators
	reverse_iterator rend() { return reverse_iterator(beginPtr); }


	//Begin() const -> Returns a const iterator to the first value node
	const_iterator begin() const {
		if (beginPtr != nullptr && beginPtr->nextNode) {
			return const_iterator(beginPtr->nextNode);
		}
		return const_iterator(beginPtr);
	}

	//End() const -> Returns a const iterator to the node after the last value node
	const_iterator end() const { return const_iterator(endPtr); }

	//Rbegin() -> Returns a reference to the "last value node" in the list. Used for the reverse_iterators
	const_reverse_iterator rbegin() const {
		if (endPtr != nullptr && endPtr->prevNode) {
			return const_reverse_iterator(endPtr->prevNode);
		}
		return const_reverse_iterator(endPtr);
	}

	//Rend() const -> Returns a const iterator to the "last reverse" node
	const_reverse_iterator rend() const { return const_reverse_iterator(beginPtr); }

	//Cbegin() const -> Returns a const iterator to the first node in the list
	const_iterator cbegin() const {
		if (beginPtr != nullptr && beginPtr->nextNode) {
			return const_iterator(beginPtr->nextNode);
		}
		return const_iterator(beginPtr);
	}

	//Cend() const -> Returns a const iterator to the last node in the list
	const_iterator cend() const { return const_iterator(endPtr); }

	//CRbegin() const -> Returns a const iterator to the "first reverse" node
	const_reverse_iterator crbegin() const {
		if (endPtr != nullptr && endPtr->prevNode) {
			return const_reverse_iterator(endPtr->prevNode);
		}
		return const_reverse_iterator(endPtr);
	}

	//Crend() const -> Returns a const iterator to the "last reverse" node
	const_reverse_iterator crend() const { return const_reverse_iterator(beginPtr); }
	
	/*
		Method Name: front()
		Purpose: Returns a reference to the first nodeValue in the list
		Input: Nothing - called from the object
		Result: Returns a const_reference to the first NodeValue
	*/
	const_reference front() const {
		return beginPtr->nextNode->nodeValue;
	}

	/*
		Method Name: back()
		Purpose: Returns a reference to the last nodeValue in the list
		Input: Nothing - called from the object
		Result: Returns a const_reference to the last nodeValue
	*/
	const_reference back() const {
		return endPtr->prevNode->nodeValue;
	}

	//Capacity Methods
	bool empty() const { return beginPtr == endPtr; }
	size_type size() const { return _count; }
	size_type max_size() const { return std::numeric_limits<size_type>::max(); }


	/*
		Method Name: operator = (const square_list<T>&)
		Purpose: Copies the values from the given input list
		Input: A square_list of the same value type to be copied
		Result: A deep copied version of the given list
	*/
	square_list<value_type>& operator = (square_list<value_type> const& item) {
		this->clear();
		this->copy(item);
		return *this;
	}

	/*
		Method Name: operator = (square_list<T> &&)
		Purpose: Copies the values from the given input list via move, and removes the values from the given list
		Input: A square_list of the same value type to be copied
		Result: A deep copied version of the given list, with the input list cleared
	*/
	square_list<value_type>& operator = (square_list<value_type> && item) {
		this->clear();
		this->swap(item);
		item.clear();
		return *this;
	}

	/*
		Method Name: operator = (initializerList {...})
		Purpose: Inserts the values from the given initializer list
		Input: An initializer list with values
		Result: A square_list with the given initializer list
	*/
	square_list<value_type>& operator = (std::initializer_list<value_type> const& initList) {
		this->clear();
		this->insert(initList.begin(), initList.end());

		return *this;
	}

	
	/*
		Method Name: insert (iterator,iterator)
		Purpose: Insert the values between the given iterator points
		Input: Two iterators that will be parsed to get the values
		Result: This square list will be populated with the values given between the iterators
	*/
	template <typename InputIterator>
	void insert(InputIterator rangeStart, InputIterator rangeEnd, typename is_iterator<InputIterator>::type* dummy = 0) {
		while (rangeStart != rangeEnd) {
			this->insert(*rangeStart++);
		}
	}

	/*
		Method Name: insert (initializer_list)
		Purpose: Insert the values in the given initializer list
		Input: An initializer list populated with values
		Result: This square list will be populated with the values given in the initializer_list
	*/
	void insert(std::initializer_list<value_type> const& initList) {
		this->insert(initList.begin(), initList.end());
	}

	
	//Below is the "MACRO" setup for the validity checks. You can define the different
	//debug setting here, to get the different validityCheck

#define FULLDEBUG

#if defined(FULLDEBUG)
#define VCHECK() this->fullValidityCheck();
#elif defined(DEBUG)
#define VCHECK() assert(this->validityCheck());
#else
#define VCHECK() ;
#endif

	/*
		Method Name: insert (value_type &&)
		Purpose: Insert the "R-Values" that have been passed to the insert method
		Input: The moved/R-Value given item
		Result: The given R-Value has been incorporated into the square_list
	*/
	void insert(value_type && item) {
		VCHECK();
		pointer newNode(new Node<value_type>(std::move(item)));
		if (beginPtr == endPtr) {
			beginPtr = new Node<value_type>();
			endPtr = new Node<value_type>();
			beginPtr->nextNode = newNode;
			newNode->prevNode = beginPtr;
			newNode->nextNode = endPtr;
			endPtr->prevNode = newNode;
			++_count;
			++_headerCount;
			cleanupNodes();
			return; //New Node will function has a header node
		}
		//Start from the first node
		pointer it = beginPtr->nextNode;
		//We need to replace the first node. This means replacing it as a header node
		if (compare(newNode->nodeValue, it->nodeValue)) {
			it->prevNode = newNode; //Shifting the beginNode forward
			newNode->nextNode = it;
			newNode->nextHeader = it->nextHeader; //Shifting the header to the new "base node"
			if (it->nextHeader != nullptr) {
				it->nextHeader->prevHeader = newNode;
			}
			newNode->listCount = it->listCount + 1; //Increment as we are adding one to this row
			it->listCount = 1;
			it->nextHeader = nullptr; //Reset the nextHeader for the new node
			beginPtr->nextNode = newNode;
			newNode->prevNode = beginPtr;
			it = newNode; //Assign the beginning node to there,
			++_count;
			cleanupNodes();
			return;
		}

		//Search the headers to see if we can find the right spot for the insert
		while (it->hasNextHeader() && !(compare(newNode->nodeValue,it->nextHeader->nodeValue))) {
			it = it->nextHeader;
		}

		//If here, it means it found a header that can support this object
		//Increment the internal list of the header to reflect which one it went down on
		it->listCount += 1;

		//Go down this list, to find out where to place it in this section
		while (it->hasNext() && !(compare(newNode->nodeValue, it->nextNode->nodeValue)) && it->nextNode != endPtr) {
			it = it->nextNode;
		}

		if (it->hasNext()) {
			newNode->nextNode = it->nextNode;
			it->nextNode->prevNode = newNode;
		}

		newNode->prevNode = it;
		it->nextNode = newNode;
		++_count;

		cleanupNodes(); //Perform the cleanup of the chains on a regular basis
		VCHECK();
	}

	/*
		Method Name: insert (const value_type &)
		Purpose: Insert the "R-Values" that have been passed to the insert method
		Input: The moved/R-Value given item
		Result: The given R-Value has been incorporated into the square_list
	*/
	void insert(value_type const& item) {
		VCHECK();
		pointer newNode(new Node<value_type>(item));
		if (beginPtr == endPtr) {
			beginPtr = new Node<value_type>();
			endPtr = new Node<value_type>();
			beginPtr->nextNode = newNode;
			newNode->prevNode = beginPtr;
			newNode->nextNode = endPtr;
			endPtr->prevNode = newNode;
			++_count;
			++_headerCount;
			cleanupNodes();
			return; //New Node will function has a header node
		}
		//Start from the first node
		pointer it = beginPtr->nextNode;
		//We need to replace the first node. This means replacing it as a header node
		if (compare(newNode->nodeValue, it->nodeValue)) {
			it->prevNode = newNode; //Shifting the beginNode forward
			newNode->nextNode = it;
			newNode->nextHeader = it->nextHeader; //Shifting the header to the new "base node"
			if (it->nextHeader != nullptr) {
				it->nextHeader->prevHeader = newNode;
			}
			newNode->listCount = it->listCount + 1; //Increment as we are adding one to this row
			it->listCount = 1;
			it->nextHeader = nullptr; //Reset the nextHeader for the new node
			beginPtr->nextNode = newNode;
			newNode->prevNode = beginPtr;
			it = newNode; //Assign the beginning node to there,
			++_count;
			cleanupNodes();
			return;
		}

		//Search the headers to see if we can find the right spot for the insert
		while (it->hasNextHeader() && !(compare(newNode->nodeValue, it->nextHeader->nodeValue))) {
			it = it->nextHeader;
		}

		//If here, it means it found a header that can support this object
		//Increment the internal list of the header to reflect which one it went down on
		it->listCount += 1;

		//Go down this list, to find out where to place it in this section
		while (it->hasNext() && !(compare(newNode->nodeValue, it->nextNode->nodeValue)) && it->nextNode != endPtr) {
			it = it->nextNode;
		}

		if (it->hasNext()) {
			newNode->nextNode = it->nextNode;
			(it->nextNode)->prevNode = newNode;
		}

		newNode->prevNode = it;
		it->nextNode = newNode;
		++_count;

		cleanupNodes(); //Perform the cleanup of the chains on a regular basis
		VCHECK();
	}

	/*
		Method Name: erase (const_iterator)
		Purpose: Erases the value that the given iterator is pointing to
		Input: An iterator containing the node that needs to be erased
		Result: Removes the node from the list and cleans it up
	*/
	void erase(const_iterator it) {
		VCHECK();
		pointer erased = it.selectedNode;
		//Pull a reference to the nextNode -> Will always have one unless we try to delete the "end"
		pointer pulledNode = erased->nextNode;

		//SITUATION 1: LAST NODE SITUATION
		if (pulledNode == endPtr && erased->prevNode == beginPtr) {
			this->clear();
			return; //Back out. We've set everything we need to!
		}

		//SITUATION 2: ERASING HEADER NODE
		else if (erased->nextHeader != nullptr || erased->prevHeader != nullptr) {
			//Goal of this situation: give the PULLEDNODE the headerDetails from the ERASED NODE
			//CHECK - If pulledNode != endPtr, then we want to assign this!
			if (pulledNode != endPtr) {
				pulledNode->copyHeaders(*erased);
				pulledNode->listCount = (erased->listCount - 1); //Since we are getting rid of one from this column, decrease the listCount by 1

				//RECONFIGURE THE SURROUNDING HEADERS
				if (erased->nextHeader != nullptr) {
					pulledNode->nextHeader->prevHeader = pulledNode; //Reassigning the next header to know about the pulledNode
				}
				if (erased->prevHeader != nullptr) {
					pulledNode->prevHeader->nextHeader = pulledNode;
				}

				erased->resetHeaders();
			} else {
				erased->prevHeader->nextHeader = nullptr; //We need to remove the "header" aspect from the next header. We've reached the last column, with just endPtr next
				--_headerCount; //We've removed a header
				erased->resetHeaders();
			}
		}

		//SITUATION 3: PULLING A HEADER NODE
		else if ((pulledNode->nextHeader != nullptr || pulledNode->prevHeader != nullptr) && pulledNode != endPtr) {
			//In this situation: give the PULLEDNODE'S NEXT NODE the header details. 
			pointer newHeader = pulledNode->nextNode;
			if (newHeader != endPtr) {
				newHeader->copyHeaders(*pulledNode);
				newHeader->listCount = (pulledNode->listCount - 1);

				//RECONFIGURE THE SURROUNDING HEADERS
				if (pulledNode->nextHeader != nullptr) {
					newHeader->nextHeader->prevHeader = newHeader;
				}
				if (pulledNode->prevHeader != nullptr) {
					newHeader->prevHeader->nextHeader = newHeader;
				}

				//RESET THE DETAILS OF THE PULLED NODE
				pulledNode->resetHeaders();
			}
			else {
				pulledNode->prevHeader->nextHeader = nullptr; //We need to remove the "header" aspect from the next header. We've reached the last column, with just endPtr next
				--_headerCount; //We've removed a header
				pulledNode->resetHeaders();
			}
		}

		//SITUATION 4 : LOWER THE LISTCOUNT OF THE HEADER OF THE NODE WE ARE ERASING
		else {
			value_type nValue = erased->nodeValue;
			pointer header = beginPtr->nextNode;

			if (!header->hasNextHeader()) {
				header->listCount -= 1; //Means we only have 1 column.. we're taking it away from that
			}
			else {
				while (header->hasNextHeader() && !(compare(nValue, header->nextHeader->nodeValue))) {
					header = header->nextHeader; //This will take us to the last possible header
				}

				if (compare(header->nodeValue, nValue)) {
					//If we hit this, we know it's in the current header's list
					header->listCount -= 1;
				}
				else {
					//Otherwise, we know it's equal. Need to implement multiple checks here
					if (compare(erased->prevNode->nodeValue, nValue)) {
						//We can see if it's the first in the collection of nodes. If we know that, we can confirm it's the previous header
						while (header->prevHeader->nodeValue == nValue) {
							header = header->prevHeader;
						}

						//Do it once more, so we get one back
						header = header->prevHeader;

						//It means we're at the first header previous that != nValue
						header->listCount -= 1; //We need to reduce this list listcount
					}
					else if (compare(nValue, erased->nextNode->nodeValue)) {
						//If it's > this node, it means we're on the last header and we reduce it
						header->listCount -= 1;
					}
					else {
						//We need to parse the list and see if we can figure out what node we are carrying
						iterator searchIT = this->find(nValue); //This will allow us to get the first node
						while (*searchIT == nValue) {
							if (searchIT.selectedNode == erased) {
								//It means we've found the right node! Now, we either go back or go forward until the header..
								//Since if it's equal, going backwards again will mean another cycle
								while (searchIT.selectedNode->prevNode != nullptr && 
									!(searchIT.selectedNode->prevHeader != nullptr 
									|| searchIT.selectedNode->nextHeader != nullptr)) {
									//Go backwards until we run into a header
									--searchIT;
								}
								searchIT.selectedNode->listCount -= 1;
								break; //Break out of the while loop
							}
							++searchIT;
						}
					}
				}
			}
		}

		//Check to see if the node has a previous node. If so, reassign this previous node to the new pulledNode
		if (erased->prevNode != nullptr) {
			erased->prevNode->nextNode = pulledNode; //Give the erased nodes "previous" a reference to pulledNode as the next node
			pulledNode->prevNode = erased->prevNode; // Reassign the pulledNodes prev node to be the erasedNodes previous
		}

		//At this point, we have reassigned the pulledNode to know how to get back and forth
		//We need to rid the erased node's references.

		delete erased;
		--_count;
		//At this point, we have removed all references to the erased node and re-assigned everything as needed.
		//Re-balance the list and we are done!
		cleanupNodes();
		VCHECK();
	}
#undef VCHECK
#undef DEBUG
#undef FULLDEBUG

	/*
		Method Name: erase (const key_type& key)
		Purpose: Erases ALL of the values from the list with that key
		Input: A key value that will be checked in the square_list
		Result: Removes ALL of the nodes that have that key as the data member and returns a number of how many were deleted
	*/
	size_type erase(key_type const& key) {
		iterator beginIterator = this->find(key);
		size_type returnCount = 0;
		if (beginIterator.selectedNode == endPtr) {
			return returnCount;
		}
		while (*beginIterator == key) {
			iterator deletedIT = beginIterator++;
			this->erase(deletedIT);
			++returnCount;
		}
		return returnCount;
	}


	/*
		Method Name: cleanupNodes()
		Purpose: Clean and balance the list to maintain its square-ness
		Input: None
		Result: The list will be balanced and left-padded as much as possible
	*/
	void cleanupNodes() {
		size_type rootSize = static_cast<size_type>(ceil(sqrt(_count)));

		if (rootSize == 1 || rootSize == 0) {
			return; //Return -> means we have 1 or 0 nodes
		}

		//To Start -> Go through each header, and check the listCounts for each of them to ensure we don't have a weight issue.
		pointer it = beginPtr->nextNode;
		while (it->hasNextHeader()) {

			//Constant left padding -> keep pushing it to the left
			while (it->listCount < rootSize) {
				it->listCount += 1; //Increment this list. We know we are going to add one to it
				//Pull the next header, as this is the one we are going to use
				pointer pulledNode = it->nextHeader;
				pointer newHeader = pulledNode->nextNode;
				if (newHeader != endPtr) {
					//If we aren't at the end, swap the headers!
					newHeader->copyHeaders(*pulledNode);
					newHeader->listCount = pulledNode->listCount - 1;

					//Since we know it has a prevHeader, don't need to validate
					newHeader->prevHeader->nextHeader = newHeader;

					//Check and ensure header access is correct
					if (newHeader->nextHeader != nullptr) {
						newHeader->nextHeader->prevHeader = newHeader;
					}

					//Reset the pulled node Headers
					pulledNode->resetHeaders();
				}
				else {
					//If it is the endPtr, we are down one header
					pulledNode->resetHeaders();
					it->nextHeader = nullptr; //Reset the current headers next node to preserve data integrity
					--_headerCount;
				}				
			}

			while (it->listCount > rootSize) {
				//Establish a left-padded square list
				//Check to see if the previous head Node has room
				if (it->prevHeader != nullptr && it->prevHeader->listCount != rootSize) {

					pointer oldHeader = it;
					pointer newHeader = it->nextNode;
					if (newHeader != endPtr){
						//Swapping headers
						//Step 1 -> Assign both headers to the new node
						newHeader->copyHeaders(*oldHeader);
						newHeader->listCount = oldHeader->listCount - 1; //Subtract one as we are removing one from this list (pushing it to the left list)

						//Step 2 - A
						//Check to see if OldHeader has a prev header. If so, assign that to the newHeader
						if (oldHeader->prevHeader != nullptr) {
							oldHeader->prevHeader->nextHeader = newHeader;

							//This should always be the case in this instance
							oldHeader->prevHeader->listCount += 1; //Increment the Prev header by one as we are moving one back
						}

						//Step 2 -B
						//Check to see if oldHeader has a next header. if So, assign that to the newHeader
						if (oldHeader->nextHeader != nullptr) {
							oldHeader->nextHeader->prevHeader = newHeader;
						}
						it = newHeader; //Re-assign it -> so we don't screw with the while loop
					}

					//Step 3 - Remove references from the oldHeader
					oldHeader->resetHeaders();
				}
				else { 
					pointer oldHeader = it->nextHeader;
					it->listCount -= 1; //We are going to remove one from this list, so we decrement
					pointer newHeader = oldHeader->prevNode;
					//Swapping Headers
					//Step 1 -> Assign both headers to the new node
					newHeader->copyHeaders(*oldHeader);
					newHeader->listCount = oldHeader->listCount + 1; //Increment by 1 as we have added a new node to this list

					//Step 2 - A
					//Check to see if oldHeader has a prev header. If so, assign that to point to newHeader
					if (oldHeader->prevHeader != nullptr) {
						oldHeader->prevHeader->nextHeader = newHeader;
					}

					//Step 2 - B
					//Check to see if oldHeader has a next header. If so, re-assign that to newHeader
					if (oldHeader->nextHeader != nullptr) {
						oldHeader->nextHeader->prevHeader = newHeader;
					}

					//Step 3 - Reset the headers/values from the oldHeader
					oldHeader->resetHeaders();
				}
			}
			//Increment to the next header -> Recheck, as we can eliminate a headNode from here
			if (it->hasNextHeader()) {
				it = it->nextHeader;
			}
		}

		//Run the same check, after the fact so we are able to get to see the stats of the final head node
		if (it->listCount > rootSize) {
			//Establish a left-padded square list
			//Check to see if the previous head Node has room
			if (it->prevHeader != nullptr && it->prevHeader->listCount != rootSize) {
				pointer oldHeader = it;
				pointer newHeader = it->nextNode;
				if (newHeader != endPtr) {

					//Swapping headers
					//Step 1 -> Assign both headers to the new node
					newHeader->copyHeaders(*oldHeader);
					newHeader->listCount = oldHeader->listCount - 1; //Subtract one as we are removing one from this list (pushing it to the left list)

					//Step 2 - A
					//Check to see if OldHeader has a prev header. If so, assign that to the newHeader
					if (oldHeader->prevHeader != nullptr) {
						oldHeader->prevHeader->nextHeader = newHeader;

						//This should always be the case in this instance
						oldHeader->prevHeader->listCount += 1; //Increment the Prev header by one as we are moving one back
					}

					//Step 2 -B
					//Check to see if oldHeader has a next header. if So, assign that to the newHeader
					if (oldHeader->nextHeader != nullptr) {
						oldHeader->nextHeader->prevHeader = newHeader;
					}
				}

				//Step 3 - Remove references from the oldHeader
				oldHeader->resetHeaders();
			}
			else if(it->nextHeader != nullptr) { //No more room the left, go to the right!

				pointer oldHeader = it->nextHeader;
				it->listCount -= 1; //We are going to remove one from this list, so we decrement
				pointer newHeader = oldHeader->prevNode;
				//Swapping Headers
				//Step 1 -> Assign both headers to the new node
				newHeader->copyHeaders(*oldHeader);
				newHeader->listCount = oldHeader->listCount + 1; //Increment by 1 as we have added a new node to this list

				//Step 2 - A
				//Check to see if oldHeader has a prev header. If so, assign that to point to newHeader
				if (oldHeader->prevHeader != nullptr) {
					oldHeader->prevHeader->nextHeader = newHeader;
				}

				//Step 2 - B
				//Check to see if oldHeader has a next header. If so, re-assign that to newHeader
				if (oldHeader->nextHeader != nullptr) {
					oldHeader->nextHeader->prevHeader = newHeader;
				}

				//Step 3 - Reset the headers/values from the oldHeader
				oldHeader->resetHeaders();
			}
			else {
				//If we reach here, it means that we need to go to the right, but we currently don't have a node there
				pointer newHeader = endPtr->prevNode;

				//Refer to each other in the headers so we can access that space
				it->nextHeader = newHeader;
				newHeader->prevHeader = it;

				//Decrement the first "list" to ensure we get the correct list count there
				it->listCount -= 1;
				_headerCount++;
			}
		}
		//this->dumpList();
	}


	/*
		Method Name: erase (const_iterator, const_iterator) -> Iterator Erase
		Purpose: Erases all of the values between the two given iterators
		Input: Two iterators that will be range-deleted
		Result: Removes ALL of the nodes between the two iterators and returns the last node (now the new node being pointed to)
	*/
	iterator erase(const_iterator begin, const_iterator end) {
		iterator it = begin;
		iterator helperNode = it;
		while (it != end) {
			++helperNode;
			this->erase(it);
			it = helperNode;
		}
		return end;
	}

	/*
		Method Name: clear()
		Purpose: Removes all of the nodes from the list and basically "reconstructs" one
		Input: None
		Result: Square_list is purged and returned to a default state
	*/
	void clear() {
		//Need to remove references here and reset listCount
		//Essentially - reconstruct the squarelist
		if (beginPtr != endPtr) {
			destroyList();
		}
		beginPtr = endPtr = nullptr;
		_count = 0;
		_headerCount = 0;
	}

	/*
		Method Name: copy (const square_list& )
		Purpose: Creates a deep copy of the given list
		Input: Another square_list of the same value type
		Result: This list is now a deep-copied version of the given list
	*/
	square_list<value_type>& copy(square_list<value_type> const& copyItem){
		//Clear this square_list
		this->clear();
		this->insert(copyItem.begin(), copyItem.end());
		return *this;
	}

	/*
		Method Name: find (const key_type& )
		Purpose: TO locate the first node whose data is the given key
		Input: key_value that will be searched
		Result: An iterator that points to the first key_value node, or the endPtr if it cannot be found
	*/
	iterator find(key_type const& key) {
		if (beginPtr == nullptr) {
			return iterator(endPtr); //Means there is nothing in the list. Return end
		}
		pointer searchNode = beginPtr->nextNode;

		while (searchNode->hasNextHeader() && !(compare(key, searchNode->nextHeader->nodeValue))) {
			searchNode = searchNode->nextHeader; //This will put us in the right column!
		}

		//EDGE CASE
		//Key value < first node
		if (compare(key, searchNode->nodeValue)) {
			return iterator(endPtr);
		}
		else if (key == searchNode->nodeValue) {
			//Here, it means that our header value is equal to the key. If this is true, we should check behind us to ensure we are at the first value
			while (searchNode->prevNode != nullptr && searchNode->prevNode->nodeValue == key) {
				searchNode = searchNode->prevNode;
			}

			return iterator(searchNode); //This will return the first possible value
		}
		else {
			//Here, we can parse until we either reach the end, or we hit a value that is > key -> We know the key is > value if we get here

			while (searchNode != endPtr && searchNode->nextNode != nullptr && compare(searchNode->nodeValue, key)){
				searchNode = searchNode->nextNode;
			}

			if (compare(key, searchNode->nodeValue)) {
				return iterator(endPtr);
			}

			if (key == searchNode->nodeValue) {
				return iterator(searchNode);
			}

			//If we hit here, only other possibility is that we have hit endPtr
			//Just return endPtr
			return iterator(endPtr);
		}
	}


	/*
		Method Name: count (const key_type& )
		Purpose: To count the number of nodes that have the given key
		Input: key_value that will be searched
		Result: A count of the number of nodes that the contain the key
	*/
	size_type count(key_type const& key) {
		iterator first = this->find(key);
		if (first == this->end()) {
			return 0;
		}
		size_type counter = 0;
		while (*first == key) {
			counter += 1;
			first++;
		}
		return counter;
	}


	/*
		Method Name: equal_range (const key_type& )
		Purpose: To return two iterators that point to the the first and last location of the key
		Input: key_value that will be searched
		Result: An std::pair that will contain two iterators that are the first and last location of the two keys
	*/
	std::pair<iterator, iterator> equal_range(key_type const& key) {
		auto first = this->find(key);
		if (first == this->end()) {
			return std::make_pair(iterator(endPtr), iterator(endPtr));
		}
		auto second = first;
		while (*second == key) {
			second++;
		}
		return std::make_pair(first, second);
	}

	/*
		Method Name: equal_range (const key_type& )
		Purpose: To return two const_iterators that point to the the first and last location of the key
		Input: key_value that will be searched
		Result: An std::pair that will contain two const_iterators that are the first and last location of the two keys
	*/
	std::pair<const_iterator, const_iterator> equal_range(key_type const& key) const {
		auto first = this->find(key);
		if (first == this->end()) {
			return std::make_pair(const_iterator(endPtr), const_iterator(endPtr));
		}
		auto second = first;
		while (*second == key) {
			second++;
		}
		return std::make_pair(first, second);
	}


	/*
		Method Name: swap (square_list<T> &)
		Purpose: Swaps the two square_lists so that they now hold the other lists' values
		Input: Another square_list that will be swapped
		Result: Each list now contains the values of the other list
	*/
	square_list<value_type>& swap(square_list<value_type>& swapped){
		//We need to swap everything about these items -> Need a temp Sq List

		square_list<value_type> temp;

		//BeginPtr first
		temp.beginPtr = std::move(swapped.beginPtr);
		swapped.beginPtr = std::move(this->beginPtr);
		this->beginPtr = std::move(temp.beginPtr);

		//EndPtr
		temp.endPtr = std::move(swapped.endPtr);
		swapped.endPtr = std::move(this->endPtr);
		this->endPtr = std::move(temp.endPtr);

		//Count
		temp._count = std::move(swapped._count);
		swapped._count = std::move(this->_count);
		this->_count = std::move(temp._count);

		//HeaderCount
		temp._headerCount = std::move(swapped._headerCount);
		swapped._headerCount = std::move(this->_headerCount);
		this->_headerCount = std::move(temp._headerCount);

		//Comparison operator
		temp.compare = std::move(swapped.compare);
		swapped.compare = std::move(this->compare);
		this->compare = std::move(temp.compare);

		temp.beginPtr = nullptr;
		temp.endPtr = nullptr;

		return *this;
	}

	/*
		Method Name: validityCheck
		Purpose: Performs a quick/easy check of the square_list (validates that it is a square)
		Input: None
		Result: A bool value that states if the square_list is valid or not
	*/
	bool validityCheck() {
		//First, get the SQRT of the list
		size_type rootSize = static_cast<size_type>(ceil(sqrt(_count)));
		if (rootSize == 1 || rootSize == 0) {
			return true; //Means we have 0 or 1 nodes. No real check to do here
		}

		//EASY CHECK
		if (this->_headerCount > rootSize) {
			return false;
		}

		//Run the check to ensure everything is right -> Check the listCount of each header
		int headerCount = 0;
		pointer headerStart = beginPtr->nextNode;
		while (headerStart->hasNextHeader()) {
			++headerCount;
			//If any header's list size > rootSize, its bad
			if (headerStart->listCount > rootSize) {
				return false;
			}
			headerStart = headerStart->nextHeader;
		}

		//check the last header
		++headerCount;
		if (headerStart->listCount > rootSize) {
			return false;
		}

		//Easier check - means we just check the numbers, not the node values
		return true;
	}

	/*
		Method Name: fullValidityCheck
		Purpose: Performs an in-depth check of the square_list (validates that it is a square)
		Input: None
		Result: A bool value that states if the square_list is actually square
	*/
	bool fullValidityCheck() {
		size_type rootSize = static_cast<size_type>(ceil(sqrt(_count)));

		if (rootSize == 1 || rootSize == 0) {
			return true; //Means we have 0 or 1 nodes. No real check to do here
		}

		//Run the easy check first -> Gets the basics out of the way
		if (validityCheck()) {
			//Start at the beginning. Check everyNode value. Ensure it's sorted and the numbers correspond
			pointer checkNode = beginPtr->nextNode;
			pointer headerCheck = checkNode; //Start here, as this should always be the first header
			//value_type nodeVal = checkNode.lock()->nodeValue;
			size_type listCount = 1; //Start at 1, as headNode also counts as a node

			while (checkNode->hasNext() && checkNode->nextNode != endPtr) {

				//Perform the header/listCount check first
				if (checkNode->nextNode->nextHeader || checkNode->nextNode->prevHeader) {
					//Above conditional checks that it contains a connection to another header. 
					if (headerCheck->listCount != listCount) {
						return false; //The listCount should correspond to the listCount in the header. Otherwise, we've got bad errors!
					}
					listCount = 0; //Reduce to 0 here, as we are going to increase it in the next set of code
					headerCheck = headerCheck->nextHeader;
				}

				checkNode = checkNode->nextNode;
				++listCount;
				if (compare(checkNode->nodeValue, checkNode->prevNode->nodeValue)) {
					return false; //Sorted Check -> If nextNode is < current node, we goofed!
				}
				//nodeVal = checkNode.lock()->nodeValue;
			} 

			//If we get here. We should be at the end. Confirm and return true
			if (checkNode->nextNode == endPtr) {
				return true;
			}
			return false; //Means something goofed, and we've lost a node somewhere
		}

		return false; //Means validityCheck has failed
	}


private:

	/*
		Method Name: destroyList
		Purpose: Provides a controlled destruction of the square_list nodes, so we avoid memory leaks or stack overflow
		Input: None
		Result: All of the nodes of the list are deleted
	*/
	void destroyList() {
		pointer eraser = beginPtr;
		pointer temp = nullptr;
		while (eraser != nullptr && eraser->hasNext() && eraser != endPtr) {
			//Assign temp to be the nextNode
			temp = eraser->nextNode;
			delete eraser;
			//Reassign eraser to temp and release temp from holding the object
			eraser = temp;
			temp = nullptr;
		}
		//Release both created scope objects, and release begin/endPtr
		delete eraser;
	}

	/*
		Method Name: dumpList
		Purpose: Dumps out a visual representation of the list in it's current state
		Input: None
		Result: Console-output, visual representation of the square_list
		NOTE: THIS IS COMMENTED OUT. UNIQUE_PTR DOES NOT WORK WITH THIS!
	*/
	
	/*void dumpList() {
		for (auto it = this->begin(); it != this->end(); ++it) {
			if (it.selectedNode->nextHeader != nullptr || it.selectedNode->prevHeader != nullptr) {
				if (it == this->begin()) {
					std::cout << *it << "-";
					continue;
				}
				std::cout << std::endl << "|" << std::endl << *it << "-";
				continue;
			}

			std::cout << *it << "-";
		}
		std::cout << std::endl << std::endl;
	}
*/
};


//RELATIONAL OPERATORS FOR SQUARE_LIST
template <typename T>
bool operator == (square_list<T> const& lhs, square_list<T> const& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	auto lhsIT = lhs.begin();
	auto rhsIT = rhs.begin();
	while (lhsIT != lhs.end() && rhsIT != rhs.end()) {
		if ((*lhsIT++) != (*rhsIT++)) {
			return false;
		}
	}

	return true;
}

template <typename T>
bool operator != (square_list<T> const& lhs, square_list<T> const& rhs) {
	return !(lhs == rhs);
}

template <typename T>
bool operator < (square_list<T> const& lhs, square_list<T> const& rhs) {
	auto lhsIT = lhs.begin();
	auto rhsIT = rhs.begin();

	while (lhsIT != lhs.end() && rhsIT != rhs.end()) {
		if (*lhsIT < *rhsIT) {
			return true;
		}
		if (*lhsIT > *rhsIT) {
			return false;
		}
		++lhsIT;
		++rhsIT;
	}

	if (lhsIT == lhs.end() && rhsIT != rhs.end()) {
		return true;
	}

	return false;
}

template <typename T>
bool operator <= (square_list<T> const& lhs, square_list<T> const& rhs) {
	return !(lhs > rhs);
}

template <typename T>
bool operator > (square_list<T> const& lhs, square_list<T> const& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator >= (square_list<T> const& lhs, square_list<T> const& rhs) {
	return !(lhs < rhs);
}


#endif