/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:28:18 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/04 19:31:55 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCMD_HPP

# define PASSCMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	PassCmd : public IRCCommand
{
	public:
		virtual void	execute(IRCServer &server, int clinet_fd, std::istringstream &iss);
};

#endif
