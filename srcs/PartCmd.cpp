/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:39:24 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 16:04:18 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PartCmd.hpp"

void	PartCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	channel_name;
	std::map<std::string, Channel>::iterator	it;
	ClientInfo	&client = server.clients[client_fd];

	iss >> channel_name;
	if (channel_name.empty())
	{
		send(client_fd, "ERROR: No channel name provided\r\n", 34, 0);
		return ;
	}

	it = server.channels.find(channel_name);
	if (it != server.channels.end() && it->second.is_member(client_fd))
	{
		std::string part_message = ":" + server.clients[client_fd].nickname + " PART " + channel_name + "\r\n";
		server.channels[channel_name].add_message(client, part_message, server);
		it->second.remove_member(client_fd);
		server.clients[client_fd].current_channel.clear();
		std::cout << "Client " << client_fd << " left channel: " << channel_name << "\r\n" << std::endl;
	}
	else
	{
		send(client_fd, "Error: cannot find channel and/or client not part of the channel.\r\n", 68, 0);
	}
}
