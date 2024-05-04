#include <cstdlib>
#include <string>

#include <dpp/dpp.h>
#include <getopt.h>

#include "../inc/commands/commands.hpp"
#include "../inc/commands/help.hpp"
#include "../inc/commands/ping.hpp"
#include "../inc/config.hpp"
#include "../inc/message_handler.hpp"

nlohmann::json config;

int main(int argc, char *argv[]) {

  /* Parse command line arguments */
  int dev = 0;
  int index;
  char arg;
  struct option longopts[] = {{"dev", no_argument, &dev, 1},
                              {"help", no_argument, NULL, 'h'}};

  while ((arg = getopt_long_only(argc, argv, "", longopts, &index)) != -1) {
    switch (arg) {
    case 0:
      break;
    case 'h':
      std::cout << "Usage: " << argv[0] << " [--help] [--dev]\n";
      std::cout << "--help:  Prints this menu and closes the program\n";
      std::cout << "--dev:   Uses the dev bot token and restricts the bot to\n"
                   "         the channel specified in config.json\n";
      return EXIT_SUCCESS;
      break;
    case '?':
    default:
      std::cerr << "Unknown parameter '" << argv[optind - 1] << "'\n";
      std::cerr << "Use '" << argv[0] << "--help' to print arguments";
      return EXIT_FAILURE;
      break;
    }
  }

  conf::set_dev(dev);
  std::string token = conf::is_dev() ? conf::get_config("devtoken")
                                     : conf::get_config("maintoken");

  /* Initialize commands */
  std::unordered_map<std::string, command_definition> commands = {
      {"ping", {ping_handler, ping_permission, ping_description}},
      {"help", {help_handler, help_permission, help_description}}};

  /* Start bot */
  dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);
  message_handler message_handler(&bot);

  bot.on_log(dpp::utility::cout_logger());

  message_handler.add_prefix("?");

  bot.on_ready(
      [&](const dpp::ready_t &event) { message_handler.commands = commands; });

  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
