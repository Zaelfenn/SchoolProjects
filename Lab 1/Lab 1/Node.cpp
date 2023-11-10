#include "Node.h"

Node::Node() : m_data(""), m_next(nullptr), m_prev(nullptr) //default ctor
{}

Node::Node(string data) : m_data(data), m_next(nullptr), m_prev(nullptr) //non default ctor
{}

Node::Node(const Node& original) : m_data(), m_next(nullptr), m_prev(nullptr) //copy ctor
{
	m_data = original.m_data;
}

Node::~Node() //dtor
{
	m_data = "";
	m_next = nullptr; //sets everything to "base node"
	m_prev = nullptr;

}

/* //setters and getters no longer needed
void Node::setData(string data) //setter for data
{
	m_data = data;
}

string Node::getData() //getter for data
{
	return m_data;
}

void Node::setNext(Node* next) //setter for next node in list
{
	m_next = next;
}

Node* Node::getNext() //getter for next node in list
{
	return m_next;
}

void Node::setPrev(Node* prev) //setter for previous node in list
{
	m_prev = prev;
}

Node* Node::getPrev() //getter for previous node in list
{
	return m_prev;
}
*/
Node& Node::operator = (const Node& rhs) //copy assignment operator
{
	if (this != &rhs) //if these arent the same node
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next; //make them the same node
		m_prev = rhs.m_prev;
	}
	return *this;
}