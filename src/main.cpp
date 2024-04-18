#include <string>

#include <dpp/commandhandler.h>
#include <dpp/dpp.h>

// #include "../include/tcBot.hpp"
#include "../inc/tcFileUtilities.hpp"
#include "../inc/tcPingCommand.hpp"

static std::string BOT_TOKEN_FILE = "../bot.token";

int main() {

  std::string botToken = tcFileUtilities::ReadStringFromFile(BOT_TOKEN_FILE);

  dpp::cluster bot(botToken, dpp::i_default_intents | dpp::i_message_content);
  dpp::commandhandler command_handler(&bot);

  bot.on_log(dpp::utility::cout_logger());

  command_handler.add_prefix("?");

  bot.on_ready([&command_handler](const dpp::ready_t &event) {
    command_handler.add_command(tcPingCommand::sCommand,
                                tcPingCommand::vsParameters,
                                tcPingCommand::PingHandler);
  });

  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
