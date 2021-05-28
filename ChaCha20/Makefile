# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 10 de Marzo de 2021
# Archivo Makefile para el programa chacha20

CXXFLAGS = -g -Wall
CXX = g++
OBJS = chacha20.o main.o 
BINARY = chacha20

all: chacha20

chacha20: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  