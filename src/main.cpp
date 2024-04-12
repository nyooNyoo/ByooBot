#include <tcFileUtilities.hpp>
#include <tcPingCommand.hpp>

#include <dpp/dpp.h>

#include <string>
    
static std::string BOT_TOKEN_FILE = "../bot.token";
    
int main() {

    std::string botToken = tcFileUtilities::ReadStringFromFile(BOT_TOKEN_FILE);

    dpp::cluster bot(botToken, dpp::i_default_intents | dpp::i_message_content);
    dpp::commandhandler command_handler(&bot);

    bot.on_log(dpp::utility::cout_logger());

    command_handler.add_prefix("?");
    
    bot.on_ready([&command_handler](const dpp::ready_t& event) {

        command_handler.add_command( tcPingCommand::command, tcPingCommand::parameters, tcPingCommand::PingHandler );
    });
    
    bot.start(dpp::st_wait);
}