import os
import numpy as np
import math as m
import random
from sets import Set

def passBlankTileLocation(node):

	# for i in np.nditer(node):
	return np.where(node == 0)

def moveLeft(node):

	row, col = np.where(node == 0)

	if col == 0:
		return None
	else:
		node[row,col-1], node[row,col] = node[row,col], node[row,col-1]
		return node

def moveRight(node):

	row, col = np.where(node == 0)

	if col == node.shape[1]-1:
		return None
	else:
		node[row,col+1], node[row,col] = node[row,col], node[row,col+1]
		return node

def moveUp(node):

	row, col = np.where(node == 0)

	if row == 0:
		return None
	else:
		node[row-1,col], node[row,col] = node[row,col], node[row-1,col]
		return node

def moveDown(node):

	row, col = np.where(node == 0)

	if row == node.shape[0]-1:
		return None
	else:
		node[row+1,col], node[row,col] = node[row,col], node[row+1,col]
		return node

def convert2int(data):
	t = 0
	data = data.reshape(9,1)
	for i in range(0,9):
		t = t + data[8-i]*10**i
	return np.int64(t)

def addNode(comp_list, node, nodes, goal_node, nodes_info, parent_number):
	exist = False
	val, achieve = 0, 0

	t = convert2int(node)

	if t in comp_list:
		exist = True

	if exist is False:
		comp_list.add(t)
		nodes.append(node)
		node_number = nodes_info[len(nodes_info)-1][0] + 1
		nodes_info.append([node_number, parent_number, 0])
		s = node_number+1
		p = parent_number+1
		f = open('NodesInfo.txt', 'a')
		f.write('%d\t' % s)
		f.write('%d\t' % p)
		f.write('%d\n' % 0)
		f.close()
		file = open('Nodes.txt', 'a')
		node = np.array(node.T).reshape(9,1)
		for ele in node:
			file.write('%d\t' %ele[0])
		file.write('\n')
		file.close()
		val = 1

	if goalCheck(t, goal_node):
		achieve = 1
	return val, achieve

def goalCheck(node, final):
	if node == final:
		return 1
	else:
		return 0	

def isSolvable(data):
	row, col = data.shape
	count = 0
	for i in range(row-1):
		for j in range(i+1,col):
			if data[j,i] and data[j,i]>data[i,j]:
				count += 1

	if count%2==0:
		return True
	else:
		return False

def main():
	# initial_node = random.sample([[i] for i in range(9)], 9)
	print "INFO:	Input Initial node configuration. Numbers are parsed row-wise upto 3 elements in each row."
	print "INFO:	Don't forget that '0' represents the empty space."
	print "INFO:	Press [ENTER] after every number:"
	initial_node = []
	for _ in range(9):
		initial_node.append(map(int,raw_input()))

	# Testing for wrong inputs, i.e num>9 or <0 or does not contain 0
	zero = False
	c = 0
	for i in initial_node:
		if i[0] == 0:
			c += 1
			zero = True
		if i[0] > 8 or i[0] < 0:
			print "ERROR:	Input numbers in range [0-8]."
			quit()
	if not zero:
		print "ERROR:	Your initial configuration does not have an empty space. Make sure it has '0' as an empty space."
		quit()
	if c > 1:
		print "ERROR:	Cannot input more than one empty space."
		quit()
	initial_node = np.array(initial_node).reshape(3,3)

	if len(np.unique(initial_node)) != 9:
		print "ERROR:	Input does not contain all elements required in goal node. Try again."
		quit()

	print "\nINFO:	Matrix being input:\n", initial_node, "\n"
	print "INFO:	If this is the matrix you wanted as initial configuration, press [y]. Else press [n] and retry."
	response = raw_input()
	if response == 'n':
		quit()

	# # Solvability check
	# status = isSolvable(initial_node)
	# if not status:
	# 	print "\nThis configuration is not solvable. Please input another configuration."
	# 	quit()
	# else:
	# 	print "\nThis configuration is solvable. Let's see how!!"

	# Goal Node
	goal_node = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 0]])
	print "\nINFO:	Goal node is:\n", goal_node
	print "\nCalculating path to goal node, hold on!!....\n"
	
	# Converting goal node to int for faster processing.
	goal_node = convert2int(goal_node)

	# Few initial def
	nodes_info = [[0,0,0]]
	nodes = [initial_node]
	success = 0
	row_iter = [0,1]
	flag = False
	comp_list = Set([])

	# Making sure files are made empty before writing into them.
	open('Nodes.txt','w').close()
	open('nodePath.txt','w').close()
	open('NodesInfo.txt','w').close()

	# Write initial values to file
	f = open('NodesInfo.txt', 'a')
	f.write('%d\t' %1)
	f.write('%d\t' %1)
	f.write('%d\n' %0)
	f.close()
	file = open('Nodes.txt', 'a')
	node = np.array(initial_node.copy().T).reshape(9,1)
	for ele in node:
		file.write('%d\t' %ele[0])
	file.write('\n')
	file.close()

	# Creating an int from initial_node for passing it to a set for faster processing.
	ini = convert2int(initial_node.copy())
	comp_list.add(ini)

	while success != 1:

		if len(comp_list) >= 181440:
			print "\nINFO:	All possible nodes reached. Solution does not exist for your initial configuration.\n"
			print "\nINFO:	Check output files for more details."
			break

		val = 0

		for itr, current_node in enumerate(nodes[row_iter[0]:]):
			newnode = moveLeft(current_node.copy())
			if newnode is not None:
				num, success = addNode(comp_list, newnode, nodes, goal_node, nodes_info, row_iter[0]+itr)
				val += num
				if success:
					flag = True

			newnode = moveUp(current_node.copy())
			if newnode is not None:
				num, success = addNode(comp_list, newnode, nodes, goal_node, nodes_info, row_iter[0]+itr)
				val += num
				if success:
					flag = True
				
			newnode = moveRight(current_node.copy())
			if newnode is not None:
				num, success = addNode(comp_list, newnode, nodes, goal_node, nodes_info, row_iter[0]+itr)
				val += num
				if success:
					flag = True

			newnode = moveDown(current_node.copy())
			if newnode is not None:
				num, success = addNode(comp_list, newnode, nodes, goal_node, nodes_info, row_iter[0]+itr)
				val += num
				if success:
					flag = True	

			if flag:
				nodes = np.array(nodes)
				nodes_info = np.array(nodes_info)
				final_path = []
				val = nodes_info[nodes_info.shape[0]-1,0]
				while val != 0:
					final_path.append(nodes[val][:][:])
					val = nodes_info[val,1]
				final_path.append(initial_node)
				print "\nINFO:	Path to Goal node is as follows\n"
				f = open('nodePath.txt','a')
				for node in reversed(final_path):
					print node, "\n"
					node = np.array(node.T).reshape(9,1)
					for ele in node:
						f.write('%d' % ele[0])
						f.write('\t')
					f.write('\n')
				f.close()

				break

		row_iter[0] = row_iter[0] + row_iter[1]
		row_iter[1] = val	

if __name__ == "__main__":
	main()