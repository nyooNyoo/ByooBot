#ifndef TCPINGCOMMAND_HPP_
#define TCPINGCOMMAND_HPP_

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <string>

#include "tcMessageHandler.hpp"

class tcPingCommand {
public:
  // command name
  static std::string sCommand;
  // param settings
  static dpp::parameter_registration_t vsParameters;
  // function to be wrapped in dpp::command_handler
  static void PingHandler(const std::string &command,
                          const dpp::parameter_list_t &parameters,
                          dpp::message_create_t,
                          tcMessageHandler::tcMessageHandler *);
};

#endif
