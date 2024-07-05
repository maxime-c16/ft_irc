/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RejectCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:02:46 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 13:03:11 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REJECTCMD_HPP

# define REJECTCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	RejectCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
