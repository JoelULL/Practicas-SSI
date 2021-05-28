# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 5 de Marzo de 2021
# Archivo Makefile para el programa rc4

CXXFLAGS = -g -Wall
CXX = g++
OBJS = rc4.o main.o 
BINARY = rc4

all: rc4

rc4: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  