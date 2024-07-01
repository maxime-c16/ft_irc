/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:23:30 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/01 17:07:17 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int	main(int ac, char **av)
{
	int		port;
	std::string	password;

	port = 0;
	if (ac != 3)
	{
		std::cerr << "Usage : " << av[0] << "<port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}

	port = std::stoi(av[1]);
	password = av[2];

	IRCServer	server(port, password);

	try
	{
		signal(SIGINT, &IRCServer::signal_handler);
		signal(SIGQUIT, &IRCServer::signal_handler);
		server.start();
	}
	catch ( const std::exception &e )
	{
		close(server.GetServerFD());
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Server closed." << std::endl;
	return (0);
}
