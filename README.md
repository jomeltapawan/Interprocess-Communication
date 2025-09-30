# Interprocess-Communication
CECS 326 Project 1 on Interprocess Communication
## Overview
In this project, we will create a program that takes in a given file and copies the contents of that file into another file. To do this we will be utilizing the fork() and pipe() operating system methods to see how the processes are distributed.
## Learning Objectives
What we will learn in this project is how our operating system interacts with the processor in regards to tasks. It uses a process known as Interprocess Communication
## How to run the program
Note: I am running this on MacOS
Firstly please ensure that you have c++ installed on your system and it is available to use from the command line as we will be compiling a c++ file and running it through the use of the command line.

Run the command
$ c++ -std=c++11 filecopy.cpp -o filecopy
note: the "-std=c++11" flag may be omitted if the program is not compiling, this is just what I needed to run the program properly on my machine, not sure if it is needed for others
Then run:
$ ./filecopy input.txt copy.txt

If there is any trouble opening the copy.txt file, something I had to do locally was this command:
$ sudo chmod a+rwx copy.txt
This was needed in order to allow the user the appropriate permissions to open the copy.txt file

Hopefully this command successfully created a new file and piped/copied the input file's contents into the newly created copy file. Otherwise, there are plenty of error handling messages at each critical point in the program to point out where an error occurred.