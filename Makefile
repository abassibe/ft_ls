# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2017/06/16 06:07:23 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c \
	   chk_opt.c \
	   crea_lst.c \
	   crea_lst_next.c \
	   crea_lst_one_file.c \
	   sort_lst.c \
	   sort_next.c \
	   ft_print.c \
	   l_print.c \
	   l_print_next.c \
	   print_date.c \
	   print_date_one_file.c \
	   one_print.c \
	   recurs.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./srcs/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(addprefix $(SRCPATH), $(SRCS)) \
		-I includes/
	@make -C libft
	@gcc $(FLAGS) $(OBJS) libft/libftprintf.a -o $(NAME)

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf libft/libftprintf.a $(NAME)

re: fclean all

