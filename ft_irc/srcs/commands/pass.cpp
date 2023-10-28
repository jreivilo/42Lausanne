#include "../../includes/server.hpp"

void Server::pass(std::vector<struct pollfd>::iterator it, const std::string &params)
{
    // Retrieve the client corresponding to the current iterator.
    Client *cli = get_client(it->fd);

    // If the client doesn't exist, log an error message or take appropriate action.
    if (!cli)
    {
        std::cerr << "Error: Received a PASS command from an unknown client (fd: " << it->fd << ")." << std::endl;
        // Optionally, you can remove this poll descriptor from the list.
        return;
    }

    // Make sure the client is not already registered.
    if (cli->get_is_registrered())
    {
        // Reply with ERR_ALREADYREGISTERED (462)
        std::string reply = ":server 462 :Unauthorized command (already registered)";
        cli->set_write_buffer(reply);
        return;
    }

    // Check if the password parameter is empty.
    if (params.empty())
    {
        // Reply with ERR_NEEDMOREPARAMS (461)
        std::string reply = ":server 461 PASS :Not enough parameters";
        cli->set_write_buffer(reply);
        return;
    }

    if (params == "LS 302")
    {
        cli->set_authorized(true);
        std::string reply = "Password Correct";
        cli->set_write_buffer(reply);
        std::cout << "Password Correct" << std::endl;
    }

    // Validate the password.
    else if (params != _password)
    {
        // Reply with ERR_PASSWDMISMATCH (464)
        std::string reply = ":server 464 :Password Incorrect";
        cli->set_write_buffer(reply);

        // Optionally, close the connection here.
        return;
    }

    // If the code reaches here, the password is correct.
    // Update the client's state to reflect that a valid password has been received.
    cli->set_authorized(true);
    std::string reply = "Password Correct";
    cli->set_write_buffer(reply);
    std::cout << "Password Correct" << std::endl;
}
