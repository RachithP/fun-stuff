'''
This is the code to apply non-linear transform on the dataset to obatined non-linear feature vectors 
and show that it is sometimes better to convert data first and do classification.
'''
import sys
import os
import numpy as np
import matplotlib.pyplot as plt
import random
from numpy.linalg import inv

def nonLinear():
	Ein = 0
	# 1000 data points
	N = 1000
	y = []
	x = []
	x_nt = []
	misclf = []
	cnt = 0
	pos = []
	neg = []

	# Calculation of data points
	for _ in range(1000):
		p = [np.random.uniform(-1,1), np.random.uniform(-1,1)]
		x.append(p)
		x_nt.append([1,p[0],p[1],p[0]*p[1],p[0]**2,p[1]**2]) # Non-linear transform is applied
		if p[0]**2 + p[1]**2 - 0.6 > 0:
			y.append(1)
			pos.append(p)
		else:
			y.append(-1)
			neg.append(p)
	# Storting + and - classified points
	pos = np.array(pos)
	neg = np.array(neg)
	# Generate noise for 10% of data by inverting it's value, chosen randomly
	for j in range(100):
		y[j] = y[j] * -1		

	x = np.array(x)
	x = np.hstack((np.ones((N,1)),x))
	y = np.array(y).reshape(N,1)
	# Solve for w with linear regression.
	w = np.matmul(np.matmul(inv(np.matmul(x.T, x)), x.T), y)

	m_hat = -w[1,0]/w[2,0]
	c_hat = -w[0,0]/w[2,0]
	y_hat = []
	# Check for error in sample
	for i in range(N):
		# Check every point's misclassification case
		if m_hat*x[i,1]+c_hat > x[i,2]:
			y_hat.append(1)
		else:
			y_hat.append(-1)
	# Check for error in sample
	for i in range(N):
		if y[i,0] != y_hat[i]:
			cnt += 1
	Ein = cnt/1000.0 # E_in for linear regression.

	x_nt = np.array(x_nt)
	# Non-linear feature vector's linear regression.
	w_nt = np.matmul(np.matmul(inv(np.matmul(x_nt.T, x_nt)), x_nt.T), y)
	cnt = 0
	y_hat = np.matmul(x_nt,w_nt)
	pos_nt = []
	neg_nt = []
	for k in range(N):
		if y_hat[k] > 0:
			t = 1
			pos_nt.append([x_nt[k,1], x_nt[k,2]])
		else:
			t = -1
			neg_nt.append([x_nt[k,1], x_nt[k,2]])
		if y[k] != t:
			cnt += 1
			misclf.append([x_nt[k,1], x_nt[k,2]])
	pos_nt = np.array(pos_nt)
	neg_nt = np.array(neg_nt)
	misclf = np.array(misclf)
	Ein_nt = cnt/1000.0 # E_in for non-linear feature vector.

	# fig, ax = plt.subplots()
	# ax.scatter(pos[:,0], pos[:,1], label="Points classified as +1")
	# ax.scatter(neg[:,0], neg[:,1], label="Points classified as -1")
	# # plt.plot(x[:,1],x[:,2], 'go', label="Data points")
	# # plt.plot(pos_nt[:,0],pos_nt[:,1], 'r.', label="Non-Linear: Points classified as +1")
	# # plt.plot(neg_nt[:,0],neg_nt[:,1], 'b.', label="Non-Linear: Points classified as -1")
	# plt.plot(misclf[:,0],misclf[:,1], 'ro', label="Points Misclassified by non-linear transform")
	# # plotLines(m_hat, c_hat, 'b', "Function g")
	# plt.legend()
	# plt.xlim(-1.5,1.5)
	# plt.ylim(-5,5)
	# plt.show()
	Eout = calculateEout(w_nt)
	return Ein, Ein_nt, Eout

def calculateEout(w):
	cnt = 0
	x = []
	y = []
	N = 1000
	misclf = []
	for _ in range(N):
		p = [np.random.uniform(-1,1), np.random.uniform(-1,1)]
		x.append([1,p[0],p[1],p[0]*p[1],p[0]**2,p[1]**2])
		if p[0]**2 + p[1]**2 - 0.6 > 0:
			y.append(1)
		else:
			y.append(-1)
	# Adding noise to 100 points as before
	for i in range(100):
		y[i] = y[i] * -1

	x = np.array(x)
	y = np.array(y).reshape(N,1)
	y_hat = np.matmul(x,w)

	for i in range(N):
		if y_hat[i] > 0:
			y_hat[i] = 1
		else:
			y_hat[i] = -1

		if y[i] != y_hat[i]:
			misclf.append([x[i,1],x[i,2]])
			cnt += 1
	misclf = np.array(misclf)
	return cnt/1000.0

def main():

	Ein = 0
	Ein_nt = 0
	E_out = 0
	for _ in range(1000):
		x, y, z = nonLinear()
		Ein += x
		Ein_nt += y
		E_out += z
	print 'Ein linear for 1000 iterations:', Ein/1000.0
	print 'Ein non-linear for 1000 iterations:', Ein_nt/1000.0
	print 'Eout non-linearfor 1000 iterations:', E_out/1000.0
	

if __name__ == "__main__":
	main()