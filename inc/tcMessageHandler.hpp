#ifndef TCMESSAGEHANDLER_HPP_
#define TCMESSAGEHANDLER_HPP_

#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

#include <unordered_map>

class tcMessageHandler;

struct command_info_t {
  std::function<void(const std::string &, const dpp::parameter_list_t,
                     dpp::message_create_t, tcMessageHandler *)>
      func;

  dpp::parameter_registration_t parameters;

  dpp::snowflake guild_id;
};

class tcMessageHandler : dpp::commandhandler {
public:
  std::unordered_map<std::string, command_info_t> commands;
  void route(const struct dpp::message_create_t &event);
};

#endif // !TCMESSAGEHANDLER_HPP_
