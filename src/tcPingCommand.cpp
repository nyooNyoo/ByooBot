#include <dpp/dpp.h>

#include <chrono>
#include <string>

void PingHandler(const std::string &command, const dpp::parameter_list_t &parameters, dpp::command_source src) 
{
    //auto now = std::chrono::system_clock::now();
    //auto sent = std::chrono::system_clock::from_time_t(src.message_event.value().msg.sent);
    //std::chrono::duration<double> elapsed_seconds = sent - now;
    src.message_event.value().reply("pong");

};

std::string command = "ping";

dpp::parameter_registration_t parameters = {};

