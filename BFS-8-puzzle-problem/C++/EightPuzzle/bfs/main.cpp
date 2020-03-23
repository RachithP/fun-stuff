#include <stdio.h>
#include "src/Node/node.h"
#include "src/Move/move.h"
#include <unordered_set>
#include <queue>
#include <stack>

using std::cout;
using std::endl;
using std::cin;
using std::string;
typedef std::unordered_set<string> un_set;


bool solve(std::queue<std::shared_ptr<Node>>& q, std::shared_ptr<Node> goal, un_set& mem){
	
std::shared_ptr<Node> currentNode{NULL}, n{NULL};
	
	bool flag = false;
	
	// Start exploring in BFS fashion
	while(true){
		
		currentNode = q.front();
		q.pop();
		
		if(currentNode->getStringValue() == goal->getStringValue()){
			goal->assignParent(currentNode);
			flag = true;
			break;
		}
		
		if(mem.size()>=181440) break;
		
		// Move up
		n = std::make_shared<Node>(*currentNode);
		n->up();
		if(mem.find(n->getStringValue())==mem.end()){
			mem.insert(n->getStringValue());
			n->assignParent(currentNode);
			q.push(n);
		}
		else{
			n.reset();
			n = NULL;
		}
		
		// Move down
		n = std::make_shared<Node>(*currentNode);
		n->down();
		if(mem.find(n->getStringValue())==mem.end()){
			mem.insert(n->getStringValue());
			n->assignParent(currentNode);
			q.push(n);
		}
		else{
			n.reset();
			n = NULL;
		}
		
		// Move left
		n = std::make_shared<Node>(*currentNode);
		n->left();
		if(mem.find(n->getStringValue())==mem.end()){
			mem.insert(n->getStringValue());
			n->assignParent(currentNode);
			q.push(n);
		}
		else{
			n.reset();
			n = NULL;
		}
		
		// Move right
		n = std::make_shared<Node>(*currentNode);
		n->right();
		if(mem.find(n->getStringValue())==mem.end()){
			mem.insert(n->getStringValue());
			n->assignParent(currentNode);
			q.push(n);
		}
		else{
			n.reset();
			n = NULL;
		}
	}
	return flag;
}

void printPath(std::shared_ptr<Node> start, std::shared_ptr<Node> goal){
	
	std::shared_ptr<Node> cur = goal->getParent();
	std::stack<std::shared_ptr<Node>> stk;
	while(cur!=start){
		stk.push(cur);
		cur = cur->getParent();
	}
	stk.push(start);
	
	while( not stk.empty() ){
		cur = stk.top();
		stk.pop();
		cur->printNode();
		cout << endl;
	}
}

int main(int argc, char **argv)
{
	// Define start, goal nodes
	
	cout << "#INFO Enter all 9 unique numbers in the range 0-8 in order of your choice.\n";
	cout << "#INFO Press [ENTER] after each number\n";
	std::string s;
	for(int i = 0; i<9; ++i){
		int x;
		cin >> x;
		s += std::to_string(x);
	}
	cout << "#INFO Entered Node is " << endl;
	std::shared_ptr<Node> start = std::make_shared<Node>(s);
	start->printNode();

//	std::shared_ptr<Node> start = std::make_shared<Node>(std::string("123456708"));
	std::shared_ptr<Node> goal = std::make_shared<Node>(std::string("123456780"));
	cout << "#INFO Need to solve for " << endl;
	goal->printNode();
	
	// Queue and memory for keeping track of visited nodes
	std::unordered_set<string> mem; // To keep a track of all nodes explored till now.
	std::queue<std::shared_ptr<Node>> qu; // For BFS
	
	qu.push(start);
	mem.insert(start->getStringValue()); // Add start and end to memory
	
	if( solve(qu, goal, mem) ){
		cout << "#AWESOME! Solved, Now lets print the path\n";
		printPath(start, goal);
	}
	else{
		cout << "#DAMN!, No path exists :( @_@ \n";
	}
	
	return 0;
	
}
