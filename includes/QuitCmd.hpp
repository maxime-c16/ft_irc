/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:02:23 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 21:02:44 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCMD_HPP

# define QUITCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	QuitCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
