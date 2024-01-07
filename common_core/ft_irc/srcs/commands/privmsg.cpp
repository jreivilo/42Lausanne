#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

bool Server::is_channel(std::string channel_name)
{
    std::map<const std::string, Channel>::iterator it = _channels.find(channel_name);
    if (it == _channels.end())
    {
        std::cout << RED << "[Server] Error: channel not found" << RESET << std::endl;
        return (false);
    }
    else
        return (true);
}

bool Server::is_nick(std::string nickname)
{
    std::map<const int, Client>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->second.get_nick() == nickname)
            return (true);
        it++;
    }
    std::cout << RED << "[Server] Error: client not found" << RESET << std::endl;
    return (false);
}

void Server::deliver_to_channel(std::vector<struct pollfd>::iterator it, std::string channel_name, std::string message)
{
    // Find the channel
    std::map<const std::string, Channel>::iterator channel_it = _channels.find(channel_name);
    if (channel_it == _channels.end())
    {
        std::string reply = "401 ERR_NOSUCHNICK " + channel_name + " :No such nick/channel";
        return;
    }

    // Retrieve the list of clients in this channel
    std::vector<std::string> users = channel_it->second.get_users();

    // Send the message to all users in the channel
    std::string reply = ":" + get_client(it->fd)->get_nick() + " PRIVMSG " + channel_name + " :" + message;
    for (size_t i = 0; i < users.size(); ++i)
    {
        Client *cli = get_client(users[i]);
        cli->set_write_buffer(reply);
    }
}

void Server::deliver_to_client(std::vector<struct pollfd>::iterator it, std::string nickname, std::string message)
{
    // Find the client
    std::map<const int, Client>::iterator client_it = _clients.find(it->fd);
    if (client_it == _clients.end())
    {
        std::string reply = "401 ERR_NOSUCHNICK " + nickname + " :No such nick/channel";
        return;
    }

    // Send the message to the client
    std::string reply = ":" + get_client(it->fd)->get_nick() + " PRIVMSG " + nickname + " :" + message;
    Client *cli = get_client(nickname);
    cli->set_write_buffer(reply);
}

void Server::privmsg(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    std::string reply;
    if (params.empty())
    {
        reply = "461 ERR_NEEDMOREPARAMS PRIVMSG :Not enough parameters";
        Client *cli = get_client(it->fd);
        cli->set_write_buffer(reply);
        return;
    }
    Client *cli = get_client(it->fd);
    // Extract target and message from params
    std::string target, message;
    std::istringstream iss(params);
    iss >> target >> std::ws;
    std::getline(iss, message);

    if (DEBUG)
    {
        std::cout << "[Server] target: " << target << std::endl;
        std::cout << "[Server] message: " << message << std::endl;
    }

    // check for : in message
    if (message[0] == ':')
        message.erase(0, 1);
    else
    {
        reply = "461 ERR_NEEDMOREPARAMS PRIVMSG :Not enough parameters";
        cli->set_write_buffer(reply);
        return;
    }

    // Check if the target is a channel or user
    if (is_channel(target))
    {
        // Check for bans, moderations, etc.
        // if (isBanned(it, target)) {
        //     reply = "404 ERR_CANNOTSENDTOCHAN :Cannot send to channel";
        // 	cli->set_write_buffer(reply);
        //     return;
        // }

        // Deliver the message to the channel
        deliver_to_channel(it, target, message);
    }
    else if (is_nick(target))
    {
        // check for is away

        // Deliver the message to the user
        deliver_to_client(it, target, message);
    }
    else
    {
        reply = "401 ERR_NOSUCHNICK " + target + " :No such nick/channel";
        cli->set_write_buffer(reply);
    }
}