## This is an implementation of Breadth First Search for solving 8-puzzle problem.

To run the file, execute 'python2 rprakas2_project1.py' and follow instructions as shown in console.
NOTE: 
1. Do not input negative numbers.

OUTPUT:
Three .txt files are being output in the current folder:
1. Nodes.txt -> Contains all the nodes traversed until a solution(if exists) is obtained. If no solutions exists, it contains all the possible configurations. Each row corresponds to a node.
2. NodesInfo.txt -> Each row corresponds to node information of each node in Nodes.txt in [node number, parent node number, cost] format.
3. nodePath.txt -> contains path to goal node from initial node. Each row represents a node in the path.

The nodes are stored in this format.
if node is,
	1 2 3
	4 5 6
	7 8 0
it is stored as 1 4 7 2 5 8 3 6 0 in the Nodes.txt and nodePath.txt file.
