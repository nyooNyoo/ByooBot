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

      for (auto &p : found_cmd->second.parameters) {
        dpp::command_parameter param;

        /* Check for end of stream */
        if (!ss) {
          break;
        }

        switch (p.second.type) {
        case dpp::pt_string: {
          std::string x;
          ss >> x;
          param = x;
        } break;
        case dpp::pt_role: {
          std::string x;
          ss >> x;
          if (x.length() > 4 && x[0] == '<' && x[1] == '&') {
            dpp::snowflake rid =
                dpp::from_string<uint64_t>(x.substr(2, x.length() - 1));
            dpp::role *r = dpp::find_role(rid);
            if (r) {
              param = *r;
            }
          }
        } break;
        case dpp::pt_channel: {
          std::string x;
          ss >> x;
          if (x.length() > 4 && x[0] == '<' && x[1] == '#') {
            dpp::snowflake cid =
                dpp::from_string<uint64_t>(x.substr(2, x.length() - 1));
            dpp::channel *c = dpp::find_channel(cid);
            if (c) {
              param = *c;
            }
          }
        } break;
        case dpp::pt_user: {
          std::string x;
          ss >> x;
          if (x.length() > 4 && x[0] == '<' && x[1] == '@') {
            dpp::snowflake uid =
                dpp::from_string<uint64_t>(x.substr(2, x.length() - 1));
            dpp::user *u = dpp::find_user(uid);
            if (u) {
              dpp::resolved_user m;
              m.user = *u;
              dpp::guild *g = dpp::find_guild(event.msg.guild_id);
              if (g->members.find(uid) != g->members.end()) {
                m.member = g->members[uid];
              }
              param = m;
            }
          }
        } break;
        case dpp::pt_integer: {
          int64_t x = 0;
          ss >> x;
          param = x;
        } break;
        case dpp::pt_double: {
          double x = 0;
          ss >> x;
          param = x;
        } break;
        case dpp::pt_boolean: {
          std::string x;
          bool y = false;
          ss >> x;
          x = dpp::lowercase(x);
          if (x == "yes" || x == "1" || x == "true") {
            y = true;
          }
          param = y;
        } break;
        }

        /* Add parameter to the list */
        called_params.emplace_back(p.first, param);
      }

      found_cmd->second.func(command, called_params, event, this);
    }
  }
}
