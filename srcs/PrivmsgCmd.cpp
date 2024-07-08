/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:03:12 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/07 14:27:03 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PrivmsgCmd.hpp"

void	PrivmsgCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	target;
	std::string	message;

	iss >> target;
	std::getline(iss, message);

	if (!message.empty() && message[0] == ' ')
		message.erase(0, 1);
	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);
	std::string formatted_message = ":" + server.clients[client_fd].nickname + " PRIVMSG " + target + " :" + message + "\r\n";

	if (target[0] == '#')
	{
		target.erase(0, 1);
		if (server.channels.find(target) != server.channels.end())
		{
			Channel	&channel = server.channels[target];
			if (channel.is_member(client_fd))
				channel.broadcast_except(server.clients[client_fd], formatted_message);
			else
				send(client_fd, "Error: User is not part of the channel, try `JOIN <channel>`.\r\n", 64, 0);
		}
		else
			send(client_fd, "Error: Channel not found.\r\n", 28, 0);
	}
	else
	{
		bool	user_found = false;
		std::map<int, ClientInfo>::iterator	it;

		it = server.clients.begin();
		while (it != server.clients.end())
		{
			if (it->second.nickname == target)
			{
				send(it->first, formatted_message.c_str(), formatted_message.size(), 0);
				user_found = true;
				break ;
			}
			it++;
		}
		if (user_found == false)
		{
			send(client_fd, "Error: User/Channel not foud.\r\n", 32, 0);
		}
	}
}
