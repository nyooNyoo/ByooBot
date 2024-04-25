#include "../../inc/commands/ping.hpp"

#include <dpp/dpp.h>

#include <dpp/utility.h>
#include <string>

void ping_handler(const std::string &command, dpp::message_create_t src,
                  messagehandler *handler) {
  int now = dpp::utility::time_f() * 100;
  int sent = src.msg.id.get_creation_time() * 100;
  int diff = sent - now;
  src.send("Pong! (" + std::to_string(diff) + " ms)");
};
