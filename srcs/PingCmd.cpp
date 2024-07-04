/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:09:20 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 20:20:00 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PingCmd.hpp"

void	PingCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	token;
	std::string	response;

	iss >> token;
	(void)server;
	if (!token.empty())
	{
		response = "Pong " + token + "\r\n";
	}
	else
		response = "Usage: PING <token>\r\n";
	send(client_fd, response.c_str(), response.size(), 0);
}
