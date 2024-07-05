/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:43:45 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 16:09:50 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/UserCmd.hpp"

void	UserCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string	username;
	std::string	realname;

	iss >> username;
	getline(iss, realname);
	if (!username.empty() && !realname.empty())
	{
		server.clients[client_fd].username = username;
		server.clients[client_fd].realname = realname;
		server.clients[client_fd].is_registered = true;
		server.clients[client_fd].client_fd = client_fd;
		std::cout << "Client " << client_fd << " registered with username " << username << " and realname " << realname << std::endl;
	}
	else
		std::cerr << "Error: username or realname empty, cannot register client " << client_fd << std::endl;
}
