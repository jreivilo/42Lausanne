#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

void Server::invite(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    std::istringstream ss(params);
    std::string nickname, channel_name;
    ss >> nickname >> channel_name;

    std::string reply;
    Client *cli = get_client(it->fd);

    if (!cli)
    {
        reply = "401 ERR_NOSUCHNICK " + cli->get_user() + " :No such nick/channel";
        cli->set_write_buffer(reply);
        return;
    }

    if (nickname.empty() || channel_name.empty())
    {
        reply = "461 ERR_NEEDMOREPARAMS INVITE :Not enough parameters";
        cli->set_write_buffer(reply);
        return;
    }

    Channel *channel = get_channel(channel_name);
    if (!channel)
    {
        reply = "403 ERR_NOSUCHCHANNEL :No such channel";
        cli->set_write_buffer(reply);
        return;
    }

    Client *targetClient = get_client(nickname);
    if (!targetClient)
    {
        reply = "401 ERR_NOSUCHNICK " + nickname + " :No such nick/channel";
        cli->set_write_buffer(reply);
        return;
    }

    if (!channel->is_member(cli->get_user()))
    {
        reply = "442 ERR_NOTONCHANNEL :You're not on that channel";
        cli->set_write_buffer(reply);
        return;
    }

    if (!channel->is_invite_only() && !channel->is_operator(cli->get_user()))
    {
        reply = "482 ERR_CHANOPRIVSNEEDED :You're not channel operator";
        cli->set_write_buffer(reply);
        return;
    }

    if (channel->is_member(targetClient->get_user()))
    {
        reply = "443 ERR_USERONCHANNEL " + nickname + " " + channel_name + " :is already on channel";
        cli->set_write_buffer(reply);
        return;
    }

    // Send RPL_INVITING numeric to the inviting client
    reply = "341 RPL_INVITING " + targetClient->get_user() + " " + channel->get_name();
    cli->set_write_buffer(reply);

    // Send INVITE message to the target client
    reply = ":" + cli->get_nick() + " INVITE " + targetClient->get_user() + " " + channel->get_name();
    targetClient->set_write_buffer(reply);
}
