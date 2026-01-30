NAME = cih

CC = clang
CFLAGS = -std=c99 -Wall -Wextra -pedantic -I./
LDFLAGS = 

LIBS = sdl3
CFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS += $(shell pkg-config --libs $(LIBS))

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# TODO optional
DEBUGFLAGS = -O0 -g
CFLAGS += $(DEBUGFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

run: all
	./$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

ren: fclean run

.PHONY: all run clean fclean re ren
