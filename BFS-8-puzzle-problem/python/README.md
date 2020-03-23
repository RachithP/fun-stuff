## This is an implementation of Breadth First Search for solving 8-puzzle problem.

To run the file, execute ```python2 bfs_8_puzzle.py``` and follow instructions as shown in console.
NOTE: 
1. Do not input negative numbers.

OUTPUT:
Three .txt files are being output in the current folder:
1. Nodes.txt -> Contains all the nodes traversed until a solution(if exists) is obtained. If no solutions exists, it contains all the possible configurations. Each row corresponds to a node.
2. NodesInfo.txt -> Each row corresponds to node information of each node in Nodes.txt in [node number, parent node number, cost] format.
3. nodePath.txt -> contains path to goal node from initial node. Each row represents a node in the path.

The nodes are stored in this format.
if node is</br>
1 2 3</br>
4 5 6</br>
7 8 0</br>

it is stored as 1 4 7 2 5 8 3 6 0 in the Nodes.txt and nodePath.txt file.

In the example folder, I have uploaded the files that correspond to the input</br>
6 5 8</br>
2 7 3</br>
4 1 0

The process goes as follows:

```bash
>>python rprakas2_project1.py
INFO:	Input Initial node configuration. Numbers are parsed row-wise upto 3 elements in each row.
INFO:	Don't forget that '0' represents the empty space.
INFO:	Press [ENTER] after every number:
6
5
8
2
7
3
4
1
0

INFO:	Matrix being input:
[[6 5 8]
 [2 7 3]
 [4 1 0]] 

INFO:	If this is the matrix you wanted as initial configuration, press [y]. Else press [n] and retry.
y

INFO:	Goal node is:
[[1 2 3]
 [4 5 6]
 [7 8 0]]

Calculating path to goal node, hold on!!....


INFO:	Path to Goal node is as follows

[[6 5 8]
 [2 7 3]
 [4 1 0]] 

[[6 5 8]
 [2 7 0]
 [4 1 3]] 

[[6 5 8]
 [2 0 7]
 [4 1 3]] 

[[6 5 8]
 [2 1 7]
 [4 0 3]] 

[[6 5 8]
 [2 1 7]
 [4 3 0]] 

[[6 5 8]
 [2 1 0]
 [4 3 7]] 

[[6 5 0]
 [2 1 8]
 [4 3 7]] 

[[6 0 5]
 [2 1 8]
 [4 3 7]] 

[[0 6 5]
 [2 1 8]
 [4 3 7]] 

[[2 6 5]
 [0 1 8]
 [4 3 7]] 

[[2 6 5]
 [1 0 8]
 [4 3 7]] 

[[2 6 5]
 [1 3 8]
 [4 0 7]] 

[[2 6 5]
 [1 3 8]
 [4 7 0]] 

[[2 6 5]
 [1 3 0]
 [4 7 8]] 

[[2 6 5]
 [1 0 3]
 [4 7 8]] 

[[2 0 5]
 [1 6 3]
 [4 7 8]] 

[[2 5 0]
 [1 6 3]
 [4 7 8]] 

[[2 5 3]
 [1 6 0]
 [4 7 8]] 

[[2 5 3]
 [1 0 6]
 [4 7 8]] 

[[2 0 3]
 [1 5 6]
 [4 7 8]] 

[[0 2 3]
 [1 5 6]
 [4 7 8]] 

[[1 2 3]
 [0 5 6]
 [4 7 8]] 

[[1 2 3]
 [4 5 6]
 [0 7 8]] 

[[1 2 3]
 [4 5 6]
 [7 0 8]] 

[[1 2 3]
 [4 5 6]
 [7 8 0]]

```
In order to visualize the path to goal node,run the plotOutput_text.m file in the 'File to Visualize....' folder. Run it as the following in the command window of MATLAB ```plotOutput_text "<path_to_nodepath.txt>"```
CREDITS: ![Ashwin Goyal](https://www.linkedin.com/in/ashwin-goyal/) for creating this UI in MATLAB.

Visualization that you will get is as shown below
![visualization](https://github.com/RachithP/fun-stuff/blob/master/BFS-8-puzzle-problem/Example/visualization.gif)
