/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:34:02 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/03 18:24:04 by mcauchy          ###   ########.fr       */
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
