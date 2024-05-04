#ifndef DATABASE__HPP__
#define DATABASE__HPP__

#include <dpp/dpp.h>
#include <mysql/mysql.h>

namespace db {

bool connect(class dpp::cluster *bot, const std::string &host,
             const std::string &user, const std::string &pass,
             const std::string &db, int port);

bool close();

} // namespace db

#endif //! DATABASE__HPP__
