/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:02:56 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 21:18:19 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/QuitCmd.hpp"

void	QuitCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	quit_msg;
	std::string	error_msg;

	(void)iss;
	quit_msg = "Client [" + server.clients[client_fd].nickname + "] has quit the connection.\r\n";
	error_msg = "Error: Closing link: " + std::to_string(client_fd);
	send(client_fd, quit_msg.c_str(), quit_msg.size(), 0);
	send(client_fd, error_msg.c_str(), error_msg.size(), 0);
	std::cout << quit_msg << std::endl;
	close(client_fd);
	server.clients.erase(client_fd);
}
