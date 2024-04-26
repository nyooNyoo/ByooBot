#ifndef HELPCOMMAND__HPP__
#define HELPCOMMAND__HPP__

#include "../messagehandler.hpp"
#include <dpp/dpp.h>

void help_handler(const std::string &command, dpp::message_create_t src,
                  messagehandler *handler);

static std::string help_description = "Lists the commands idk";

#endif // !HELPCOMMAND__HPP__
