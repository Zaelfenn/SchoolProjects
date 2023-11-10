#include "List.h"
#include <iostream>
using std::cout;

List::List() : m_head(nullptr), m_tail(nullptr) //default ctor
{}

List::List(const List& original) : m_head(nullptr), m_tail(nullptr) //copy constructor
{
	if (original.m_head != nullptr) { //if data can be copied
		purgeList(); //clear the old list
		Node* travel = original.m_head; //make a traveling pointer through old list
		Node* nn = new Node; //new node for new list
		nn->m_data = travel->m_data; //set data
		m_head = nn; //make head of new list new node
		if (travel->m_next == nullptr) { //if this is the end of the list
			m_tail = nn; //new node is also the tail
		}
		else {
			nn->m_next = new Node(travel->m_next->m_data); //set the next node to a new node that has the data of old lists next node
			nn->m_next->m_prev = nn; //set the next node's previous to the "original" new node
			travel = travel->m_next; //traverse the list
			while (travel != nullptr) { //while the list still has data
				nn = nn->m_next; //go to the next item
				if (travel->m_next == nullptr) { //if this is the last item in the list
					m_tail = nn; //make this node the tail
				}
				else
				{
					nn->m_next = new Node(travel->m_next->m_data); //set the next node to a new node with the next data
					nn->m_next->m_prev = nn; //set the previous node of the next node to this node
				}
				travel = travel->m_next; //traverse the list
			}

		}
	}
}
 
List::List(List&& original) noexcept : m_head(original.m_head), m_tail(original.m_tail) //move semantics, set beginnning and end of list
{
	original.m_head = nullptr; //old list will no longer have a head pointer
	original.m_tail = nullptr; //old list will no longer have a tail pointer (both were moved to the new list)
}

List::~List() //destructor
{
	Node* travel = m_head; //set to the head of the list
	while (travel != nullptr) { //while the list still has items
		m_head = travel->m_next; 
		delete travel; //delete the node
		travel = m_head; //traverse the list
	}
}

List& List::operator = (const List& rhs) //copy assignment operator
{
	if (this != &rhs) { //if these are not the same list
		purgeList(); //clear the old list
		Node* travel = rhs.m_head; //make a traveling pointer through old list
		Node* nn = new Node; //new node for new list
		nn->m_data = travel->m_data; //set data
		m_head = nn; //make head of new list new node
		if (travel->m_next == nullptr) { //if this is the end of the list
			m_tail = nn; //new node is also the tail
		}
		else {
			nn->m_next = new Node(travel->m_next->m_data); //set the next node to a new node that has the data of old lists next node
			nn->m_next->m_prev = nn; //set the next node's previous to the "original" new node
			travel = travel->m_next; //traverse the list
			while (travel != nullptr) { //while the list still has data
				nn = nn->m_next; //go to the next item
				if (travel->m_next == nullptr) { //if this is the last item in the list
					m_tail = nn; //make this node the tail
				}
				else
				{
					nn->m_next = new Node(travel->m_next->m_data); //set the next node to a new node with the next data
					nn->m_next->m_prev = nn; //set the previous node of the next node to this node
				}
				travel = travel->m_next; //traverse the list
			}

		}
	}
	return *this; //return the new list
}

List& List::operator = (List&& rhs) noexcept { //move semantics

	if (this != &rhs) { //if they arent the same list
		purgeList(); //destroy the old list
		m_head = rhs.m_head; //steal the head of the new list
		m_tail = rhs.m_tail; //steal the tail of the new list
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr; //cut the ties of the old list
	}
	return *this; //return new list
}

void List::deleteData(string data) //deleting a node
{
	if (m_head == nullptr) //if the list is nonexistent
		cout << "Error: List not found" << std::endl; //error message
	else {
		Node* travel = m_head; //traveling pointer to traverse the list
		while (travel->m_data != data && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (travel->m_data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else
			cout << "Error: list item not found" << std::endl; //error message if the data isn't found
	}
}

void List::prependList(string data) //prepend the list
{
	Node* nn = new Node(data); //new node initialized with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else{ 
		nn->m_next = m_head; //set the new nodes next to the old head
		m_head->m_prev = nn; //set the old heads previous to the new node
		m_head = nn; //set the new head of the list to the new node
	}
}

void List::appendList(string data) //append the list
{
	Node* nn = new Node(data); //new node initialized with data
	if (m_tail == nullptr) { //if the list doesn't exist yet
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else {
		nn->m_prev = m_tail; //set the new nodes previous to the old tail
		m_tail->m_next = nn
			; //set the old tails next to the new node
		m_tail = nn; //set the new tail to the new node
	}
}

void List::insertList(string data) //insert data into the list in order
{
	Node* nn = new Node(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node* travel = m_head; //traveling pointer from the beginning of the list
		bool loop = true; //keep looping until finished
		while (loop == true) {
			if (travel->m_data >= nn->m_data) { //if the data is the same or comes first alphabetically
				if (travel == m_head) { //if the traveling pointer is the head
					nn->m_next = m_head; //prepend the list
					m_head->m_prev = nn;
					m_head = nn;
					loop = false; //stop the loop
				}
				else //the data is not the first in the list
				{
					Node* trail = travel->m_prev; //find the node right before
					trail->m_next = nn; //set the next to the new node
					nn->m_prev = trail; //set the new nodes previous to the trailing pointer
					nn->m_next = travel; //set the new noedes next to the traveling pointer
					travel->m_prev = nn; //set the traveling pointers previous to the new node
					loop = false; //stop the loop
				}
			}
			else if (travel == m_tail) { //if the pointer has traveled to the end of the list but the data is alphabetically last
				appendList(data); //append the list
				loop = false; //stop the loop
			}
			travel = travel->m_next; //traverse the list
		}


	}
}

void List::purgeList()//delete all nodes
{
	Node* travel = m_head; //from the head of the list
	while (travel != nullptr) { //while the list still exists
		m_head = travel->m_next;
		delete travel; //delete the nodes
		travel = m_head; //traverse the list
	}
}

void List::displayListFrwd() //display from head to tail
{ 
	Node* travel = m_head; //travel set to start of list
	while (travel != m_tail) { //while it is not at the end 
		cout << travel->m_data << " -> "; //output data with an arrow to "point" to next data
		travel = travel->m_next; //traverse the list
	}
	cout << travel->m_data << std::endl; //at the end, output just the data
}

void List::displayListBckwd() //display from tail to head
{
	Node* travel = m_tail; //travel set to end of list
	while (travel != m_head) { //while it is not at the start
		cout << travel->m_data << " -> "; //output data with an arrow "pointing" at previous data
		travel = travel->m_prev; //traverse the list
	}
	cout << travel->m_data << std::endl; //at the start, output only data
}