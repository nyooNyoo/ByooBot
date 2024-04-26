#ifndef COMMAND__HPP__
#define COMMAND__HPP__

#include <dpp/dpp.h>

#include <string>

typedef std::function<void(const std::string &, dpp::message_create_t,
                           class messagehandler *)>
    command_handler;

struct command_definition {
  // Executed upon command call
  command_handler function;
  // Description of the command, used in help command
  std::string description;
};

#endif // !COMMAND__HPP__
