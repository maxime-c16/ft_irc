/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:24:58 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/15 17:32:10 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ModeCmd.hpp"

bool ModeCmd::is_valid_mode(const std::string &mode)
{
	return	mode == "+i" || mode == "-i" || mode == "+m" || mode == "-m" ||
			mode == "+n" || mode == "-n" || mode == "+p" || mode == "-p" ||
			mode == "+s" || mode == "-s" || mode == "+t" || mode == "-t" ||
			mode == "+a" || mode == "-a" || mode[1] == 'u' || mode == "-u" ||
			mode == "+k" || mode == "-k" || mode == "+c" || mode == "-c" ||
			mode == "+x" || mode == "-x" || mode == "+l" || mode == "-l" ||
			mode == "+f" || mode == "-f" || mode == "+r" || mode == "-r" ||
			mode == "+g" || mode == "-g" || mode == "+e" || mode == "-e" ||
			mode == "+b" || mode == "-b";
}

int	ModeCmd::get_mode_flag(const std::string &mode)
{
	if (mode == "+i") return CM_INVITE_ONLY;
	if (mode == "-i") return -CM_INVITE_ONLY;
	if (mode == "+m") return CM_MODERATED;
	if (mode == "-m") return -CM_MODERATED;
	if (mode == "+n") return CM_NO_EXTERNAL;
	if (mode == "-n") return -CM_NO_EXTERNAL;
	if (mode == "+p") return CM_PRIVATE;
	if (mode == "-p") return -CM_PRIVATE;
	if (mode == "+s") return CM_SECRET;
	if (mode == "-s") return -CM_SECRET;
	if (mode == "+t") return CM_TOPIC_LOCK;
	if (mode == "-t") return -CM_TOPIC_LOCK;
	if (mode == "+a") return CM_NO_ANONYMOUS;
	if (mode == "-a") return -CM_NO_ANONYMOUS;
	if (mode == "-u") return -CM_USER_LIMIT;
	if (mode[1] == 'u') return CM_USER_LIMIT;
	if (mode == "+k") return CM_KEY_PROTECTED;
	if (mode == "-k") return -CM_KEY_PROTECTED;
	if (mode == "+c") return CM_NO_COLOR;
	if (mode == "-c") return -CM_NO_COLOR;
	if (mode == "+x") return CM_NO_SPAM;
	if (mode == "-x") return -CM_NO_SPAM;
	if (mode == "+l") return CM_LOGGING;
	if (mode == "-l") return -CM_LOGGING;
	if (mode == "+f") return CM_LANGUAGE_FILTER;
	if (mode == "-f") return -CM_LANGUAGE_FILTER;
	if (mode == "+r") return CM_SLOW_MODE;
	if (mode == "-r") return -CM_SLOW_MODE;
	if (mode == "+g") return CM_READ_ONLY;
	if (mode == "-g") return -CM_READ_ONLY;
	if (mode == "+e") return CM_GUESTS_ALLOWED;
	if (mode == "-e") return -CM_GUESTS_ALLOWED;
	if (mode == "+b") return CM_NO_MEDIA;
	if (mode == "-b") return -CM_NO_MEDIA;
	return 0;
}

void	ModeCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	ClientInfo	&client = server.clients[client_fd];
	std::string	target;
	std::string	mode;
	int			flag;

	iss >> target >> mode;
	if (target.empty() || mode.empty())
	{
		send(client_fd, "Error: Target and mode must not be empty.\r\n", 44, 0);
		return ;
	}
	if (!server.channels[target].is_member(client_fd))
	{
		send(client_fd, "Error: User not part of the channel.\r\n", 39, 0);
		return ;
	}
	if (!is_valid_mode(mode))
	{
		send(client_fd, "Error: Invalid mode.\r\n", 23, 0);
		return ;
	}

	flag = get_mode_flag(mode);
	if (flag == 0)
	{
		send(client_fd, "Error: Unrecognized flag.\r\n", 28, 0);
		return ;
	}
	if (server.channels.find(target) == server.channels.end())
	{
		send(client_fd, "Error: Channel not found.\r\n", 28, 0);
		return ;
	}

	Channel	&channel = server.channels[target];
	if (mode[0] == '+')
		channel.set_mode(mode, flag, client, server);
	else if (mode[0] == '-')
		channel.unset_mode(mode, -flag, client, server);
}
