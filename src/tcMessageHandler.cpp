#include "../inc/tcMessageHandler.hpp"
#include <dpp/cache.h>
#include <dpp/cluster.h>
#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/role.h>
#include <dpp/snowflake.h>
#include <dpp/stringops.h>

tcMessageHandler::tcMessageHandler(dpp::cluster *o) : owner(o) {
  messages = o->on_message_create([this](const dpp::message_create_t &event) {
    auto found_id = this->hooks.find(event.msg.channel_id);
    if (found_id == this->hooks.end() ||
        (found_id->second(event, this->owner))) {
      this->route(event);
    }
  });
};

tcMessageHandler &tcMessageHandler::set_owner(dpp::cluster *o) {
  owner = o;
  return *this;
}

tcMessageHandler::~tcMessageHandler() {
  if (messages) {
    owner->on_message_create.detach(messages);
  }
}

tcMessageHandler &tcMessageHandler::add_prefix(const std::string &prefix) {
  prefixes.emplace_back(prefix);
  return *this;
}

tcMessageHandler &
tcMessageHandler::add_command(const std::string &command,
                              const dpp::parameter_registration_t &params,
                              handler handler, const std::string &description) {
  command_info_t i;
  i.func = std::move(handler);
  i.parameters = params;
  i.description = description;
  commands[dpp::lowercase(command)] = i;
  return *this;
}

tcMessageHandler &tcMessageHandler::add_hook(const dpp::snowflake &channel_id,
                                             channel_hook channel_hook) {
  hooks[channel_id] = channel_hook;
  return *this;
}

tcMessageHandler &
tcMessageHandler::remove_hook(const dpp::snowflake &channel_id) {
  hooks.erase(hooks.find(channel_id));
  return *this;
}

bool tcMessageHandler::string_has_prefix(std::string &str) {
  for (auto &p : prefixes) {
    size_t prefix_length = dpp::utility::utf8len(p);
    if (dpp::utility::utf8substr(str, 0, prefix_length) == p) {
      str.erase(str.begin(), str.begin() + prefix_length);
      return true;
    }
  }
  return false;
}

void tcMessageHandler::route(const struct dpp::message_create_t &event) {
  std::string msg_content = event.msg.content;
  if (this->string_has_prefix(msg_content)) {
    std::stringstream ss(msg_content);
    std::string command;
    ss >> command;
    dpp::parameter_list_t called_params;
    auto found_cmd = this->commands.find(dpp::lowercase(command));
    if (found_cmd != this->commands.end()) {

      found_cmd->second.func(command, called_params, event, this);
    }
  }
}
