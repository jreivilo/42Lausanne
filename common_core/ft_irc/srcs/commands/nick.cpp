#include "../../includes/server.hpp"
#include <sstream>
#include <cctype> // for std::isdigit and std::isalnum

bool is_valid_nickname(const std::string &nickname)
{
    if (nickname.empty())
    {
        return false;
    }

    if (std::isdigit(nickname[0]))
    {
        return false;
    }

    for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); ++it)
    {
        char c = *it;
        if (!std::isalnum(c) && c != '[' && c != ']' && c != '{' && c != '}' && c != '\\' && c != '|')
        {
            return false;
        }
    }

    return true;
}

bool Server::is_nickname_used(const std::string &nickname)
{
    for (std::map<const int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second.get_nick() == nickname)
        {
            return true;
        }
    }
    return false;
}

void Server::nick(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    std::string nickname;
    std::string reply;
    std::istringstream buf(params);

    getline(buf, nickname, ' ');

    Client *cli = get_client(it->fd);

    if (nickname.empty())
    {
        reply = "431 ERR_NONICKNAMEGIVEN :No nickname given";
        cli->set_write_buffer(reply);
        return;
    }

    if (!is_valid_nickname(nickname))
    {
        reply = "432 ERR_ERRONEUSNICKNAME " + nickname + " :Erroneous nickname";
        cli->set_write_buffer(reply);
        return;
    }

    if (is_nickname_used(nickname))
    {
        reply = "433 ERR_NICKNAMEINUSE " + nickname + " :Nickname is already in use";
        cli->set_write_buffer(reply);
        return;
    }

    // You can also inform other clients about the nickname change here if needed.
    if (!cli->get_nick().empty())
    {
        reply = ":" + cli->get_nick() + " changed his nickname to " + nickname;
        cli->set_write_buffer(reply);
    }
    cli->set_nick(nickname);
	// If both username and nickname are set, set is_registered to true
    if (!cli->get_nick().empty() && !cli->get_user().empty())
    {
        cli->set_is_registered(true);
    }
}
