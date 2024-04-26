#ifndef FILEUTILITIES__HPP__
#define FILEUTILITIES__HPP__

#include <string>

class file_utilities {
public:
  // used to read file contents and load it into memory as a string
  static std::string ReadStringFromFile(const std::string &arcFilePath);

  // some lines contain a line/carriage return - this will remove it from string
  static void TrimLineReturn(std::string &arcInputString);
};

#endif // !FILEUTILITIES__HPP__
