#include <cstdint>
#include <dpp/dpp.h>
#include <dpp/guild.h>
#include <dpp/permissions.h>
#include <dpp/snowflake.h>
#include <string>
#include <vector>

#include "../inc/config.hpp"
#include "../inc/permission_default.hpp"

bool permission::has_permission(permission::minimum rules,
                                dpp::guild_member user) {
  switch (rules.overide) {
  case NONE:
    // Check the users permissions against that required to use the command.
    // Because the permissions are stored as a bitmask we can compare the
    // cumulative bitwise OR of all roles the user has.
    return dpp::permission(
               std::accumulate(
                   user.get_roles().begin(), user.get_roles().end(), 0,
                   [](uint64_t acc, const dpp::snowflake &role_id) {
                     return acc | dpp::find_role(role_id)->permissions;
                   }))
        .can(rules.permission_bitmask);
    break;
  case SERVER_OWNER:
    // Very simple and straightforward check thanks to the library.
    return user.is_server_owner();
    break;
  case BOT_OWNER:
    // TODO handler invalid string
    return user.user_id == std::stoull(conf::get_config("devtoken"));
  }
}
