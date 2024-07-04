/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:54:32 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 20:01:41 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OperCmd.hpp"

void	OperCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	name;
	std::string	password;
	std::string	response;

	iss >> name >> password;
	if (name == "admin" && password == "password")
	{
		server.clients[client_fd].is_operator = true;
		response = "You are now an IRC operator\r\n";
	}
	else
		response = "Invalid credentials\r\n";
	send(client_fd, response.c_str(), response.size(), 0);
}
