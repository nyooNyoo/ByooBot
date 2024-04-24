#ifndef TCMESSAGEHANDLER_HPP_
#define TCMESSAGEHANDLER_HPP_

#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

#include <dpp/snowflake.h>
#include <unordered_map>

class tcMessageHandler;

typedef std::function<bool(dpp::message_create_t, class dpp::cluster *)>
    channel_hook;

typedef std::function<void(const std::string &, const dpp::parameter_list_t,
                           dpp::message_create_t, class tcMessageHandler *)>
    handler;

struct command_info_t {
  handler func;

  dpp::parameter_registration_t parameters;

  std::string description;
};

class tcMessageHandler {
public:
  std::unordered_map<std::string, command_info_t> commands;

  std::unordered_map<dpp::snowflake, channel_hook> hooks;

  std::vector<std::string> prefixes;

  class dpp::cluster *owner;

  dpp::event_handle messages;

public:
  tcMessageHandler(class dpp::cluster *o);

  ~tcMessageHandler();

  tcMessageHandler &set_owner(class dpp::cluster *o);

  tcMessageHandler &add_prefix(const std::string &prefix);

  tcMessageHandler &add_command(const std::string &command,
                                const dpp::parameter_registration_t &params,
                                handler handler,
                                const std::string &description = "");

  tcMessageHandler &add_hook(const dpp::snowflake &channel_id,
                             channel_hook channel_hook);

  tcMessageHandler &remove_hook(const dpp::snowflake &channel_id);

  void route(const struct dpp::message_create_t &event);

  bool string_has_prefix(std::string &s);
};

#endif // !TCMESSAGEHANDLER_HPP_
