/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:08 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 20:41:09 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/NickCmd.hpp"

void	NickCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	nickname;
	std::string	response;

	iss >> nickname;
	if (!server.clients[client_fd].password.empty() || server.password.empty())
	{
		if (!nickname.empty())
		{
			server.clients[client_fd].nickname = nickname;
			std::cout << "Client " << client_fd << " set nickname to " << nickname << std::endl;
		}
		else
		{
			response = "Usage: NICK <nickname>.\r\n";
			send(client_fd, response.c_str(), response.size(), 0);
		}
	}
	else
	{
		response = "Error: set password before nickname ...\r\n";
		send(client_fd, response.c_str(), response.size(), 0);
	}
}
