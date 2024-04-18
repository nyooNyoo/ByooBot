#include "../inc/tcPingCommand.hpp"
#include "../inc/tcMessageHandler.hpp"

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

#include <chrono>
#include <string>

std::string tcPingCommand::sCommand = "ping";
dpp::parameter_registration_t tcPingCommand::vsParameters = {};

void tcPingCommand::PingHandler(const std::string &command,
                                const dpp::parameter_list_t &parameters,
                                dpp::message_create_t,
                                tcMessageHandler::tcMessageHandler) {
  // auto now = std::chrono::system_clock::now();
  // auto sent =
  // std::chrono::system_clock::from_time_t(src.message_event.value().msg.sent);
  // std::chrono::duration<double> elapsed_seconds = sent - now;
  src.message_event.value().send("test");
};
