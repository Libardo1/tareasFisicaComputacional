import sys
import numpy as np
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
archivo =sys.argv[1]
data = np.loadtxt(archivo)
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
x = np.linspace(0,100,101)
for i in range(len(data)):
    t = [ i for j in range(len(data[i]))]
    plt.plot(t, x, data[i], color='g')
ax.set_xlabel('Tiempo [seg]')
ax.set_ylabel('Posicion [mts]')
ax.set_zlabel('Amplitud [mts]')
plt.savefig('string_'+ archivo[7:15] +'.pdf')
