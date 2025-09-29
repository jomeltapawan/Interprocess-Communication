/*
 *
 * filecopy.cpp
 * 
 * This program copies files using a pipe.
 *
 */

 #include <unistd.h>
 #include <stdio.h>
 #include <fcntl.h>
 #include <iostream>
 #include <sys/types.h>
 #include <sys/wait.h>

 #define READ_END 0
 #define WRITE_END 1

 using namespace std;

 int main(int argc, char *argv[])
 {
    if (argc != 3) { // Error handling for incorrect command line usage
        cerr << "Error Usage:" << argv[0] << "(source_file) (destination_file)" << endl;
        return 1;
    } // Command line should be ./filecopy.cpp source_file destination_file

    const char* source_file = argv[1];
    const char* destination_file = argv[2];

    // Declaration of pipe
    int pipePr[2];
    // Checking if pipe initialization has an error
    if (pipe(pipePr) == - 1) {
      cerr << "pipe error";
      return 1;
    }
    // create a child process
    pid_t pid = fork();

    if (pid < 0) {
      cerr << "fork error"; // error creating child
      return 1;
    }
    if (pid > 0) {
      // parent process
      close(pipePr[0]); // parent doesn’t read from pipe

      // opens the source file to read
      int srcRead = open(source_file, O_RDONLY);

      if (srcRead < 0) { // if open fails
        cerr << "open source";
        close(pipePr[1]); // close write end of pipe
        return 1;
      }
    }
    else { // if child process (pid == 0)
      // child will close pipePr[1] and read from pipePr[0]
    }
 }