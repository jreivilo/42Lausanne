#include "../../includes/channel.hpp"

Channel::Channel(std::string name) : _name(name), _topic(""), _mode(""), _key(""), _max_users(0), _only_invite(false), _topic_protected(false)
{
}

Channel::~Channel(void)
{
}

// SETTERS
void Channel::set_name(std::string name)
{
	_name = name;
}

void Channel::set_topic(std::string topic)
{
	_topic = topic;
}

void Channel::set_mode(std::string mode)
{
	_mode = mode;
}

void Channel::set_key(std::string key)
{
	_key = key;
}

void Channel::set_users(std::vector<std::string> users)
{
	_users = users;
}

void Channel::set_max_users(int max_users)
{
	_max_users = max_users;
}

void Channel::set_only_invite(bool only_invite)
{
	_only_invite = only_invite;
}

void Channel::set_topic_protected(bool topic_protected)
{
	_topic_protected = topic_protected;
}

// GETTERS
std::string Channel::get_name(void) const
{
	return (_name);
}

std::string Channel::get_topic(void) const
{
	return (_topic);
}

std::string Channel::get_mode(void) const
{
	return (_mode);
}

std::string Channel::get_key(void) const
{
	return (_key);
}

int Channel::get_max_users(void) const
{
	return (_max_users);
}

std::vector<std::string> Channel::get_users(void) const
{
	return (_users);
}

std::string Channel::get_users_string(void) const
{
	std::string users_string;
	std::vector<std::string>::const_iterator it = _users.begin();
	while (it != _users.end())
	{
		users_string.append(*it);
		users_string.append(" ");
		it++;
	}
	return (users_string);
}

std::vector<std::string> Channel::get_ban_list(void) const
{
	return (_ban_list);
}

std::vector<std::string> Channel::get_invite_list(void) const
{
	return (_invite_list);
}

// OTHERS
void Channel::add_user(std::string user)
{
	_users.push_back(user);
}

void Channel::remove_user(std::string user)
{
	std::vector<std::string>::iterator it = _users.begin();
	while (it != _users.end())
	{
		if (*it == user)
		{
			_users.erase(it);
			return;
		}
		it++;
	}
}

void Channel::add_operator(std::string user)
{
	_operators.push_back(user);
}

void Channel::remove_operator(std::string user)
{
	std::vector<std::string>::iterator it = _operators.begin();
	while (it != _operators.end())
	{
		if (*it == user)
		{
			_operators.erase(it);
			return;
		}
		it++;
	}
}

bool Channel::is_member(std::string user)
{
	std::cout << "user: " << user << std::endl;
	std::vector<std::string>::iterator it = _users.begin();
	while (it != _users.end())
	{
		std::cout << "it: " << *it << std::endl;
		if (*it == user)
			return (true);
		it++;
	}
	std::cout << RED << "[Server] Error: user not found" << RESET << std::endl;
	return (false);
}

bool Channel::is_operator(std::string user)
{
	std::vector<std::string>::iterator it = _operators.begin();
	while (it != _operators.end())
	{
		if (*it == user)
			return (true);
		it++;
	}
	return (false);
}

bool Channel::is_topic_protected(void)
{
	return (_topic_protected);
}

bool Channel::is_invite_only(void)
{
	return (_only_invite);
}

void Channel::remove_key(void)
{
	_key = "";
}

void Channel::remove_max_users(void)
{
	_max_users = 0;
}