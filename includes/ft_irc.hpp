/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:15:10 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 13:03:22 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP

# define FT_IRC_HPP

# define EXIT_FAILURE 1
# define BUFF_SIZE 4096

# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <map>
# include <set>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <csignal>
# include <sstream>

typedef struct s_ClientInfo
{
	std::string	nickname;
	std::string	username;
	std::string	realname;
	std::string	password;
	std::string	current_channel;
	std::string	pending_invite;
	bool		is_registered;
	bool		is_operator;
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
# include "IRCCommand.hpp"

#endif
