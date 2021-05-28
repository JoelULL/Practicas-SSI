# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Seguridad en sistemas informáticos
# Autor Joel Aday Dorta Hernandez
# Fecha 15 de Mayo de 2021
# Archivo Makefile para el programa menu

CXXFLAGS = -g -Wall
CXX = g++
OBJS = menu.o vigenere.o rc4.o chacha20.o cagps.o binarymul.o aes.o cbc.o diffie.o gamal.o rsa.o eldifhel.o fefisha.o main.o 
BINARY = menu

all: menu

menu: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINARY)

clean:
	rm -f $(BINARY) $(OBJS)  
