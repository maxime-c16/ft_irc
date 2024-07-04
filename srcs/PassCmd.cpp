/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:32:16 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 22:28:39 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PassCmd.hpp"

void	PassCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	password;

	iss >> password;
	if (!password.empty())
	{
		server.clients[client_fd].password = password;
		std::cout << "Client " << client_fd << " set connection password." << std::endl;
	}
	else
	{
		std::cerr << "Error: password is empty ..." << std::endl;
		send(client_fd, "Error: password is empty ...\r\n", 31, 0);
	}
}
