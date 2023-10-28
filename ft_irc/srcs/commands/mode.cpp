#include "../../includes/server.hpp"
#include <sstream>
#include <vector>


void Server::mode(std::vector<struct pollfd>::iterator it, const std::string& params)
{
    std::istringstream ss(params);
    std::string channel_name, mode_string, optional_param;
    ss >> channel_name >> mode_string;

	std::string reply;

    Channel* channel = get_channel(channel_name);

	Client* client = get_client(it->fd);
    if (!client)
    {
        return;  // Unexpected case, a client should exist for the given file descriptor.
    }

    if (!channel)
    {
        reply = "403 ERR_NOSUCHCHANNEL :No such channel";
		client->set_write_buffer(reply);
        return;
    }



    // Only a channel operator can change modes
    if (!channel->is_operator(client->get_user()))
    {
        reply = "482 ERR_CHANOPRIVSNEEDED :You're not channel operator";
		client->set_write_buffer(reply);
        return;
    }

    bool add_mode = true;
	for (std::size_t i = 0; i < mode_string.length(); i++)
	{
		char mode = mode_string[i];
        switch (mode)
        {
            case '+':
                add_mode = true;
                break;

            case '-':
                add_mode = false;
                break;

            case 'i':
                channel->set_only_invite(add_mode);
                break;

            case 't':
                channel->set_topic_protected(add_mode);
                break;

            case 'k':
                if (add_mode)
                {
                    ss >> optional_param;
                    if (!optional_param.empty())
                        channel->set_key(optional_param);
                    else
					{
						reply = "475 ERR_KEYSET :Channel key already set";
						client->set_write_buffer(reply);
					}
                }
                else
                {
                    channel->remove_key();
                }
                break;

            case 'o':
                ss >> optional_param;
                if (!optional_param.empty())
                {
                    Client* targetClient = get_client(optional_param);
                    if (targetClient)
                    {
                        if (add_mode)
                            channel->add_operator(targetClient->get_user());
                        else
                            channel->remove_operator(targetClient->get_user());
                    }
                    else
                    {
                        reply = "441 ERR_USERNOTINCHANNEL " + optional_param + " " + channel->get_name() + " :They aren't on that channel";
						client->set_write_buffer(reply);
                    }
                }
                else
                {
					reply = "461 ERR_NEEDMOREPARAMS MODE :Not enough parameters";
					client->set_write_buffer(reply);
                }
                break;

            case 'l':
                if (add_mode)
                {
                    ss >> optional_param;
                    if (!optional_param.empty())
						 channel->set_max_users(atoi(optional_param.c_str()));

                    else
					{
						reply = "461 ERR_NEEDMOREPARAMS MODE :Not enough parameters";
						client->set_write_buffer(reply);
					}
                }
                else
                {
                    channel->remove_max_users();
                }
                break;

            default:
                reply = "472 ERR_UNKNOWNMODE :is unknown mode char to me";
				client->set_write_buffer(reply);
                break;
        }
    }
}
