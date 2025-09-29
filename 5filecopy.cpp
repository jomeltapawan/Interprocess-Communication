#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>

#define BUFFER_SIZE 4096

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <source_file> <destination_file>" << endl;
        return 1;
    }

    const char* srcFile = argv[1];
    const char* destFile = argv[2];

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process: read from source and write to pipe
        close(pipefd[0]); // close read end of pipe

        int srcFd = open(srcFile, O_RDONLY);
        if (srcFd < 0) {
            perror("open source");
            close(pipefd[1]);
            return 1;
        }
char buffer[BUFFER_SIZE];
        ssize_t bytesRead;
        while ((bytesRead = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
            if (write(pipefd[1], buffer, bytesRead) != bytesRead) {
                perror("write to pipe");
                close(srcFd);
                close(pipefd[1]);
                return 1;
            }
        }

        if (bytesRead < 0) {
            perror("read source");
        }

        close(srcFd);
        close(pipefd[1]); // done writing
        wait(nullptr);    // wait for child
    } else {
        // Child process: read from pipe and write to destination
        close(pipefd[1]); // close write end of pipe

        int destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (destFd < 0) {
            perror("open destination");
            close(pipefd[0]);
            return 1;
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            if (write(destFd, buffer, bytesRead) != bytesRead) {
                perror("write destination");
                close(destFd);
                close(pipefd[0]);
                return 1;
            }
        }

        if (bytesRead < 0) {
            perror("read pipe");
        }

        close(destFd);
        close(pipefd[0]);
    }

    return 0;
}
