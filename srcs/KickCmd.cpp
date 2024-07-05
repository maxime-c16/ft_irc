/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:34:26 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 15:42:35 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/KickCmd.hpp"

void	KickCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	nickname;
	std::string	channel_name;
	int			target_fd;

	target_fd = -1;
	iss >> nickname >> channel_name;
	if (nickname.empty() || channel_name.empty())
	{
		send(client_fd, "Error: Usage `KICK <nickname> <channel>`.\r\n", 44, 0);
		return ;
	}

	std::map<std::string, Channel>::iterator	channel_it;

	channel_it = server.channels.find(channel_name);
	if (channel_it != server.channels.end())
	{
		if (server.channels[channel_name].is_member(client_fd))
		{
			std::map<int, ClientInfo>::iterator	it;

			it = server.clients.begin();
			while (it != server.clients.end())
			{
				if (it->second.nickname == nickname && server.channels[channel_name].is_member(it->first))
				{
					target_fd = it->first;
					break ;
				}
				it++;
			}
			if (target_fd != -1)
			{
				std::string kick_message = ":" + server.clients[client_fd].nickname + " KICK " + nickname + " from " + channel_name + "\r\n";
				server.channels[channel_name].broadcast(kick_message);
				server.channels[channel_name].remove_member(target_fd);
				server.clients[target_fd].current_channel.clear();
				std::cout << "Client " << client_fd << " kicked " << nickname << " from channel " << channel_name << "\r\n" << std::endl;
			}
			else
			{
				std::string	error_msg = "Error: " + nickname + " is not part of the channel " + channel_name + "\r\n";
				send(client_fd, error_msg.c_str(), error_msg.size(), 0);
			}
		}
		else
		{
			std::string	error_msg = "Error: " + server.clients[client_fd].nickname + " is not part of the channel " + channel_name + "\r\n";
			send(client_fd, error_msg.c_str(), error_msg.size(), 0);
		}
	}
	else
	{
		send(client_fd, "Error: Channel not found ...\r\n", 31, 0);
	}
}
