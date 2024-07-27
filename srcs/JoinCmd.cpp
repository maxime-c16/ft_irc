/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:23:21 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/15 16:53:48 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/JoinCmd.hpp"

void	JoinCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	channel_name;
	std::string	key;
	std::string	join_msg;
	std::set<int>	members;
	std::map<std::string, Channel>::iterator	it;
	ClientInfo	&client = server.clients[client_fd];

	name = "JOIN";
	iss >> channel_name >> key;
	std::cerr << "Usernam/nick : " << client.username << ", " << client.nickname << ".\r\n";
	std::cerr << "Parsed channel_name: " << channel_name << ", key: " << key << std::endl;
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
	std::cerr << "Finding channel: " << channel_name << std::endl;
	it = server.channels.find(channel_name);
	std::cerr << "Channel found: " << (it != server.channels.end()) << std::endl;
	if (it == server.channels.end())
	{
		if (key.empty())
		{
			server.channels[channel_name] = Channel(channel_name);
			std::cerr << "EXEC JOIN creation no key" << std::endl;
		}
		else
		{
			std::cerr << "EXEC JOIN creation with key: " << key << std::endl;
			server.channels[channel_name] = Channel(channel_name, CM_KEY_PROTECTED, key, client, server);
			std::cerr << "Channel key: " << server.channels[channel_name].GetKey() << std::endl;
			client.channel_keys[channel_name] = key;
		}
		client.admin_privs[channel_name] = PRV_ADM1;
	}
	else if (server.channels[channel_name].is_member(client_fd))
	{
		send(client_fd, "Error: Client is already in target channel.\r\n", 46, 0);
		return ;
	}
	else if (!key.empty())
	{
		client.channel_keys[channel_name] = key;
	}
	if (server.check_modes(client, server.channels[channel_name], name) == false)
	{
		std::cerr << "Modes KO!\r\n" << std::endl;
		return ;
	}
	std::cerr << "Modes OK!\r\n";
	std::set<std::string>::iterator	joined_it = client.joined_channel.find(channel_name);
	if (joined_it == client.joined_channel.end())
	{
		client.joined_channel.insert(channel_name);
		std::cerr << "joined channel " << *(client.joined_channel.find(channel_name)) << std::endl;
	}
	else
		std::cerr << "joined channel " << *joined_it << std::endl;
	server.channels[channel_name].add_member(client_fd);
	client.current_channel = channel_name;
	join_msg = ":" + client.nickname + " JOIN " + client.current_channel + "\r\n";
	server.channels[channel_name].add_message(client, join_msg, server);
	std::cout << "Client " << client_fd << " joined channel " << channel_name << std::endl;
}
