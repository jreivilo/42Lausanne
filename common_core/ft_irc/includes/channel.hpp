#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>    // std::find

#include "utils.hpp"


class Channel
{
	public:
		Channel(std::string name);
		~Channel(void);

		//SETTERS
		void 		set_name(std::string name);
		void 		set_topic(std::string topic);
		void 		set_mode(std::string mode);
		void 		set_key(std::string key);
		void 		set_max_users(int max_users);
		void 		set_users(std::vector<std::string> users);
		void 		set_only_invite(bool only_invite);
		void		set_topic_protected(bool topic_protected);

		//GETTERS
		std::string 				get_name(void) const;
		std::string 				get_topic(void) const;
		std::string 				get_mode(void) const;
		std::string 				get_key(void) const;
		int 						get_max_users(void) const;
		std::vector<std::string> 	get_users(void) const;
		std::string 				get_users_string(void) const;
		std::vector<std::string> 	get_ban_list(void) const;
		std::vector<std::string> 	get_invite_list(void) const;

		//OTHERS
		void add_user(std::string user);
		void remove_user(std::string user);
		void add_operator(std::string user);
		void remove_operator(std::string user);

		bool is_member(std::string user);
		bool is_operator(std::string user);
		bool is_topic_protected(void);
		bool is_invite_only(void);

		void	remove_key(void);
		void	remove_max_users(void);


	private:
		std::string				_name;
		std::string				_topic;
		std::string				_mode;
		std::string				_key;
		int 						_max_users;
		std::vector<std::string>	_users;
		std::vector<std::string>	_operators;

		bool						_only_invite;
		bool						_topic_protected;
		std::vector<std::string>	_ban_list;
		std::vector<std::string>	_invite_list;

};



#endif

