/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AcceptCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:32:04 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 15:55:20 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AcceptCmd.hpp"

void	AcceptCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	ClientInfo	&client = server.clients[client_fd];

	(void)iss;
	if (client.pending_invite.empty())
	{
		send(client_fd, "Error: No pending invite ...\r\n", 31, 0);
		return ;
	}

	std::string	channel_name = client.pending_invite;
	std::map<std::string, Channel>::iterator	it;

	it = server.channels.find(channel_name);
	if (it != server.channels.end() && server.channels[channel_name].is_member(client_fd))
	{
		send(client_fd, "Error: Client already in channel...\r\n", 38, 0);
		client.pending_invite.clear();
		return ;
	}
	else if (it == server.channels.end())
	{
		send(client_fd, "Error: Channel not found, try `JOIN <channel>`.\r\n", 50, 0);
		client.pending_invite.clear();
		return ;
	}

	server.channels[channel_name].add_member(client_fd);
	client.current_channel = channel_name;
	client.pending_invite.clear();

	std::string join_message = ":" + client.nickname + " JOIN " + channel_name + "\r\n";
	// server.channels[channel_name].broadcast(join_message);
	server.channels[channel_name].display_channel(client_fd, server);
	server.channels[channel_name].add_message(client, join_message, server);
	std::cout << "Client " << client_fd << " accepted invitation and joined channel " << channel_name << std::endl;
}
