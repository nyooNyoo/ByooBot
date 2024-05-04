#ifndef PERMISSION_DEFAULT__HPP__
#define PERMISSION_DEFAULT__HPP__

#include <dpp/guild.h>
#include <dpp/permissions.h>
#include <dpp/snowflake.h>
#include <dpp/user.h>

namespace permission {

enum overide { NONE, SERVER_OWNER, BOT_OWNER };

struct minimum {
  // The default permission bitmask that must be passed
  dpp::permission permission_bitmask;
  // Special overides that aren't possible through native discord permissions
  // these apply such that the bitmask is ignored.
  permission::overide overide;
};

bool has_permission(permission::minimum rules, dpp::guild_member user);
} // namespace permission
#endif // INCLUDE_INC_PERMISSION_DEFAULT_HPP_
