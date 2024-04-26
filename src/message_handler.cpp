#include "../inc/message_handler.hpp"
#include <dpp/cache.h>
#include <dpp/cluster.h>
#include <dpp/commandhandler.h>
#include <dpp/dispatcher.h>
#include <dpp/role.h>
#include <dpp/snowflake.h>
#include <dpp/stringops.h>

message_handler::message_handler(dpp::cluster *o) : owner(o) {
  messages = o->on_message_create([this](const dpp::message_create_t &event) {
    auto found_id = this->hooks.find(event.msg.channel_id);
    if (found_id == this->hooks.end() ||
        (found_id->second(event, this->owner))) {
      this->route(event);
    }
  });
};

message_handler &message_handler::set_owner(dpp::cluster *o) {
  owner = o;
  return *this;
}

message_handler::~message_handler() {
  if (messages) {
    owner->on_message_create.detach(messages);
  }
}

message_handler &message_handler::add_prefix(const std::string &prefix) {
  prefixes.emplace_back(prefix);
  return *this;
}

message_handler &message_handler::add_command(const std::string &command,
                                              command_handler handler,
                                              const std::string &description) {
  command_definition i;
  i.function = std::move(handler);
  i.description = description;
  commands[dpp::lowercase(command)] = i;
  return *this;
}

message_handler &message_handler::add_hook(const dpp::snowflake &channel_id,
                                           channel_hook channel_hook) {
  hooks[channel_id] = channel_hook;
  return *this;
}

message_handler &
message_handler::remove_hook(const dpp::snowflake &channel_id) {
  hooks.erase(hooks.find(channel_id));
  return *this;
}

bool message_handler::string_has_prefix(std::string &str) {
  for (auto &p : prefixes) {
    size_t prefix_length = dpp::utility::utf8len(p);
    if (dpp::utility::utf8substr(str, 0, prefix_length) == p) {
      str.erase(str.begin(), str.begin() + prefix_length);
      return true;
    }
  }
  return false;
}

void message_handler::route(const struct dpp::message_create_t &event) {
  std::string msg_content = event.msg.content;
  if (this->string_has_prefix(msg_content)) {
    std::stringstream ss(msg_content);
    std::string command;
    ss >> command;
    dpp::parameter_list_t called_params;
    auto found_cmd = this->commands.find(dpp::lowercase(command));
    if (found_cmd != this->commands.end()) {
      found_cmd->second.function(command, event, this);
    }
  }
}
