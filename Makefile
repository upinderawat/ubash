CC= g++
CFLAGS= -Wall
ubash:main
	@echo "ubash started"
main: main.cpp utils.cpp execute_cmd.cpp
	@echo "Resolving dependencies.."
	@$(CC) $(CFLAGS) -o main.o main.cpp execute_cmd.cpp utils.cpp -I. 

clean:
	@echo "Deleting old binaries"
	rm main.o

