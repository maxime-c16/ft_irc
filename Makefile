# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 13:04:54 by mcauchy           #+#    #+#              #
#    Updated: 2024/07/01 15:07:16 by mcauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		=	main.cpp irc_server.cpp

SRC_DIR		=	srcs

DIR_OBJS	=	.objs

SRCS		=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS		=	$(addprefix $(DIR_OBJS)/, $(notdir $(SRCS:.cpp=.o)))

CC			=	c++

CFLAGS		=	-Wall -Wextra -Werror -std=c++98

DEBUG		=	-fsanitize=address -g3

HEADER		=	includes/ft_irc.hpp

NAME		=	ft_irc


all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

$(DIR_OBJS)/%.o	:	$(SRC_DIR)/%.cpp $(HEADER)
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) $(DEBUG) -o $@ -c $<

clean			:
					/bin/rm -rf $(OBJS)
					/bin/rm -rf $(DIR_OBJS)

fclean			:	clean
					/bin/rm -rf $(NAME)

re				:	fclean all
