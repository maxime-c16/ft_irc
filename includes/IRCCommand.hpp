/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:37:23 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 16:13:33 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCOMMAND_HPP

# define IRCCOMMAND_HPP

# include <string>
# include <sstream>

class	IRCServer;

class	IRCCommand
{
	public:
		virtual			~IRCCommand( void );
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss) = 0;
};

#endif
