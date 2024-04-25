#ifndef MESSAGEHANDLER_HPP_
#define MESSAGEHANDLER_HPP_

#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/snowflake.h>

#include "commands/commands.hpp"
#include <unordered_map>

typedef std::function<bool(dpp::message_create_t, class dpp::cluster *)>
    channel_hook;

class messagehandler {
public:
  std::unordered_map<std::string, command_definition> commands;

  std::unordered_map<dpp::snowflake, channel_hook> hooks;

  std::vector<std::string> prefixes;

  class dpp::cluster *owner;

  dpp::event_handle messages;

public:
  messagehandler(class dpp::cluster *o);

  ~messagehandler();

  messagehandler &set_owner(class dpp::cluster *o);

  messagehandler &add_prefix(const std::string &prefix);

  messagehandler &add_command(const std::string &command,
                              command_handler handler,
                              const std::string &description = "");

  messagehandler &add_hook(const dpp::snowflake &channel_id,
                           channel_hook channel_hook);

  messagehandler &remove_hook(const dpp::snowflake &channel_id);

  void route(const struct dpp::message_create_t &event);

  bool string_has_prefix(std::string &s);
};

#endif // !MESSAGEHANDLER_HPP_
