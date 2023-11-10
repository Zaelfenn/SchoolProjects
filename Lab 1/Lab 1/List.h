#pragma once
#include "Node.h"
class List {
	public:
		List(); //default ctor
		List(const List& original); //copy ctor
		~List(); //dtor
		List& operator = (const List& rhs); //copy assignment operator

		List& operator = (List&& rhs) noexcept; //move semantics
		List(List&& original) noexcept; //move semantics
		
		void deleteData(string data); //deletes a node
		void prependList(string data); //prepends list
		void appendList(string data); //appends list
		void insertList(string data); //inserts into the list alphabetically
		void purgeList(); //deletes all nodes
		void displayListFrwd(); //displays list from head to tail
		void displayListBckwd(); //displays list from tail to head



	private:
		Node* m_head; //first item in list
		Node* m_tail; //last item in list
};