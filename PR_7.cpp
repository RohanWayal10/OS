#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
using namespace std;

#define SIZE 1024

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    char filename[SIZE];
    char buffer[SIZE];
    int fd;
    ssize_t n;

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Pipe creation failed");
        exit(1);
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0)
    {
        // Parent Process
        close(pipe1[0]);
        close(pipe2[1]);

        cout << "Enter the file pathname: ";
        cin >> filename;

        // Send filename to child
        write(pipe1[1], filename, strlen(filename) + 1);
        close(pipe1[1]);

        cout << "\nContents of the file:\n";

        // Receive file contents from child
        while ((n = read(pipe2[0], buffer, SIZE)) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(pipe2[0]);
        wait(NULL);
    }
    else
    {
        // Child Process
        close(pipe1[1]);
        close(pipe2[0]);

        // Receive filename from parent
        read(pipe1[0], filename, SIZE);
        close(pipe1[0]);

        // Open the file
        fd = open(filename, O_RDONLY);

        if (fd < 0)
        {
            perror("File opening failed");
            close(pipe2[1]);
            exit(1);
        }

        // Read file contents and send to parent
        while ((n = read(fd, buffer, SIZE)) > 0)
        {
            write(pipe2[1], buffer, n);
        }

        close(fd);
        close(pipe2[1]);
        exit(0);
    }

    return 0;
}
