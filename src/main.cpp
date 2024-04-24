#include <string>

#include <dpp/commandhandler.h>
#include <dpp/dpp.h>

#include "../inc/tcFileUtilities.hpp"
#include "../inc/tcMessageHandler.hpp"
#include "../inc/tcPingCommand.hpp"

static std::string BOT_TOKEN_FILE = "../bot.token";

int main() {

  std::string botToken = tcFileUtilities::ReadStringFromFile(BOT_TOKEN_FILE);

  dpp::cluster bot(botToken, dpp::i_default_intents | dpp::i_message_content);
  tcMessageHandler message_handler(&bot);

  bot.on_log(dpp::utility::cout_logger());

  message_handler.add_prefix("?");

  bot.on_ready([&message_handler](const dpp::ready_t &event) {
    message_handler.add_command(tcPingCommand::sCommand,
                                tcPingCommand::vsParameters,
                                tcPingCommand::PingHandler);
  });

  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
