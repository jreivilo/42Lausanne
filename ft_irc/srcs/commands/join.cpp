#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

void Server::join(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    std::string channels_str, keys_str;
    std::vector<std::string> channels;
    std::vector<std::string> keys;
    std::string reply;
    std::istringstream buf(params);

    // Parse parameters
    getline(buf, channels_str, ' ');
    getline(buf, keys_str, ' ');

    // Tokenize channel and keys
    std::istringstream channels_buf(channels_str);
    std::string channel;
    while (getline(channels_buf, channel, ','))
    {
        channels.push_back(channel);
    }

    std::istringstream keys_buf(keys_str);
    std::string key;
    while (getline(keys_buf, key, ','))
    {
        keys.push_back(key);
    }

    // Get the client
    Client *cli = get_client(it->fd);
    for (size_t i = 0; i < channels.size(); ++i)
    {
        Channel *chan = get_channel(channels[i]);
        if (!chan)
        {
            reply = "403 ERR_NOSUCHCHANNEL :No such channel";
            cli->set_write_buffer(reply);
            continue;
        }
        std::vector<std::string> users = chan->get_users();
        if (i < keys.size() && chan->get_key() != keys[i])
        {
            reply = "475 ERR_BADCHANNELKEY :Cannot join channel (+k)";
            cli->set_write_buffer(reply);
            continue;
        }

        // check if the client is already in the channel, if so, ignore
        if (DEBUG)
        {
            std::cout << "[Server] Checking if " << cli->get_nick() << " is already in " << chan->get_name() << std::endl;
            // print channel users
            std::cout << "[Server] Channel users: \n";
            for (size_t i = 0; i < users.size(); ++i)
            {
                std::cout << users[i] << " ";
            }
            std::cout << std::endl;
        }
        if (find(users.begin(), users.end(), cli->get_nick()) != users.end())
        {
            reply = "443 ERR_USERONCHANNEL :is already on channel";
            cli->set_write_buffer(reply);
            continue;
        }

        // check if not banned
        //  if (std::find(chan->get_ban_list().begin(), chan->get_ban_list().end(), cli->get_nick()) != chan->get_ban_list().end()) {
        //      reply = "474 ERR_BANNEDFROMCHAN :Cannot join channel (+b)";
        //      cli->set_write_buffer(reply);
        //      continue;
        //  }

        // check if the channel is full
        if (chan->get_users().size() >= static_cast<std::vector<std::string>::size_type>(chan->get_max_users()))
        {
            reply = "471 ERR_CHANNELISFULL :Cannot join channel (+l)";
            cli->set_write_buffer(reply);
            continue;
        }

        // Finally, join the channel
        chan->add_user(cli->get_user());

        // Inform the client and channel members about the join
        cli->set_write_buffer("JOIN : " + chan->get_name());
        cli->set_write_buffer("332 RPL_TOPIC " + chan->get_name() + " :" + chan->get_topic());
        cli->set_write_buffer("353 RPL_NAMREPLY " + chan->get_name() + " :" + chan->get_users_string());

        // inform the channel members
        for (size_t i = 0; i < users.size(); ++i)
        {
            Client *user = get_client(users[i]);
            if (user)
                user->set_write_buffer(cli->get_nick() + " is joining the channel " + chan->get_name());
        }
    }
    // If the client successfully joins, server should send JOIN, RPL_TOPIC, and RPL_NAMREPLY
    // (Omitted in this example)
}
