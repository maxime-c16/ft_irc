/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:23:21 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 15:58:23 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/JoinCmd.hpp"

void	JoinCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	channel_name;
	std::string	join_msg;
	std::set<int>	members;
	std::map<std::string, Channel>::iterator	it;
	ClientInfo	&client = server.clients[client_fd];

	iss >> channel_name;
	if (channel_name.empty())
	{
		send(client_fd, "Error: No channel name provided\r\n", 34, 0);
		return ;
	}
	else if (!server.clients[client_fd].current_channel.empty())
	{
		send(client_fd, "Error: User already in a channel, try `PART <channel>`.\r\n", 58, 0);
		return ;
	}
	it = server.channels.find(channel_name);
	if (it == server.channels.end())
	{
		server.channels[channel_name] = Channel(channel_name);
	}
	else if (server.channels[channel_name].is_member(client_fd))
	{
		send(client_fd, "Error: Client is already in channel.\r\n", 39, 0);
		return ;
	}
	server.channels[channel_name].add_member(client_fd);
	server.clients[client_fd].current_channel = channel_name;
	join_msg = ":" + server.clients[client_fd].nickname + " JOIN " + server.clients[client_fd].current_channel + "\r\n";
	server.channels[channel_name].add_message(client, join_msg, server);
	server.channels[channel_name].display_channel(client_fd, server);
	// members = server.channels[channel_name].GetMembers();
	// for (std::set<int>::iterator it = members.begin(); it != members.end(); it++)
	// 	send(*it, join_msg.c_str(), join_msg.size(), 0);
	std::cout << "Client " << client_fd << " joined channel " << channel_name << std::endl;
}
