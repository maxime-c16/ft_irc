/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:07:09 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/05 16:11:46 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRCServer.hpp"

IRCServer::IRCServer( void )
{

}

IRCServer::IRCServer( int port, const std::string &password) : password(password), _port(port), _server_fd(-1)
{
	create_server_socket();
	set_non_blocking(_server_fd);
	set_server_addr();
	bind_socket();
	start_listening();

	pollfd	server_pollfd = { _server_fd, POLLIN, 0 };
	_pollfds.push_back(server_pollfd);
}

IRCServer::~IRCServer( void )
{
	close(_server_fd);
}

int	IRCServer::GetServerFD( void )
{
	return (_server_fd);
}

bool	IRCServer::_signal = false;
void	IRCServer::signal_handler( int signum )
{
	(void)signum;
	std::cout << std::endl << "Signal received" << std::endl;
	_signal = true;
}

void	IRCServer::error( const std::string &msg )
{
	perror(msg.c_str());
	exit(EXIT_FAILURE);
}

void	IRCServer::set_non_blocking( int sockfd )
{
	int	flags;

	flags = fcntl(sockfd, F_GETFL, O_NONBLOCK);
	if (flags == -1)
		error("Error: Fcntl F_GETFL");
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
		error("Error: Fcntl F_SETFL");
}

void	IRCServer::create_server_socket( void )
{
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0)
		error("Error: socket");
}

void	IRCServer::set_server_addr( void )
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_addr.s_addr = INADDR_ANY;
	_server_addr.sin_port = htons(_port);
}

void	IRCServer::bind_socket( void )
{
	if (bind(_server_fd, (sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
		error("Error: Couldn't bind server fd");
}

void	IRCServer::start_listening( void )
{
	if (listen(_server_fd, 5) < 0)
		error("Error: Couldn't listen on server fd");
	std::cout << "Server Listening ..." << std::endl;
}

int	IRCServer::accept_new_client( void )
{
	int	client_fd;

	client_fd = accept(_server_fd, nullptr, nullptr);
	if (client_fd < 0)
	{
		if (errno != EWOULDBLOCK)
			error("Error: Cannot accept client");
	}
	else
	{
		set_non_blocking(client_fd);
		std::cout << "New client connected: " << client_fd << std::endl;
	}
	return (client_fd);
}

void	IRCServer::handle_client_message( int client_fd )
{
	char	buffer[BUFF_SIZE];
	int		bytes_read;

	std::memset(buffer, 0, sizeof(buffer));
	bytes_read = read(client_fd, buffer, sizeof(buffer));
	if (bytes_read < 0)
		if (errno != EWOULDBLOCK)
			error("Error: Cannot read from client fd");
	if (bytes_read == 0)
	{
		std::cout << "Client disconnected" << std::endl;
		close(client_fd);
		std::vector<pollfd>::iterator it = std::remove_if(_pollfds.begin(), _pollfds.end(), ClientFdComparator(client_fd));
		_pollfds.erase(it, _pollfds.end());
		clients.erase(client_fd);
	}
	else
	{
		std::cout << "Received message from " << client_fd << ": " << buffer << "\r\n" << std::endl;
		process_command(client_fd, buffer);
	}
}

void	IRCServer::process_command( int client_fd, const std::string &message )
{
	std::istringstream	iss(message);
	std::string			command;

	iss >> command;
	if (!command.empty())
	{
		IRCCommand	*cmd = create_command(command);
		if (!cmd)
		{
			if (this->channels.find(this->clients[client_fd].current_channel) != this->channels.end())
			{
				this->channels[this->clients[client_fd].current_channel].broadcast_except(this->clients[client_fd], message);
			}
			else
			{
				send(client_fd, "Error: Join a channel to start speaking, try `JOIN <channel>`.\r\n", 65, 0);
			}
			return ;
		}
		cmd->execute(*this, client_fd, iss);
		delete cmd;
	}
	else
		send(client_fd, "Error: command missing, try `CMD <args>`.\r\n", 44, 0);
}

IRCCommand	*IRCServer::create_command( const std::string &command_name)
{
	if (command_name == "NICK")
		return new NickCmd();
	else if (command_name == "PASS")
		return new PassCmd();
	else if (command_name == "USER")
		return new UserCmd();
	else if (command_name == "OPER")
		return new OperCmd();
	else if (command_name == "PING")
		return new PingCmd();
	else if (command_name == "KILL")
		return new KillCmd();
	else if (command_name == "QUIT")
		return new QuitCmd();
	else if (command_name == "JOIN")
		return new JoinCmd();
	else if (command_name == "PART")
		return new PartCmd();
	else if (command_name == "JOIN")
		return new JoinCmd();
	else if (command_name == "INVITE")
		return new InviteCmd();
	else if (command_name == "ACCEPT")
		return new AcceptCmd();
	else if (command_name == "REJECT")
		return new RejectCmd();
	else if (command_name == "KICK")
		return new KickCmd();
	return (nullptr);
}

void	IRCServer::start( void )
{
	int		poll_count;
	int		client_fd;
	pollfd	client_pfd;
	size_t	i;

	while (_signal == false)
	{
		poll_count = poll(_pollfds.data(), _pollfds.size(), -1);
		if (poll_count < 0 && IRCServer::_signal == false)
			throw (std::runtime_error("Error: poll"));
		i = 0;
		while (i < _pollfds.size())
		{
			if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _server_fd)
				{
					client_fd = accept_new_client();
					if (client_fd >= 0)
					{
						client_pfd.fd = client_fd;
						client_pfd.events = POLLIN;
						client_pfd.revents = 0;
						_pollfds.push_back(client_pfd);
						clients[client_fd].username = "";
					}
				}
				else
					handle_client_message(_pollfds[i].fd);
			}
			i++;
		}
	}
}

IRCServer::ClientFdComparator::ClientFdComparator( int fd ) : client_fd(fd)
{

}

bool	IRCServer::ClientFdComparator::operator()( const pollfd &pfd ) const
{
	return (pfd.fd == client_fd);
}
