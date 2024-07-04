/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KillCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:25:15 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 20:25:27 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILLCMD_HPP

# define KILLCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	KillCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
