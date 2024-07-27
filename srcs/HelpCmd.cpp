/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:11:26 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/10 13:11:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HelpCmd.hpp"

void HelpCmd::execute(IRCServer &server, int client_fd, std::istringstream &iss)
{
	std::string command;
	iss >> command;

	std::string help_msg = CLEAR;
	(void)server;
	if (command.empty()) {
		help_msg += BOLD WHITE "IRC - [HELP]\n\n" RESET;
		help_msg += "The following commands are available:\n\n";
		help_msg += BOLD CYAN "JOIN <channel> <key>\n" RESET;
		help_msg += "    Join the specified channel.\n\n";
		help_msg += BOLD CYAN "PART <channel>\n" RESET;
		help_msg += "    Leave the specified channel.\n\n";
		help_msg += BOLD CYAN "INVITE <user> <channel>\n" RESET;
		help_msg += "    Invite a user to a channel.\n\n";
		help_msg += BOLD CYAN "KICK <channel> <user>\n" RESET;
		help_msg += "    Kick a user from a channel.\n\n";
		help_msg += BOLD CYAN "PRIVMSG <target> <message>\n" RESET;
		help_msg += "    Send a private message to a user or channel.\n\n";
		help_msg += BOLD CYAN "NOTICE <target> <message>\n" RESET;
		help_msg += "    Send a notice to a user or channel.\n\n";
		help_msg += BOLD CYAN "PING <server>\n" RESET;
		help_msg += "    Check the connection latency with the server.\n\n";
		help_msg += BOLD CYAN "OPER <username> <password>\n" RESET;
		help_msg += "    Gain operator privileges.\n\n";
		help_msg += BOLD CYAN "KILL <user>\n" RESET;
		help_msg += "    Terminate a user's connection to the server (operators only).\n\n";
		help_msg += BOLD CYAN "QUIT\n" RESET;
		help_msg += "    Terminate your connection to the server.\n\n";
		help_msg += BOLD CYAN "HELP [command]\n" RESET;
		help_msg += "    Display this help message or get help for a specific command.\n";
	} else {
		if (command == "JOIN") {
			help_msg += BOLD CYAN "JOIN <channel>\n" RESET;
			help_msg += "    Join the specified channel.\n";
		} else if (command == "PART") {
			help_msg += BOLD CYAN "PART <channel>\n" RESET;
			help_msg += "    Leave the specified channel.\n";
		} else if (command == "INVITE") {
			help_msg += BOLD CYAN "INVITE <user> <channel>\n" RESET;
			help_msg += "    Invite a user to a channel.\n";
		} else if (command == "KICK") {
			help_msg += BOLD CYAN "KICK <channel> <user>\n" RESET;
			help_msg += "    Kick a user from a channel.\n";
		} else if (command == "PRIVMSG") {
			help_msg += BOLD CYAN "PRIVMSG <target> <message>\n" RESET;
			help_msg += "    Send a private message to a user or channel.\n";
		} else if (command == "NOTICE") {
			help_msg += BOLD CYAN "NOTICE <target> <message>\n" RESET;
			help_msg += "    Send a notice to a user or channel.\n";
		} else if (command == "PING") {
			help_msg += BOLD CYAN "PING <server>\n" RESET;
			help_msg += "    Check the connection latency with the server.\n";
		} else if (command == "OPER") {
			help_msg += BOLD CYAN "OPER <username> <password>\n" RESET;
			help_msg += "    Gain operator privileges.\n";
		} else if (command == "KILL") {
			help_msg += BOLD CYAN "KILL <user>\n" RESET;
			help_msg += "    Terminate a user's connection to the server (operators only).\n";
		} else if (command == "QUIT") {
			help_msg += BOLD CYAN "QUIT\n" RESET;
			help_msg += "    Terminate your connection to the server.\n";
		} else if (command == "HELP") {
			help_msg += BOLD CYAN "HELP [command]\n" RESET;
			help_msg += "    Display this help message or get help for a specific command.\n";
		} else {
			help_msg += RED "Unknown command: " + command + "\n" RESET;
		}
	}

	send(client_fd, help_msg.c_str(), help_msg.size(), 0);
}
