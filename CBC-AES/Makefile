# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 15 de abril de 2021
# Archivo Makefile para el programa cbc

CXXFLAGS = -g -Wall
CXX = g++
OBJS = cbc.o aes.o main.o 
BINARY = cbc

all: cbc

cbc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  