/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:10:32 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 20:10:53 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCMD_HPP

# define PINGCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	PingCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
