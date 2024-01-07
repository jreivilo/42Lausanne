#include "../../includes/client.hpp"

Client::Client(int socket) : _socket(socket), _authorized(false), _registrered(false), _connected(true)
{
	(void)_socket;
}

Client::~Client(void)
{
}

// SETTERS
void Client::set_authorized(bool authorized)
{
	_authorized = authorized;
}

void Client::set_is_registered(bool registrered)
{
	_registrered = registrered;
}

void Client::set_is_connected(bool connected)
{
	_connected = connected;
}

void Client::set_read_buffer(std::string buffer)
{
	_read_buffer = buffer;
}

void Client::append_read_buffer(std::string buffer, int size)
{
	_read_buffer.append(buffer, 0, size);
}

void Client::set_write_buffer(std::string buffer)
{
	// append the buffer to the write buffer and add every message a \r\n
	_write_buffer.append(buffer);
	_write_buffer.append(EOL);
}

void Client::set_nick(std::string nick)
{
	_nick = nick;
}

void Client::set_user(std::string user)
{
	_user = user;
}

void Client::set_realname(std::string realname)
{
	_realname = realname;
}

// GETTERS
bool Client::get_is_authorized(void) const
{
	return (_authorized);
}

bool Client::get_is_registrered(void) const
{
	return (_registrered);
}

bool Client::get_is_connected(void) const
{
	return (_connected);
}

std::string Client::get_read_buffer(void) const
{
	return (_read_buffer);
}

std::string Client::get_write_buffer(void) const
{
	return (_write_buffer);
}

std::string Client::get_nick(void) const
{
	return (_nick);
}

std::string Client::get_user(void) const
{
	return (_user);
}

// OTHERS
void Client::clear_read_buffer(void)
{
	_read_buffer.clear();
}

void Client::clear_write_buffer(void)
{
	_write_buffer.clear();
}
