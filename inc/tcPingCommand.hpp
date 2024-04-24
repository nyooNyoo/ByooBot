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
  static handler PingHandler;
};

#endif
