CC = g++
HELPERSPATH = ../gr_helpers/
INCLPATH = ./ $(HELPERSPATH)
CFLAGS = -std=c++17 $(foreach H, $(INCLPATH), -I$(H)) -g
MAIN = main.cpp
HELPERS = $(HELPERSPATH)*.cpp
EXEC = ./a.out

all: $(EXEC)

$(EXEC) : $(MAIN) $(HELPERS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXEC)

re : fclean all

run: $(EXEC)
	./$^

crun: $(EXEC)
	clear
	./$^

.PHONY: all clean fclean re run crun