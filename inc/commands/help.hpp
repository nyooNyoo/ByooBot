#ifndef HELPCOMMAND__HPP__
#define HELPCOMMAND__HPP__

#include "../message_handler.hpp"
#include <dpp/dpp.h>
#include <dpp/permissions.h>

void help_handler(const std::string &command, dpp::message_create_t src,
                  message_handler *handler);

const permission::minimum help_permission = {dpp::permission(),
                                             permission::overide::NONE};

const std::string help_description = "Lists the commands idk";

#endif // !HELPCOMMAND__HPP__
