#include <string>

#include <dpp/commandhandler.h>
#include <dpp/dpp.h>
#include <unordered_map>

#include "../inc/commands/commands.hpp"
#include "../inc/commands/help.hpp"
#include "../inc/commands/ping.hpp"
#include "../inc/messagehandler.hpp"
#include "../inc/tcFileUtilities.hpp"

static std::string BOT_TOKEN_FILE = "../bot.token";

int main() {

  std::string botToken = tcFileUtilities::ReadStringFromFile(BOT_TOKEN_FILE);

  std::unordered_map<std::string, command_definition> commands = {
      {"ping", {ping_handler, ping_description}},
      {"help", {help_handler, help_description}}};

  dpp::cluster bot(botToken, dpp::i_default_intents | dpp::i_message_content);
  messagehandler message_handler(&bot);

  bot.on_log(dpp::utility::cout_logger());

  message_handler.add_prefix("?");

  bot.on_ready(
      [&](const dpp::ready_t &event) { message_handler.commands = commands; });

  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
