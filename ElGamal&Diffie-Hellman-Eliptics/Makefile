# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 8 de mayo de 2021
# Archivo Makefile para el programa eliptic

CXXFLAGS = -g -Wall
CXX = g++
OBJS = eldifhel.o main.o 
BINARY = eliptic

all: eliptic

eliptic: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  