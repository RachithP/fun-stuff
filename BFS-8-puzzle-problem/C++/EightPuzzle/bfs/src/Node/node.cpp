#include "node.h"
#include <math.h>
#include <string>

using std::vector;
using std::swap;

Node::Node()
{
//	std::cout << "Node non-parameterized constructor called...\n";
	strValue_ = "";
	parent_ = NULL;
}

Node::Node(std::string x)
{
//	std::cout << "Node parameterized constructor called...\n";
	strValue_ = x;
	parent_ = NULL;
}

Node::~Node()
{
//	std::cout << "Node destrcutor called...\n";
}

void Node::assignParent(const std::shared_ptr<Node> p){
	parent_ = p;
}

std::shared_ptr<Node> Node::getParent() const{
	return parent_;
}

void Node::up(){
	int coord = strValue_.find('0');
	if(coord>=3) swap(strValue_[coord], strValue_[coord-3]);
}

void Node::down(){
	int coord = strValue_.find('0');
	if(coord<=5) swap(strValue_[coord], strValue_[coord+3]);
}

void Node::left(){
	int coord = strValue_.find('0');
	if(coord!=0 and coord!=3 and coord!=6) swap(strValue_[coord], strValue_[coord-1]);
}

void Node::right(){
	int coord = strValue_.find('0');
	if(coord!=2 and coord!=5 and coord!=8) swap(strValue_[coord], strValue_[coord+1]);
}

std::string Node::getStringValue() const{
	return strValue_;
}

void Node::printNode() const
{
	for(int k=0;  k<strValue_.length();++k){
		std::cout << strValue_[k] << " ";
		if( (k+1)%3==0 ) std::cout << "\n";
	}
}