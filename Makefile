# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 13:57:20 by polenyc           #+#    #+#              #
#    Updated: 2024/02/05 14:31:03 by polenyc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
OBJDIR = objs
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
OBJBONUS = $(SRCBONUS:%.c=$(OBJDIR)/%.o)
SRCBONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

CC = gcc
CFLAGSO = -c -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGSO) $< -o $@

bonus: fclean $(OBJBONUS)
	ar -rc $(NAME) $(OBJBONUS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all