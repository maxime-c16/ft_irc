/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:01:32 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 11:51:14 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/InviteCmd.hpp"

void	InviteCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	nickname;
	std::string	channel_name;
	int			target_fd;

	target_fd = -1;
	iss >> nickname >> channel_name;
	if (nickname.empty() || channel_name.empty())
	{
		send(client_fd, "Error: Nickname or channel name missing\r\n", 42, 0);
		return ;
	}

	for (std::map<int, ClientInfo>::iterator it = server.clients.begin(); it != server.clients.end(); it++)
	{
		if (it->second.nickname == nickname)
		{
			target_fd = it->first;
			break ;
		}
	}

	if (target_fd == -1)
	{
		send(client_fd, "Error: User not found.\r\n", 25, 0);
		return ;
	}

	server.clients[target_fd].pending_invite = channel_name;
	std::string invite_message = ":" + server.clients[client_fd].nickname + " INVITE " + nickname + " to " + channel_name + "\r\n";
	send(target_fd, invite_message.c_str(), invite_message.size(), 0);
	send(client_fd, invite_message.c_str(), invite_message.size(), 0);
	std::cout << "Client " << client_fd << " invited " << target_fd << " to channel " << channel_name << std::endl;
}
