# Variables
CC=g++

# Targets
all:
	g++ -g src/Main.cpp -o bin/renderfarm-0.1a-win32.exe -lm
	
clean:
	rm bin/renderfarm-0.1a-win32.exe