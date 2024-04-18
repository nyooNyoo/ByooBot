#include "../inc/tcMessageHandler.hpp"
#include <cstdint>
#include <dpp/cache.h>
#include <dpp/commandhandler.h>
#include <dpp/role.h>
#include <dpp/snowflake.h>
#include <dpp/stringops.h>

void tcMessageHandler::route(const struct dpp::message_create_t &event) {
  std::string msg_content = event.msg.content;
  if (this->string_has_prefix(msg_content)) {
    std::stringstream ss(msg_content);
    std::string command;
    ss >> command;
    auto found_cmd = this->commands.find(dpp::lowercase(command));
    if (found_cmd != this->commands.end()) {
      if (found_cmd->second.guild_id &&
          found_cmd->second.guild_id != event.msg.guild_id) {
        return;
      }
      dpp::parameter_list_t call_params;

      for (auto &p : found_cmd->second.parameters) {
        dpp::command_parameter param;

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
          if (x == "yes" || x == "true") {
            y = true;
          }
        } break;
        }
        call_params.emplace_back(p.first, param);
      }
      found_cmd->second.func(command, call_params, event, this);
    }
  }
}
