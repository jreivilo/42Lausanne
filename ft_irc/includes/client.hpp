#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

#include "utils.hpp"

class Client
{
public:
	Client(int socket);
	~Client(void);

	// SETTERS
	void set_authorized(bool authorized);
	void set_is_registered(bool registrered);
	void set_is_connected(bool connected);
	void set_read_buffer(std::string buffer);
	void append_read_buffer(std::string buffer, int size);
	void set_write_buffer(std::string buffer);
	void set_nick(std::string nick);
	void set_user(std::string user);
	void set_realname(std::string realname);

	// GETTERS
	bool get_is_authorized(void) const;
	bool get_is_registrered(void) const;
	bool get_is_connected(void) const;
	std::string get_read_buffer(void) const;
	std::string get_write_buffer(void) const;

	std::string get_nick(void) const;
	std::string get_user(void) const;

	// OTHERS
	void clear_read_buffer(void);
	void clear_write_buffer(void);

private:
	int _socket;
	std::string _read_buffer;
	std::string _write_buffer;

	std::string _nick;
	std::string _user;
	std::string _realname;

	bool _authorized;
	bool _registrered;
	bool _connected;
};

#endif
