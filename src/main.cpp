#include <fstream>
#include <string>

#include <dpp/commandhandler.h>
#include <dpp/dpp.h>
#include <unordered_map>

#include "../inc/commands/commands.hpp"
#include "../inc/commands/help.hpp"
#include "../inc/commands/ping.hpp"
#include "../inc/message_handler.hpp"

nlohmann::json config;

int main() {

  /* Load config file */
  std::ifstream config_stream("../config.json");
  config = nlohmann::json::parse(config_stream);

  /* Initialize commands */
  std::unordered_map<std::string, command_definition> commands = {
      {"ping", {ping_handler, ping_description}},
      {"help", {help_handler, help_description}}};

  /* Start bot */
  dpp::cluster bot(config["devtoken"],
                   dpp::i_default_intents | dpp::i_message_content);
  message_handler message_handler(&bot);

  bot.on_log(dpp::utility::cout_logger());

  message_handler.add_prefix("?");

  bot.on_ready(
      [&](const dpp::ready_t &event) { message_handler.commands = commands; });

  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
