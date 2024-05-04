#ifndef MESSAGE_HANDLER__HPP__
#define MESSAGE_HANDLER__HPP__

#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/snowflake.h>

#include "commands/commands.hpp"
#include <unordered_map>

typedef std::function<bool(dpp::message_create_t, class dpp::cluster *)>
    channel_hook;

class message_handler {
public:
  std::unordered_map<std::string, command_definition> commands;

  std::unordered_map<dpp::snowflake, channel_hook> hooks;

  std::vector<std::string> prefixes;

  class dpp::cluster *owner;

  dpp::event_handle messages;

public:
  message_handler(class dpp::cluster *o);

  ~message_handler();

  message_handler &set_owner(class dpp::cluster *o);

  message_handler &add_prefix(const std::string &prefix);

  message_handler &add_command(const std::string &command,
                               command_handler handler,
                               const std::string &description = "");

  message_handler &remove_command(const std::string &command);

  message_handler &add_hook(const dpp::snowflake &channel_id,
                            channel_hook channel_hook);

  message_handler &remove_hook(const dpp::snowflake &channel_id);

  void route(const struct dpp::message_create_t &event);

  bool string_has_prefix(std::string &s);
};

#endif // !MESSAGE_HANDLER__HPP__
