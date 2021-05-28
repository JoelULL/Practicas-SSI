# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 21 de abril de 2021
# Archivo Makefile para el programa difhel

CXXFLAGS = -g -Wall
CXX = g++
OBJS = diffie.o gamal.o main.o 
BINARY = difhel

all: difhel

difhel: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
