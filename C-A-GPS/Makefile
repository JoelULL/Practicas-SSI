# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 17 de Marzo de 2021
# Archivo Makefile para el programa c/a gps

CXXFLAGS = -g -Wall
CXX = g++
OBJS = cagps.o main.o 
BINARY = cagps

all: cagps

cagps: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
