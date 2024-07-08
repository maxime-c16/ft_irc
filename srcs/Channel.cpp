/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:34:02 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 16:58:34 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel( void ) : _name("")
{

}

Channel::Channel( const std::string &channel_name ) : _name(channel_name)
{
}

Channel::~Channel()
{

}

void	Channel::add_member( int client_fd )
{
	_members.insert(client_fd);
}

void	Channel::remove_member( int client_fd )
{
	_members.erase(client_fd);
}

bool	Channel::is_member( int client_fd )
{
	return (_members.find(client_fd) != _members.end());
}

void	Channel::add_message(const ClientInfo &client, const std::string &message, IRCServer &server)
{
	time_t	now = time(0);
	_message_history[client][now] = message;
	// if (_message_history[client].size() > 200)
	// 	_message_history[client].erase(_message_history[client].begin());
	for (std::set<int>::iterator it = _members.begin(); it != _members.end(); it++)
		display_channel(*it, server);
}

void	Channel::display_channel( int client_fd, IRCServer &server )
{
	std::ostringstream	oss;
	std::string			message;

	oss << "Channel :" << _name << "\nMembers :\n";
	for (std::set<int>::iterator it = _members.begin(); it != _members.end(); it++)
		oss << "- " << server.clients[*it].nickname << "\n";
	message = oss.str();
	send(client_fd, message.c_str(), message.size(), 0);
	display_history(client_fd);
}
bool compareMessages(const std::pair<time_t, std::string> &a, const std::pair<time_t, std::string> &b)
{
	return a.first < b.first;
}

void	Channel::display_history( int client_fd )
{
	std::ostringstream	oss;
	std::string			message;

	std::vector<std::pair<time_t, std::string> >	all_messages;
	std::vector<std::string>						client_nicknames;
	oss << "\033[2J\033[H";
	for (std::map<ClientInfo, std::map<time_t, std::string> >::iterator it = _message_history.begin(); it != _message_history.end(); it++)
	{
		const ClientInfo &client = it->first;
		const std::map<time_t, std::string>	&messages = it->second;
		for (std::map<time_t, std::string>::const_iterator msg_it = messages.begin(); msg_it != messages.end(); msg_it++)
		{
			if (client.client_fd == client_fd)
				all_messages.push_back(std::make_pair(msg_it->first, BLUE "@" + client.nickname + RESET " - " YELLOW + ctime(&msg_it->first) + RESET "--> " + msg_it->second));
			else
				all_messages.push_back(std::make_pair(msg_it->first, RED "@" + client.nickname + RESET " - " YELLOW + ctime(&msg_it->first) + RESET "--> " + msg_it->second));
		}
	}
	std::sort(all_messages.begin(), all_messages.end(), compareMessages);
	oss << "Messages:\n";
	for (std::vector<std::pair<time_t, std::string> >::iterator msg_it = all_messages.begin(); msg_it != all_messages.end(); msg_it++)
	{
		oss << msg_it->second << "\n";
	}
	message = oss.str();
	send(client_fd, message.c_str(), message.size(), 0);
}

void	Channel::broadcast( const std::string &message )
{
	std::set<int>::iterator	it;

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		send(*it, message.c_str(), message.size(), 0);
		it++;
	}
}

void	Channel::broadcast_except( ClientInfo &client, const std::string &message )
{
	std::set<int>::iterator	it;
	std::string	message_from = client.nickname + " @" + client.username + "\r\n---> " + message + "\r\n";

	it = this->_members.begin();
	while (it != this->_members.end())
	{
		if (*it != client.client_fd)
		{
			send(*it, message_from.c_str(), message_from.size(), 0);
		}
		it++;
	}
}

void	Channel::SetName( const std::string &channel_name )
{
	_name = channel_name;
}

void	Channel::SetMembers( int client_fd )
{
	_members.insert(client_fd);
}

std::string	Channel::GetName( void ) const
{
	return (_name);
}

std::set<int>	Channel::GetMembers( void ) const
{
	return (_members);
}
