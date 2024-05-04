#ifndef COMMAND__HPP__
#define COMMAND__HPP__

#include <dpp/dpp.h>
#include <string>

#include "../permission_default.hpp"

typedef std::function<void(const std::string &, dpp::message_create_t,
                           class message_handler *)>
    command_handler;

struct command_definition {
  // Executed upon command call
  command_handler function;
  // The minimum permission level to use this command
  permission::minimum minimum_permission;
  // Description of the command, used in help command
  std::string description;
};

#endif // !COMMAND__HPP__
