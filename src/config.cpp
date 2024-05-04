#include "../inc/config.hpp"

std::string conf::get_config(const std::string &key) {
  return conf::config_doc[key].get<std::string>();
}

bool conf::is_dev() { return dev; }

void conf::set_dev(int dev_flag) { dev = dev_flag; }
