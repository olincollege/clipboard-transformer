// ClipboardHelper.h
#pragma once
#include <string>

class ClipboardHelper {
 public:
  static std::string getString();
  static std::string getFilePath();
  static std::string getURL();
  static void setString(const std::string& input);
};
