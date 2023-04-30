#include "transformation.h"

#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

#if !__APPLE__
#include <sys/wait.h> // macOS doesn't need this import, it's in unistd.h
#endif

Transformation::Transformation(std::string name, std::filesystem::path path) {
  this->name = name;
  this->path = path;
}

TransformationResult* Transformation::transform(std::string* input) {
  int stdin_pipe[2], stdout_pipe[2], stderr_pipe[2];
  pipe(stdin_pipe);
  pipe(stdout_pipe);
  pipe(stderr_pipe);

  pid_t pid = fork();

  TransformationResult* result = new TransformationResult();

  if (pid == -1) {
    result->output = "failed to fork";
    result->exitCode = 1;
  }

  if (pid == 0) {
    // child process
    close(stdin_pipe[1]);   // we won't write to stdin
    close(stdout_pipe[0]);  // we won't read from stdout
    close(stderr_pipe[0]);  // we won't read from stderr

    // duplicate needed ends of pipes, since we're gonna exec
    dup2(stdin_pipe[0], STDIN_FILENO);
    dup2(stdout_pipe[1], STDOUT_FILENO);
    dup2(stderr_pipe[1], STDERR_FILENO);

    const char arg[] = "transform";
    char* const argv[] = {(char*)this->path.c_str(), (char*)arg, NULL};

    execv(this->path.c_str(), argv);

    // execv failed
    std::cerr << "failed to run the transformation" << std::endl;
    exit(1);
  } else {
    // parent process

    // close pipe ends we won't use
    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);

    // write our input to its stdin pipe
    write(stdin_pipe[1], input->c_str(), input->size());
    close(stdin_pipe[1]);  // sends EOF

    // wait for child to finish
    int status;
    waitpid(pid, &status, 0);

    int exit_status = WEXITSTATUS(status);

    int reading_pipe = exit_status == 0 ? stdout_pipe[0] : stderr_pipe[0];

    // process exited successfully, read stdout
    char buf[1024];
    std::string output = "";
    int n;
    while ((n = read(reading_pipe, buf, sizeof(buf))) > 0) {
      output += std::string(buf, n);
    }

    close(stdout_pipe[0]);
    close(stderr_pipe[0]);

    result->output = output;
    result->exitCode = exit_status;
  }

  return result;
}
