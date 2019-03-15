'''
This is the code to apply Linear regression for a dataset of dimension 2, each in [-1,1]. Then the optimal weight is used for PLA classification.
'''
import sys
import os
import numpy as np
import matplotlib.pyplot as plt
import random
from numpy.linalg import inv

def linearRegression():

	# Take N=100 or above for linear Regression, N = 10 to test PLA
	N = 10
	Ein = 0
	Eout = 0
	p1 = [np.random.uniform(-1,1), np.random.uniform(-1,1)]
	p2 = [np.random.uniform(-1,1), np.random.uniform(-1,1)]
		
	# Find the equation of line
	a = p1[1]-p2[1]
	b = p2[0]-p1[0]
	d = -(a*p1[0]+b*p1[1])

	# Calculating slope and intercept
	m = -a/b
	c = -d/b
	y = []
	x = []

	for _ in range(N):
		xn = np.array([np.random.uniform(-1,1), np.random.uniform(-1,1)])
		x.append(xn)

		# Vertical distance is used for comparison
		if m*xn[0]+c > xn[1]:
			y.append(1)
		else:
			y.append(-1)

	x = np.array(x)
	x = np.hstack((np.ones((N,1)),x))
	y = np.array(y).reshape(N,1)
	w = np.matmul(np.matmul(inv(np.matmul(x.T, x)), x.T), y)
	m_hat = -w[1,0]/w[2,0]
	c_hat = -w[0,0]/w[2,0]
	y_hat = []
	for i in range(N):
		# Check every point's misclassification case
		if m_hat*x[i,1]+c_hat > x[i,2]:
			y_hat.append(1)
		else:
			y_hat.append(-1)

	cnt = [1.0 for i in range(N) if y[i,0] != y_hat[i]]
	Ein = sum(cnt)
	Eout = calculateEout(m, c, m_hat, c_hat)
	ite = PLA(N,x.T,y.T,w.T)
	
	# fig, ax = plt.subplots()
	# ax.scatter(x[:,1],x[:,2])
	# plotLines(m_hat, c_hat, 'b', "Function g")
	# plotLines(m, c, 'r', "Function f")
	# plt.legend()
	# plt.show()
	return Ein, Eout, ite


def calculateEout(m, c, m_hat, c_hat):
	# Taking fresh 1000 points to validate Eout
	cnt = 0
	for _ in range(1000):
		p = [np.random.uniform(-1,1), np.random.uniform(-1,1)]

		if m*p[0]+c > p[1]:
			y = 1
		else:
			y = -1

		if m_hat*p[0]+c_hat > p[1]:
			y_hat = 1
		else:
			y_hat = -1

		if y != y_hat:
			cnt += 1
	return cnt


def PLA(N,x,y,w):
	# PLA algorithm
	ite = 0
	val = False
	while not val:
		y_hat = np.matmul(w,x).reshape(1,N)

		classify = [1 if y_hat[0,i]>0 else -1 for i in range(N)]

		misclassified = [1 if y[0,i]!=classify[i] else 0 for i in range(N)]
		
		ind = [i for i in range(N) if misclassified[i]==1]

		if not len(ind):
			val = True
			break

		rn = np.random.randint(0,len(ind))

		w = w + x[:,ind[rn]] * y[0,ind[rn]]

		ite += 1
	return ite

def plotLines(m, c, color,label):
	'''
	Pass slope and intercept value as input.
	'''
	plt.xlim(-1.5,1.5)
	plt.ylim(-5,5)
	plt.plot(np.linspace(-1,1),m*np.linspace(-1,1)+c, color, label = label)

def main():
	Ein = 0
	Eout = 0
	ite = 0
	for _ in range(1000):
		x, y, w = linearRegression()
		Ein += x
		Eout += y
		ite += w

	print 'Avg. Ein:', Ein/10000.0
	print 'Avg. Eout:', Eout/1000000.0
	print 'No. of iterations:', ite/1000.0

if __name__=="__main__":
	main()