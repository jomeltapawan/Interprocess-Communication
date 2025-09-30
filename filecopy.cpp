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

 #define BUFFER_SIZE 4096
 #define READ_END 0
 #define WRITE_END 1

 using namespace std;

 int main(int argc, char *argv[])
 {
    if (argc != 3) { // Error handling for incorrect command line usage
      cerr << "Error Usage: " << argv[0] << "(source_file) (destination_file)" << endl;
      return 1;
    } // Command line should be ./filecopy.cpp source_file destination_file

    const char* source_file = argv[1];
    const char* destination_file = argv[2];

    // Declaration of pipe
    int pipePr[2];
    // Checking if pipe initialization has an error
    if (pipe(pipePr) == - 1) {
      cerr << "Error occurred in pipe initialization";
      return 1;
    }
    // create a child process
    pid_t pid = fork();

    if (pid < 0) {
      cerr << "Error occurred when creating fork"; // error creating child
      return 1;
    }
    if (pid > 0) {
      // parent process
      // Reading from source and writing to the pipe buffer
      close(pipePr[0]); // Closes pipe because the parent does not read from the pipe

      // opens the source file to read
      int srcFile = open(source_file, O_RDONLY);

      if (srcFile < 0) { // if open fails
        cerr << "Unable to open source file '" << argv[1] << "'";
        close(pipePr[1]); // close write end of pipe
        return 1;
      }
    char buffer[BUFFER_SIZE];     // Initializing the buffer using size of 4kb stated earlier in the header of the program
    ssize_t readChunks;   //Counter for how many bytes are read

    while((readChunks = read(srcFile, buffer, BUFFER_SIZE)) > 0) {
      if (write(pipePr[1], buffer, readChunks) != readChunks) {
        cerr << "Error writing to the pipe"; // Error message in writing to pipe
        close(srcFile); //closes file descriptor
        close(pipePr[1]); // closes the pipe parent write process
        return 1; 
      }
    }

    if (readChunks < 0) {
      cerr << "Error Reading pipe";
    }

    close(srcFile);
    close(pipePr[1]); // closes the parent process
    wait(nullptr); // Waits for child process
    }

    else {
      // child process
      // Reading from the pipe and writing to the destination
      close(pipePr[1]); // Ensure Parent process is closed
      int dstFile = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC | 0644); // Opens the destination file in the necessary permissions to create a file, truncate data, and write to it
      if (dstFile < 0) {
        cerr << "Error opening destination file '" << argv[2] << "'";
        close(pipePr[0]); // Ensures pipe is not hanging when program exits
        return 1;
      }

      // Buffer for the child process
      char buffer[BUFFER_SIZE];
      ssize_t readChunks;

      while ((readChunks = read(pipePr[0], buffer, BUFFER_SIZE)) > 0) {
        if (write(dstFile, buffer, readChunks) != readChunks) { //Error Handling for the write to destination process
          cerr << "Error writing to the destination file";
          close(dstFile); // Closes the file to prevent overhead
          close(pipePr[0]); // Closes the pipe so it is not left hanging, will continue process when re-executed
          return 1;
        }
      }

      close(dstFile);
      close(pipePr[0]); //Closing the child proces
    }

// Yay you're done!!
 }