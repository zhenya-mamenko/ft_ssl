# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/20 11:27:05 by emamenko          #+#    #+#              #
#    Updated: 2019/03/21 17:04:40 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY:		$(NAME) all clean fclean re reclean del reexec

NAME	=	ft_ssl
SOURCES	=	ft_ssl.c print.c commands.c functions.c input.c \
			md5/md5.c md5/md5_alg.c md5/md5_transform.c
DEBUG	=	-g -fsanitize=address

all:		$(NAME)

$(NAME):
			make -C libft/
			gcc -g -Wall -Wextra -Werror -o $(NAME) -Llibft -lft $(SOURCES)

clean:
			make -C libft/ clean

fclean:		clean
			make -C libft/ fclean
			rm -f $(NAME)

re: 		fclean all
			make -C libft/ re

reclean:	re; make clean;
			make -C libft/ reclean

del:
			rm -f $(NAME)

reexec:		del all
