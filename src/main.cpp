#include <tcFileUtilities.hpp>

#include <dpp/dpp.h>
    
static std::string BOT_TOKEN_FILE = "../bot.token";
    
int main() {

    std::string botToken = tcFileUtilities::ReadStringFromFile(BOT_TOKEN_FILE);

    dpp::cluster bot(botToken);
    
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
            if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });
    
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("ping", "Ping pong!", bot.me.id)
            );
        }
    });
    
    bot.start(dpp::st_wait);
}