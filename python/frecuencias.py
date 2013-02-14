
import sys, string, os
# se carga el archivo 
ar= sys.argv[1]
infile=open(ar)
text= infile.readlines()
#text=u(text)
infile.close()
a=0
b=0
c=0
d=0

# se crea la biblioteca de cada libro con los caracter
biblioteca = []
#text= unicode(text,"utf-8")

for line in text:
    for letter in line:
        biblioteca.append(letter)
biblioteca = list(set(biblioteca))

# se remueve los caracteres no deseados
paraquitar = ['\n', ' ']
for item in paraquitar:
    biblioteca.remove(item)

# se calcula la frecuencia de cada caracter
ssize=len(biblioteca)
frecuencia=range(ssize)
for i in range(len(frecuencia)):
    frecuencia[i] =0
for line in text:
    for c in range(ssize):
        frecuencia[c] += line.count(biblioteca[c])

# se crea un arhivo de texto para guardar los datos de frecuencia  
grabado=open("frecuencias_"+ar, "w")

for d in range(ssize):
    grabado.write("%s %d\n"%(biblioteca[d], frecuencia[d]))
grabado.close()



