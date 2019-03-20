# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/20 11:27:05 by emamenko          #+#    #+#              #
#    Updated: 2019/03/20 11:34:21 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY:		$(NAME) all clean fclean re reclean

NAME	=	ft_ssl
SOURCES	=	ft_ssl.c print.c

all:		$(NAME)

$(NAME):
			make -C libft/
			gcc -Wall -Wextra -Werror -o $(NAME) -Llibft -lft $(SOURCES)

clean:
			make -C libft/ clean

fclean:		clean
			make -C libft/ fclean
			rm -f $(NAME)

re: 		fclean all
			make -C libft/ re

reclean:	re; make clean;
			make -C libft/ reclean
