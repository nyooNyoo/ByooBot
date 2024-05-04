#ifndef CONFIG__HPP__
#define CONFIG__HPP__

#include <dpp/nlohmann/json.hpp>
#include <fstream>

namespace conf {

const nlohmann::json config_doc =
    nlohmann::json::parse(std::ifstream("../config.json"));

static int dev;

bool is_dev();

void set_dev(int dev_flag);

std::string get_config(const std::string &key);
} // namespace conf

#endif // !CONFIG__HPP__
