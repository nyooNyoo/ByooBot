#include "../../inc/commands/help.hpp"
#include <dpp/dpp.h>
#include <sstream>

void help_handler(const std::string &command, dpp::message_create_t src,
                  message_handler *handler) {
  std::stringstream ss;
  for (auto &[key, value] : handler->commands) {
    ss << key << ": " << value.description << "\n";
  }
  src.send(ss.str());
}
