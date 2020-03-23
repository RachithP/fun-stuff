#pragma once

#include <iostream>
#include <vector>
#include "src/Move/move.h"
#include <memory>

using std::vector;

class Node : public Move
{
public:
	// Constructors
	Node();
	Node(std::string);
	
	// Destrcutors
	virtual ~Node();
	
	// Member functions
	void assignParent(const std::shared_ptr<Node>);
	std::shared_ptr<Node> getParent() const;
	void printNode() const;
	std::string getStringValue() const;
	
	// overload operator
	void operator = (Node& x){
		strValue_ = x.strValue_;
	}
	
	// Overriden member functions
	virtual void up() override;
	virtual void down() override;
	virtual void left() override;
	virtual void right() override;
	
private:
	std::string strValue_;
	std::shared_ptr<Node> parent_;
	std::string convert2String() const;
};

