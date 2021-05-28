# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 25 de Febrero de 2021
# Archivo Makefile para el programa vigenere

CXXFLAGS = -g -Wall
CXX = g++
OBJS = vigenere.o main.o 
BINARY = vigenere

all: vigenere

vigenere: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
