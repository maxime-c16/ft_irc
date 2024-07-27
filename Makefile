# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 13:04:54 by mcauchy           #+#    #+#              #
#    Updated: 2024/07/10 13:27:43 by mcauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		=	main.cpp IRCServer.cpp Channel.cpp NickCmd.cpp IRCCommand.cpp \
				PassCmd.cpp UserCmd.cpp OperCmd.cpp PingCmd.cpp KillCmd.cpp \
				QuitCmd.cpp JoinCmd.cpp PartCmd.cpp InviteCmd.cpp AcceptCmd.cpp \
				RejectCmd.cpp KickCmd.cpp PrivmsgCmd.cpp NoticeCmd.cpp DebugCmd.cpp\
				HelpCmd.cpp ModeCmd.cpp

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
