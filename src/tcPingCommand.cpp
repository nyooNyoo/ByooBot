#include "../inc/tcPingCommand.hpp"
#include "../inc/tcMessageHandler.hpp"

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

#include <chrono>
#include <string>

std::string tcPingCommand::sCommand = "ping";
dpp::parameter_registration_t tcPingCommand::vsParameters = {};

handler tcPingCommand::PingHandler =
    [](const std::string &command, const dpp::parameter_list_t &parameters,
       dpp::message_create_t src, tcMessageHandler *handler) {
      int iNow = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
      int iSent = src.msg.id.get_creation_time() * 100;
      int iDiff = iSent - iNow;
      src.send("Pong! (" + std::to_string(iDiff) + " ms)");
    };
