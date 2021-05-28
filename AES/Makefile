# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 4 de abril de 2021
# Archivo Makefile para el programa aes

CXXFLAGS = -g -Wall
CXX = g++
OBJS = aes.o main.o 
BINARY = aes

all: aes

aes: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  