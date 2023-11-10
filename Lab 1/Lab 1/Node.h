#pragma once
#include <string>
using std::string;
class Node {
	friend class List;
	private:
		Node(); //default ctor
		Node(string data); //non default ctor
		Node(const Node& original); //copy ctor
		~Node(); //destructor
		/* setters and getters (no longer needed)
		void setData(string data); //setter
		string getData(); //getter
		void setNext(Node* next); //setter
		Node* getNext(); //getter
		void setPrev(Node* prev); //setter
		Node* getPrev(); //getter
		*/
		Node& operator = (const Node& rhs); //copy assignment operator

	
		Node* m_next; //next node in list
		Node* m_prev; //previous node in list
		string m_data; //data in node

};