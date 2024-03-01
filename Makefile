# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geymat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 04:17:20 by geymat            #+#    #+#              #
#    Updated: 2024/03/01 22:38:35 by geymat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = manda/pipex.c \
       manda/ft_split.c \
       manda/ft_strjoins.c \
       manda/execve_stuff.c \
       manda/open_close_free.c \
       manda/almost_libft_utils.c \
       manda/get_next_line.c \
       manda/get_next_line_utils.c

SRCS_BONUS =       bonus/almost_libft_utils_bonus.c \
		   bonus/execve_stuff_bonus.c \
		   bonus/ft_split_bonus.c \
		   bonus/ft_strjoins_bonus.c \
		   bonus/get_next_line_bonus.c \
		   bonus/get_next_line_utils_bonus.c \
		   bonus/open_close_free_bonus.c \
		   bonus/pipex_bonus.c

HEADERS = manda/pipex.h \
	  manda/get_next_line.h

OBJECTS = $(SRCS:.c=.o)

OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex 

CFLAGS = -Wall -Wextra -Werror

all:
	$(RM) $(OBJECTS_BONUS)
	make $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

bonus: $(OBJECTS_BONUS)
	$(RM) $(OBJECTS)
	$(MAKE) $(NAME) OBJECTS="$(OBJECTS_BONUS)"  HEADERS="bonus/pipex_bonus.h bonus/get_next_line_bonus.h"

.PHONY: re all clean fclean bonus
