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
    if (argc != 3) {
        cout << "Error Usage:" << argv[0] << "(source_file) (destination_file)" << endl;
        return 0;
    }
 }