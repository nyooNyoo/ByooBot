#ifndef TCPINGCOMMAND_HPP_
#define TCPINGCOMMAND_HPP_

#include <string>
#include <dpp/dpp.h>

class tcPingCommand 
{
public:
    // contains args for dpp::commandhandler
    static std::string command;

    static dpp::parameter_registration_t parameters;
    // function to be wrapped in dpp::command_handler
    static void PingHandler(const std::string &command, const dpp::parameter_list_t &parameters, dpp::command_source src);
};

#endif