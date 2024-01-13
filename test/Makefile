NAME = test
NAME_BONUS = test_bonus

OBJ_DIR = objs

SRC = ../get_next_line.c ../get_next_line_utils.c test.c
SRC_BONUS = ../get_next_line_bonus.c ../get_next_line_utils_bonus.c test_bonus.c

OBJECTS = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJECTS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:%.c=%.o))
CC = gcc
CFLAG = -g -Wall -Wextra -Werror -I../

.PHONY: all fclean clean bonus run

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAG) $(OBJECTS) -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS_BONUS)
	$(CC) $(CFLAG) $(OBJECTS_BONUS) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAG) -D BUFFER_SIZE=42 $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -f $(NAME_BONUS)

run: fclean $(NAME)
	./$(NAME)

run_bonus: fclean bonus
	./$(NAME_BONUS)

re: fclean $(NAME)

re_bonus: fclean $(NAME_BONUS)