CC= g++
CFLAGS= -Wall
ubash:main
	@echo "ubash started"

main: utils.o execute_cmd.o 
	@echo "Resolving dependencies.."
	@$(CC) $(CFLAGS) -o main.o main.cpp execute_cmd.o utils.o builtins.o

execute_cmd.o: execute_cmd.h utils.o builtins.o

builtins.o: builtins.h

utils.o:utils.h

clean:
	@echo "Deleting old binaries"
	rm *.o

