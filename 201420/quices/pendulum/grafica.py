import numpy as np  
import matplotlib.pyplot as plt

figura = plt.figure()
ax = plt.axes()
data = np.loadtxt('data.dat')
ax.plot(data[:,0], data[:,1])
plt.savefig('data.pdf')
