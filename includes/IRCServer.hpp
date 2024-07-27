/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:03 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/15 17:46:39 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP

# define IRC_SERVER_HPP

# include "ft_irc.hpp"
# include "IRCCommand.hpp"

class	Channel;

class	IRCServer
{
	public:

		IRCServer( void );
		IRCServer(int port, const std::string &password);
		~IRCServer( void );

		static void	signal_handler( int signum );
		void		start( void );
		int			GetServerFD( void );
		bool	check_modes( ClientInfo &client, Channel &channel, std::string &command, int mode );

		// void	display_welcome_message( int client_fd );

		std::map<int, ClientInfo>		clients;
		std::map<std::string, Channel>	channels;
		std::string						password;


	private:

		static bool						_signal;
		int								_port;
		int								_server_fd;
		std::vector<pollfd>				_pollfds;
		sockaddr_in						_server_addr;

		void	error( const std::string &msg );
		void	set_non_blocking( int sockfd );
		void	create_server_socket( void );
		void	set_server_addr( void );
		void	bind_socket( void );
		void	start_listening( void );
		int		accept_new_client( void );
		void	handle_client_message( int client_fd );
		void	process_command( int client_fd, const std::string &message);

		IRCCommand	*create_command( const std::string &command_name);

		struct ClientFdComparator
		{
			int client_fd;
			ClientFdComparator(int fd);
			bool operator()(const pollfd &pfd) const;
		};
};

#endif
