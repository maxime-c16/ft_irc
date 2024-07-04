/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:38:42 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 22:39:01 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCMD_HPP

# define PARTCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	PartCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
