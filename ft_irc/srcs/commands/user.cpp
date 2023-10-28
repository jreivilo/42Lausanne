#include "../../includes/server.hpp"
#include <sstream>
#include <cctype>

bool Server::is_user_used(const std::string &user)
{
	for (std::map<const int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second.get_user() == user)
		{
			return true;
		}
	}
	return false;
}


void Server::user(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    std::string username, zero, asterisk, realname;
    std::string reply;
    std::istringstream buf(params);

    buf >> username >> zero >> asterisk;

    // Skip the leading colon if exists
    if (buf.peek() == ':')
    {
        buf.ignore();
    }

    getline(buf, realname);

    Client *cli = get_client(it->fd);

    // Check if client is already registered
    if (cli->get_is_registrered())
    {
        reply = "462 ERR_ALREADYREGISTERED :Unauthorized command (already registered)";
        cli->set_write_buffer(reply);
        return;
    }

    // Check if username or realname is empty
    if (username.empty() || realname.empty())
    {
        reply = "461 ERR_NEEDMOREPARAMS :Not enough parameters";
        cli->set_write_buffer(reply);
        return;
    }

    // If the clienbt already has a username, return error
    if (!cli->get_user().empty())
    {
        reply = "462 ERR_ALREADYREGISTERED :Unauthorized command (already registered)";
        cli->set_write_buffer(reply);
        return;
    }

	//if the user is not taken
	if (is_user_used(username))
	{
		reply = "463 ERR_ALREADYTAKEN :Unauthorized command (user already taken)";
		cli->set_write_buffer(reply);
		return;
	}

    // Truncate username if it exceeds max USERLEN (assuming USERLEN is defined)
    if (username.size() > USERLEN)
    {
        username.resize(USERLEN);
    }
	
    cli->set_user(username);
    cli->set_realname(realname);

    // If both username and nickname are set, set is_registered to true
    if (!cli->get_nick().empty() && !cli->get_user().empty())
    {
        cli->set_is_registered(true);
    }
}
