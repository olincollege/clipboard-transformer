// main.cpp
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#if __APPLE__
#include "DarwinClipboardHelper/DarwinClipboardHelper.h"
#endif

#include "clip/clip.h"
#include "gui.h"
#include "transformation.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  std::string input("");

#if __APPLE__
  // if there is a file path, read the file
  std::string filePath = ClipboardHelper::getFilePath();
  if (!filePath.empty()) {
    std::ifstream input_file;
    input_file.open(filePath.substr(7));

    if (!input_file.is_open()) {
      std::cerr << "could not open " + filePath << std::endl;
      return 0;
    }

    std::string line = "";
    while (std::getline(input_file, line)) {
      input += line + "\n";
    }

    input_file.close();
  } else {
    input = ClipboardHelper::getString();
  }
#else
  clip::get_text(input);
#endif

  if (input.empty()) {
    std::cerr << "no input" << std::endl;
    return 0;
  }

  // enumerate transformations
  std::string txfnPath = "./transformations";

  if (!fs::exists(txfnPath)) {
    std::cerr << "transformations directory (./transformations) does not exist"
              << std::endl;
    return 1;
  }

  TransformationMapPtr txfnMap = std::make_shared<TransformationMap>();
  for (const auto& p : fs::directory_iterator(txfnPath)) {
    if (!p.is_regular_file()) {
      continue;
    } else if (p.path().extension() != "") {
      continue;
    }
    Transformation* t =
        new Transformation(p.path().filename().string(), p.path());
    (*txfnMap)[t->name] = t;
  }

  start_gui(argc, argv, txfnMap, input);
  return 0;
}
