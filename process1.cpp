
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    // Open first FIFO for writing
    int fd1 = open(fifo1, O_WRONLY);

    string line;
    cout << "Enter sentences (type END to finish):" << endl;

    while (true)
    {
        getline(cin, line);

        if (line == "END")
            break;

        line += "\n";
        write(fd1, line.c_str(), line.length());
    }

    close(fd1);

    // Open second FIFO for reading
    int fd2 = open(fifo2, O_RDONLY);

    char buffer[1024];
    int n;

    cout << "\nResults received from Second Process:\n";

    while ((n = read(fd2, buffer, sizeof(buffer))) > 0)
    {
        cout.write(buffer, n);
    }

    close(fd2);

    return 0;
}

