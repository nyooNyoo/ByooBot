#include "../inc/file_utilities.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string file_utilities::ReadStringFromFile(const std::string &arcFilePath) {
  const std::ifstream inputStream(arcFilePath, std::ios_base::binary);
  if (inputStream.fail()) {
    throw std::runtime_error("Failed to open file: " + arcFilePath);
  }

  std::stringstream buffer;
  buffer << inputStream.rdbuf();
  std::string fileString = buffer.str();
  file_utilities::TrimLineReturn(fileString);

  return fileString;
}

void file_utilities::TrimLineReturn(std::string &arcInputString) {
  arcInputString.erase(
      std::remove_if(arcInputString.begin(), arcInputString.end(),
                     [](auto ch) { return (ch == '\n' || ch == '\r'); }),
      arcInputString.end());
}
