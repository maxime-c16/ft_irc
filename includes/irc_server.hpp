/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:03 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/01 15:20:57 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP

# define IRC_SERVER_HPP

# include "ft_irc.hpp"

struct ClientFdComparator
{
	int client_fd;
	ClientFdComparator(int fd);
	bool operator()(const pollfd &pfd) const;
};

class	IRCServer
{
	public:

		IRCServer(int port, const std::string &password);
		~IRCServer();

		void	start( void );

	private:

		int							_port;
		int							_server_fd;
		std::string					_password;
		std::map<int, std::string>	_clients;
		std::vector<pollfd>			_pollfds;
		sockaddr_in					_server_addr;

		void	error( const std::string &msg );
		void	set_non_blocking( int sockfd );
		void	create_server_socket( void );
		void	set_server_addr( void );
		void	bind_socket( void );
		void	start_listening( void );
		int		accept_new_client( void );
		void	handle_client_message( int client_fd );
};

#endif
