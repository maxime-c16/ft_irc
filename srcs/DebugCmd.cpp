/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DebugCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:25:27 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/15 16:46:55 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/DebugCmd.hpp"

void	DebugCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	ClientInfo	&client = server.clients[client_fd];
	std::string	debug_message;

	(void)iss;
	debug_message = "[DEBUG]\nNickname: " + client.nickname + "\nCurrent channel: " + client.current_channel + "\nOperator: " + std::to_string(client.is_operator) + "\nPending invite: " + client.pending_invite+"\n";
	debug_message += "Joined channel: ";
	for (std::set<std::string>::iterator it = client.joined_channel.begin(); it != client.joined_channel.end(); it++)
		debug_message += *it + " ";
	debug_message += "\r\n";
	send(client_fd, debug_message.c_str(), debug_message.size(), 0);
}
