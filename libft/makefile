# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2017/06/20 23:46:37 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
PRINTFSRC =	ft_printf.c \
			core.c \
			verif_format.c \
			recup_format.c \
			convert_int.c \
			convert_int_next.c \
			preci_int.c \
			field_int.c \
			field_int_next.c \
			field_string.c \
			conv_string.c \
			preci_string.c \
			conv_char.c \
			conv_hexa.c \
			conv_octal.c \
			conv_octal_next.c \
			conv_hexa_x.c \
			recup_args_hexa.c \
			concaten_result.c \
			conv_uint.c \
			conv_percent.c \
			conv_bin.c \
			conv_n.c \
			conv_empty.c \
			spc_flags.c \
			chk_color.c \
			set_lst.c

LFTSRC =	ft_atoi.c \
			ft_itoa.c \
			ft_itoa_long.c \
			ft_itoa_ulong.c \
			ft_itoa_base.c \
			ft_itoa_base_maj.c \
			ft_itoa_base_unsigned.c \
			ft_itoa_base_maj_unsigned.c \
			ft_itoa_base_unicode.c \
			ft_putnstr.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strjoin.c \
			ft_strnjoin.c \
			ft_strjoinn.c \
			ft_strjoinf.c \
			ft_strjoinfn.c \
			ft_strjoinff.c \
			ft_strlen.c \
			ft_strnew.c \
			ft_strsub.c \
			ft_memalloc.c \
			ft_putchar.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdel.c \
			ft_memdel.c \
			ft_power.c \
			ft_btoi.c \
			ft_strcmp.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_strcat.c \
			ft_strcpy.c \
			ft_strlcat.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsubf.c \


OBJS1 = $(LFTSRC:.c=.o)
	OBJS2 = $(PRINTFSRC:.c=.o)
	OBJS = $(OBJS2) $(OBJS1)

all: $(NAME)

$(NAME): $(addprefix objs/, $(OBJS2)) $(addprefix objs/, $(OBJS1))
		@printf "\033[0;35m> Compiling ft_ls\033[0m"
			@ar rc $(NAME) $(addprefix objs/, $(OBJS))
				@printf "\033[0;32m > OK\n\033[0m"

$(addprefix objs/, $(OBJS1)): $(addprefix libft/, $(LFTSRC))
		@printf "\033[0;35m.\033[0m"
			@gcc $(FLAGS) -c $(addprefix libft/, $(addsuffix .c, $(basename $(notdir $@)))) -o objs/$(notdir $@) -I includes/

$(addprefix objs/, $(OBJS2)): $(addprefix srcs/, $(PRINTFSRC))
		@test -d objs || mkdir objs
			@printf "\033[0;35m.\033[0m"
				@gcc $(FLAGS) -c $(addprefix srcs/, $(addsuffix .c, $(basename $(notdir $@)))) -o objs/$(notdir $@) -I includes/

clean:
		@rm -rdf objs/

fclean: clean
		@rm -f $(NAME)

re: fclean all
