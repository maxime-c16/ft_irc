/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:18:32 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 16:08:00 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP

# define CHANNEL_HPP

# include "ft_irc.hpp"

class	Channel
{
	public:

		Channel();
		Channel( const std::string &channel_name );
		~Channel();

		void	add_member( int client_fd );
		void	remove_member( int client_fd );
		bool	is_member( int client_fd );
		void	broadcast( const std::string &message );
		void	broadcast_except( ClientInfo &client , const std::string &message );

		void	SetName( const std::string &name );
		void	SetMembers( int client_fd );

		std::string		GetName( void ) const;
		std::set<int>	GetMembers( void ) const;

	private:

		std::string		_name;
		std::set<int>	_members;
};

#endif
