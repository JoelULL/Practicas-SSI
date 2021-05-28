# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 31 de Marzo de 2021
# Archivo Makefile para el programa binarymul

CXXFLAGS = -g -Wall
CXX = g++
OBJS = binarymul.o main.o 
BINARY = binarymul

all: binarymul

binarymul: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  