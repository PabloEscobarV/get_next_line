# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 13:57:20 by polenyc           #+#    #+#              #
#    Updated: 2024/03/11 13:15:00 by blackrider       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
BONUSNAME = libgnlfull.a
OBJDIR = objs
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
OBJBONUS = $(SRCBONUS:%.c=$(OBJDIR)/%.o)
SRCBONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

CC = gcc
CFLAGSO = -c -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

bonus: $(BONUSNAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) $(BONUSNAME)

re: fclean all

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(BONUSNAME): $(OBJBONUS)
	ar -rc $(BONUSNAME) $(OBJBONUS)
	ranlib $(BONUSNAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGSO) $< -o $@
