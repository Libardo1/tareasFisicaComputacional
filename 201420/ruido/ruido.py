import numpy as np 
import scipy
import matplotlib.pyplot as plt
from pprint import pprint 
from scipy.fftpack import fft, fftfreq, ifft

# Generar ruido blanco 
m = 500
r = np.random.randn(m,1)

# Grafica del Ruido Blanco
plt.plot(r)
plt.title('Ruido Blanco')
plt.grid()
plt.show()

#Parte 1: Transformada de fourier
fft_ = fft(r) / m # FFT Normalized
timestep = 1.0
freq_ = fftfreq(m, d=timestep)
ifft_ = ifft(fft_)

# Parte 2: Transformada y antitransformada
plt.plot(fft_)
plt.title('Transformada')
plt.grid()
plt.show()

plt.plot(ifft_)
plt.title('Antitransformada')
plt.grid()
plt.show()

pprint('La transformada de fourier del ruido blanco muestra que este es totalmente aleatorio y no existe componentes deterministicos en los cuales se pueda descomponer. Haciendo un analisis de las frencuencias se encuentra que no hay ninguna predominante.')

# Parte 2: potencias vs frecuencias
fnew = np.fft.fftshift(freq_)
fftnew = np.fft.fftshift(fft_)
P = np.abs(fftnew)**2

plt.plot(fnew, P)
plt.ylabel('Potencias')
plt.xlabel('Frecuencias')
plt.scatter(fnew, P)
plt.grid()
plt.show()
