#pragma once
#include <filesystem>
#include <unordered_map>

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

  /**
   * Creates a new transformation object.
   * @param name
   * @param path
   */
  Transformation(std::string name, std::filesystem::path path);

  /**
   * Runs the transformation on the given input.
   *
   * The input is written to the transformation's stdin, and the
   * transformation's stdout and stderr are read. If the transformation exits
   * with a non-zero exit code, the output property will contain the stderr
   * output. Otherwise, the output property will data from stdout.
   * @param input A pointer to a string containing the input. The string will
   * not be modified, and the pointer will not be freed.
   * @return A pointer to a TransformationResult object. The pointer must be
   * freed.
   */
  TransformationResult* transform(std::string* input);
};

using TransformationMap = std::unordered_map<std::string, Transformation*>;
using TransformationMapPtr = std::shared_ptr<TransformationMap>;
