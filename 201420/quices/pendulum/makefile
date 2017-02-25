all: data.pdf

data.pdf: data.dat grafica.py
	python grafica.py

data.dat: pendulum.py
	python pendulum.py 5 0.9 1

clear: 
	rm -f data.*
