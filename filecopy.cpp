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
        cout << "Error Usage:" << argv[0] << "(source_file) (destination_file)" << endl;
        return 0;
    } // Command line should be ./filecopy.cpp source_file destination_file

    const char* source_file = argv[1];
    const char* destination_file = argv[2];
 }