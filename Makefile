CC= gcc
CFLAGS= -Wall
ubash:main
	@echo "ubash started"
main: 
	@echo "Resolving dependencies.."
	@$(CC) $(CFLAGS) main.c -o main.o
clean:
	@echo "Deleting old binaries"
	rm main.o