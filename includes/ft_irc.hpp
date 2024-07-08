/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:15:10 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 16:25:16 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP

# define FT_IRC_HPP

# define EXIT_FAILURE 1
# define BUFF_SIZE 4096

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLD		"\033[1m"
# define UNDERLINE	"\033[4m"

# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <algorithm>
# include <map>
# include <set>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <csignal>
# include <ctime>
# include <sstream>

typedef struct s_ClientInfo
{
	std::string	nickname;
	std::string	username;
	std::string	realname;
	std::string	password;
	std::string	current_channel;
	std::string	pending_invite;
	int			client_fd;
	bool		is_registered;
	bool		is_operator;
	bool		operator<( const struct s_ClientInfo &other ) const {
		return (client_fd < other.client_fd || (client_fd == other.client_fd && nickname < other.nickname)
				|| (client_fd == other.client_fd && nickname == other.nickname && username < other.username));
	}
}				ClientInfo;

# include "Channel.hpp"
# include "IRCServer.hpp"
# include "NickCmd.hpp"
# include "PassCmd.hpp"
# include "UserCmd.hpp"
# include "OperCmd.hpp"
# include "PingCmd.hpp"
# include "KillCmd.hpp"
# include "QuitCmd.hpp"
# include "JoinCmd.hpp"
# include "PartCmd.hpp"
# include "InviteCmd.hpp"
# include "AcceptCmd.hpp"
# include "RejectCmd.hpp"
# include "KickCmd.hpp"
# include "PrivmsgCmd.hpp"
# include "NoticeCmd.hpp"
# include "DebugCmd.hpp"
# include "IRCCommand.hpp"

#endif
