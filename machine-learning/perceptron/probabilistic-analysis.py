import os
import sys
import matplotlib.pyplot as plt
import numpy as np

# Number of input points
N = 100
count = 0
cnt = 0

# Running PLA algorithm 1000times to get average
for _ in range(1000):

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

		if m*xn[0]+c > xn[1]:
			y.append(1)
		else:
			y.append(-1)

	x = np.array(x).T
	y = np.array(y).reshape(1,N)

	fig, ax = plt.subplots()
	plt.plot(np.linspace(-1,1),m*np.linspace(-1,1)+c)
	ax.scatter(x[0],x[1])
	plt.xlim(-1.5,1.5)
	plt.ylim(-5,5)
	# for i in range(N):
	    # ax.annotate(i, (x[0,i], x[1,i]))

	# Define weight vector according to size of d, x0 = 1, w0 = bias
	w = np.zeros((1,3))
	x = np.insert(x,0,np.ones((1,N)),axis=0)

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

		slope = -w[0,1]/w[0,2]
		intercept = -w[0,0]/w[0,2]

		ite += 1
	
	count += ite

	# Approximating the probability of misclassification on a random point
	# 1000 samples taken into consideration
	for _ in range(1000):
		p = [np.random.uniform(-1,1), np.random.uniform(-1,1)]
		if m*p[0]+c > p[1]:
			f = 1
		else:
			f = 0

		if slope*p[0]+intercept > p[1]:
			g = 1
		else:
			g = 0

		if f!=g:
			cnt += 1


	plt.plot(np.linspace(-1,1),slope*np.linspace(-1,1)+intercept, 'r')
	plt.axhline(y=1, color='g', linestyle=':')
	plt.axhline(y=-1, color='g', linestyle=':')
	plt.axvline(x=-1, color='g', linestyle=':')
	plt.axvline(x=1, color='g', linestyle=':')
	plt.show()

print "avg iterations: ", count/1000.0
print "avg probability of miscl: ", cnt/1000000.0