SRC = $(shell find src/ -type f -name "*.c")

OBJ = $(SRC:src/%.c=obj/%.o)

RED = \033[1;31m

GREEN = \033[1;32m

BLUE = \033[1;34m

NC = \033[0m

NAME = conventional_commiter

CFLAGS = -Wall -Wextra -Werror -I./include

all: $(NAME)

$(NAME): $(OBJ)
	@echo -e "$(BLUE)Binary created !$(NC)"
	@gcc -o $(NAME) $(OBJ)

obj/%.o: src/%.c
	@echo -e "$(GREEN)Building $<$(NC)"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: clean fclean all
