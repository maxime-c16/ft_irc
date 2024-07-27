/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:34:02 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/15 17:38:37 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel( void ) : _name(""), _modes(0), _user_limit(0)
{

}

Channel::Channel( const std::string &channel_name ) : _name(channel_name), _modes(0), _user_limit(0)
{
}

Channel::Channel( const std::string &channel_name, int modes, ClientInfo &client, IRCServer &server ) : _name(channel_name), _modes(0), _user_limit(0)
{
	std::cerr << "creation with no key" << std::endl;
	set_mode("NOFLAG", modes, client, server);
}

Channel::Channel( const std::string &channel_name, int modes, const std::string &key, ClientInfo &client, IRCServer &server ) : _name(channel_name), _modes(0), _key(key), _user_limit(0)
{
	std::cerr << "creation with key: " << key << std::endl;
	set_mode("NOFLAG", modes, client, server);
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

bool	Channel::is_invited( int client_fd )
{
	return (_invited.find(client_fd) != _invited.end());
}

void	Channel::set_mode( const std::string &flag,  int mode, ClientInfo &client, IRCServer &server )
{
	if (flag[1] == 'u' && flag[0] == '+')
	{
		std::string	ulimit = flag.substr(2);
		std::cerr << "ulimit: " << ulimit << std::endl;
		_user_limit = std::stoi(ulimit);
	}
	else if (flag.compare("-u"))
	{
		_user_limit = 0;
	}
	if (flag.compare("NOFLAG") != 0)
	{
		std::string	set_msg = ":" + client.nickname + " set mode: " + flag[1] + " to #" + _name + ".\r\n";
		add_message(client, set_msg, server);
	}
	else
		std::cout << "creation with no flags" << std::endl;
	_modes |= mode;
}

void	Channel::unset_mode( const std::string &flag, int mode, ClientInfo &client, IRCServer &server )
{
	std::string	unset_msg = ":" + client.nickname + " unset mode " + flag[1] + " to #" + _name + ".\r\n";
	add_message(client, unset_msg, server);
	_modes &= ~mode;
}

void	Channel::unset_invited( int client_fd )
{
	_invited.erase(client_fd);
}

bool	Channel::has_mode( int mode ) const
{
	return ((_modes & mode) != 0);
}

void	Channel::SetKey( const std::string &key )
{
	_key = key;
}

void	Channel::SetInvited( int client_fd )
{
	_invited.insert(client_fd);
}

std::string	Channel::GetKey( void ) const
{
	return (_key);
}

std::set<int>	Channel::GetInvited( void ) const
{
	return (_invited);
}

int	Channel::GetUlimit( void ) const
{
	return (_user_limit);
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

	oss << "\033[2J\033[H";
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
