#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

void Server::kick(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    // Split params to get channel, user, and optionally comment.
    std::istringstream iss(params);
    std::string channel, user, comment;
    iss >> channel >> user;
    if (!iss.eof())
    {
        getline(iss, comment);
        if (!comment.empty() && comment[0] == ':')
            comment.erase(0, 1);
    }

    Client *requestingClient = get_client(it->fd);
    // Validation
    std::string reply;
    Channel *chan = get_channel(channel);
    if (!chan)
    {
        reply = "403 ERR_NOSUCHCHANNEL :No such channel";
        requestingClient->set_write_buffer(reply);
        return;
    }

    if (!requestingClient || !chan->is_member(requestingClient->get_user()))
    {
        reply = "442 ERR_NOTONCHANNEL :You're not on that channel";
        requestingClient->set_write_buffer(reply);
        return;
    }

    if (!chan->is_operator(requestingClient->get_user()))
    {
        reply = "482 ERR_CHANOPRIVSNEEDED :You're not channel operator";
        requestingClient->set_write_buffer(reply);
        return;
    }

    Client *kickedClient = get_client(user);
    if (!kickedClient || !chan->is_member(kickedClient->get_user()))
    {
        reply = "441 ERR_USERNOTINCHANNEL :They aren't on that channel";
        requestingClient->set_write_buffer(reply);
        return;
    }

    // Kick the user
    chan->remove_user(kickedClient->get_user());

    // Notify the kicked user and other members of the channel
    std::string kickNotification = requestingClient->get_nick() + " kicked you from " + channel;
    if (!comment.empty())
    {
        kickNotification += " (" + comment + ")";
    }
    kickedClient->set_write_buffer(kickNotification);

    // Notify other users in the channel
    kickNotification = user + " was kicked by " + requestingClient->get_nick();
    if (!comment.empty())
    {
        kickNotification += " (" + comment + ")";
    }
    std::vector<std::string> users = chan->get_users();
    for (size_t i = 0; i < users.size(); ++i)
    {
        Client *user = get_client(users[i]);
        if (user)
            user->set_write_buffer(kickNotification);
    }
}
