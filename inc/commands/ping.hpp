#ifndef PINGCOMMAND__HPP__
#define PINGCOMMAND__HPP__

#include <dpp/dispatcher.h>
#include <string>

#include "../message_handler.hpp"

void ping_handler(const std::string &command, dpp::message_create_t src,
                  message_handler *handler);

static std::string ping_description = "Pings the bot and returns the delay";

#endif //! PINGCOMMAND__HPP__
