'''
This is the code for validating Hoeffding bound for single bin.
'''

import sys, os
import numpy as np
import random

# Heads = 1, tails = 0
coins = 1000
tosses = 10
experiments = 100000
sig_v1 = 0
sig_vrand = 0
sig_vmin = 0

# Since, N = 10, lets choose e=0.2 and e=0.3 to check Hoeffding inequality
# e=0.1 gives probability of bound as 1.6 which is not useful.
e = 0.2
E_out = 0.5 # Eout is 0.5 as 50% chance of getting an head or tail.

for i in range(experiments):
	stack = np.zeros((1,10), dtype=int)
	for _ in range(coins):
		P = []
		for _ in range(tosses):	
			P.append(random.randint(0,1))
		stack = np.vstack((stack, P))

	stack = np.delete(stack,0,0)

	# c1
	c1 = stack[0,:]
	v1 = sum([1 for i in c1 if i == 1])/10.0
	if abs(v1-E_out)>e:
		sig_v1 += 1.0
	# C rand
	ind = random.randint(0,999)
	crand = stack[ind,:]
	vrand = sum([1 for i in crand if i == 1])/10.0
	if abs(vrand-E_out)>e:
		sig_vrand += 1.0

	#c min
	ind = np.argmin(np.sum(stack, axis=1))
	cmin = stack[ind,:]
	vmin = sum([1 for i in cmin if i == 1])/10.0
	if abs(vmin-E_out)>e:
		sig_vmin += 1.0


print 'Average probability of v1: ', sig_v1/experiments
print 'Average probability of vrand: ', sig_vrand/experiments
print 'Average probability of vmin: ', sig_vmin/experiments