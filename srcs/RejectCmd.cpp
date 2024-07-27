/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RejectCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:35 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/10 12:45:50 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RejectCmd.hpp"

void	RejectCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	ClientInfo	&client = server.clients[client_fd];

	(void)iss;
	if (client.pending_invite.empty())
	{
		send(client_fd, "Error: No pending invite...\r\n", 30, 0);
		return ;
	}

	std::string reject_message = ":" + client.nickname + " REJECT " + client.pending_invite + "\r\n";
	server.channels[client.pending_invite].unset_invited(client_fd);
	client.pending_invite.clear();
	send(client_fd, reject_message.c_str(), reject_message.size(), 0);
	std::cout << "Client " << client_fd << " rejected invitation.\r\n" << std::endl;
}
