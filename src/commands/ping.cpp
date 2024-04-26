#include "../../inc/commands/ping.hpp"

#include <dpp/dpp.h>

#include <chrono>
#include <dpp/utility.h>
#include <string>

void ping_handler(const std::string &command, dpp::message_create_t src,
                  messagehandler *handler) {
  double now = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
  double sent = src.msg.id.get_creation_time() * 1000;
  int diff = (now - sent);

  src.send("Pong! (" + std::to_string(diff) + " ms)");
};
