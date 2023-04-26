#pragma once
#include <filesystem>

struct TransformationResult {
  std::string output;
  int exitCode;
};

/**
 * Represents a transformation.
 *
 * A transformation is a program that takes a string as input and outputs a
 * string. It is expected to be located in the `transformations` directory.
 */
class Transformation {
 public:
  // name of the transformation, e.g. "uppercase"
  std::string name;
  // path to the transformation, e.g. "./transformations/uppercase"
  std::filesystem::path path;

  // constructs a transformation with the given name and path
  Transformation(std::string name, std::filesystem::path path);
  // runs the transformation with the given input passed in via stdin
  TransformationResult transform(std::string input);
};
