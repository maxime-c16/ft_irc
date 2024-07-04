/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KillCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:59 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 22:32:20 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/KillCmd.hpp"

void	KillCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	target_nick;
	std::string	response;
	std::map<int, ClientInfo>::iterator it;

	iss >> target_nick;

	if (server.clients[client_fd].is_operator)
	{
		if (!target_nick.empty())
		{
			it = server.clients.begin();
			while (it != server.clients.end())
			{
				if (it->second.nickname == target_nick)
				{
					std::string	confirmation;

					confirmation = "You have killed [" + target_nick + "].\r\n";
					response = "You have been killed by an operator.\r\n";
					std::cout << "[" << server.clients[client_fd].nickname << "] killed [" << target_nick << "].\r\n" << std::endl;
					send(it->first, response.c_str(), response.size(), 0);
					send(client_fd, confirmation.c_str(), confirmation.size(), 0);
					close(it->first);
					server.clients.erase(it);
					break;
				}
				it++;
			}
			if (it == server.clients.end())
			{
				response = "Error: [" + target_nick + "] not found.\r\n";
				send(client_fd, response.c_str(), response.size(), 0);
			}
		}
		else
		{
			response = "Usage: KILL <target_nickname>.\r\n";
			send(client_fd, response.c_str(), response.size(), 0);
		}
	}
	else
	{
		response = "Not enough priviledge, try `OPER <user> <psswd>` command.\r\n";
		send(client_fd, response.c_str(), response.size(), 0);
	}
}
