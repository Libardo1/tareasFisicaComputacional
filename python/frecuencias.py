
import sys, string, os

# se carga el archivo 
ar= sys.argv[1]
infile=open(ar)
text= infile.readlines()
infile.close()
a=0
b=0
c=0
d=0

# se elimina los espacios y demas simbolos en cada fila del documento
#tam = len(text)
#for a in text(tam):
#    text[a]=text[a].rstrip('\n')
#    text[a]=text[a].rstrip(' ')
        
# convertir en una lista los arreglos de cada fila 
#for b in range(tam):
#    if b==0:
#        texto= list(text[b])
#    else:
#        texto+=list(text[b])    

# se crea la biblioteca de cada libro con los caracteres dentro de el
biblioteca = []
for line in text:
    for letter in line:
        biblioteca.append(letter)

biblioteca = list(set(biblioteca))

paraquitar = ['\n', ' ']
for item in paraquitar:
    biblioteca.remove(item)
print biblioteca
# se calcula la frecuencia de cada caracter


ssize=len(biblioteca)
frecuencia=range(ssize)

for i in range(len(frecuencia)):
    frecuencia[i] =0

for line in text:
    for c in range(len(biblioteca)):
        frecuencia[c] += line.count(biblioteca[c])

# se crea un arhivo 
grabado=open("frecuencias_"+ar, "w")

for d in range(ssize):
    grabado.write("%s %d\n"%(biblioteca[d], frecuencia[d]))
grabado.close()


