CC=gcc
 
MYDIR=~/Escritorio/Tercero/SSI/kasumi
 
INCLUDE=-I./
OPTIONS=-o
 
TARGET=kasumi_f8_f9.o
 
SRCS=$(MYDIR)/f9.cc \
	$(MYDIR)/f8.cc \
	$(MYDIR)/kasumi.cc \
	$(MYDIR)/main.cc
 
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(SRCS)
 
.PHONY: clobber
clobber:
	rm -rf *.o
clean:
	rm -rf *.o