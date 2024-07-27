/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:10:05 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/08 18:10:31 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPCMD_HPP

# define HELPCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	HelpCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);
};

#endif
