#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

void Server::topic(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    size_t spacePos = params.find(' ');
    std::string channel_name = params.substr(0, spacePos);
    std::string topic = spacePos != std::string::npos ? params.substr(spacePos + 1) : "";

    Client *cli = get_client(it->fd);
    Channel *channel = get_channel(channel_name);
    std::string reply;

    if (!channel)
    {
        reply = "403 ERR_NOSUCHCHANNEL :No such channel";
        cli->set_write_buffer(reply);
        return;
    }

    Client *client = get_client(it->fd);
    if (!client)
    {
        reply = "401 ERR_NOSUCHNICK " + client->get_user() + " :No such nick/channel";
        cli->set_write_buffer(reply);
        return;
    }

    // Check if client is a member of the channel
    if (!channel->is_member(client->get_user()))
    {
        reply = "442 ERR_NOTONCHANNEL :You're not on that channel";
        cli->set_write_buffer(reply);
        return;
    }

    // If topic is not given, return current topic
    if (topic.empty())
    {
        if (channel->get_topic().empty())
        {
            reply = "331 RPL_NOTOPIC " + channel_name + " :No topic is set";
            cli->set_write_buffer(reply);
        }
        else
        {
            reply = "332 RPL_TOPIC " + channel_name + " :" + channel->get_topic();
            cli->set_write_buffer(reply);
        }
        return;
    }

    // If the topic is given, check if client has permission to set the topic
    if (!channel->is_topic_protected() && !channel->is_operator(client->get_user()))
    {
        reply = "482 ERR_CHANOPRIVSNEEDED :You're not channel operator";
        cli->set_write_buffer(reply);
        return;
    }

    // Set the new topic
    channel->set_topic(topic);

    // Notify all clients in the channel about the topic change
    std::vector<std::string> users = channel->get_users();
    for (size_t i = 0; i < users.size(); ++i)
    {
        Client *cli = get_client(users[i]);
        cli->set_write_buffer("TOPIC " + channel_name + " :" + topic);
    }
}
