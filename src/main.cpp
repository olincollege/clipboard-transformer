// main.cpp
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "ClipboardHelper/ClipboardHelper.h"
#include "gui.h"
#include "transformation.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  std::string input = "";

  // read the clipboard
  std::string filePath = ClipboardHelper::getFilePath();
  std::string url = ClipboardHelper::getURL();
  std::string text = ClipboardHelper::getString();

  // if there is a file path, read the file
  if (!filePath.empty()) {
    std::ifstream input_file;
    input_file.open(filePath.substr(7));
    input = "";

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
    if (!text.empty()) {
      input = text;
    }
  }

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

  std::unordered_map<std::string, Transformation*> txfnMap;
  for (const auto& p : fs::directory_iterator(txfnPath)) {
    if (!p.is_regular_file()) {
      continue;
    } else if (p.path().extension() != "") {
      continue;
    }
    Transformation* t =
        new Transformation(p.path().filename().string(), p.path());
    txfnMap[t->name] = t;
  }

  // print transformations
  if (txfnMap.size() < 1) {
    std::cout << "no transformations found" << std::endl;
    return 0;
  }

  // select transformation, for now just uppercase
  Transformation* selected_txfn = txfnMap["uppercase"];

  if (!selected_txfn) {
    std::cout << "no transformation selected" << std::endl;
    return 0;
  }

  // run transformation
  TransformationResult output = selected_txfn->transform(input);

  // handle output
  if (output.exitCode != 0) {
    std::cout << "transformation failed with exit code " << output.exitCode
              << std::endl;
    return 1;
  }

  ClipboardHelper::setString(output.output);

  // not freeing txfnMap because it lives as long as the program
  return 0;
}