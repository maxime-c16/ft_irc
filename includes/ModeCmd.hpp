/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:22:51 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/10 13:27:31 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECMD_HPP

# define MODECMD_HPP

# include "IRCCommand.hpp"
# include "IRCServer.hpp"

class	ModeCmd : public IRCCommand
{
	public:
		virtual	void	execute(IRCServer &server, int client_fd, std::istringstream &iss);

	private:
		bool	is_valid_mode( const std::string &mode );
		int		get_mode_flag( const std::string &mode );
};

#endif
