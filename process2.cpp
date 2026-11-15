
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cctype>
#include <iterator>

using namespace std;

int main()
{
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    // Open first FIFO for reading
    int fd1 = open(fifo1, O_RDONLY);

    char ch;
    int characters = 0;
    int words = 0;
    int lines = 0;
    bool inWord = false;
    bool lastWasNewline = false;

    // Read data from first process
    while (read(fd1, &ch, 1) > 0)
    {
        if (ch == '\n')
        {
            lines++;
            lastWasNewline = true;
        }
        else
        {
            characters++;
            lastWasNewline = false;
        }

        if (isspace(static_cast<unsigned char>(ch)))
        {
            inWord = false;
        }
        else if (!inWord)
        {
            words++;
            inWord = true;
        }
    }

    close(fd1);

    // Handle a final line without newline
    if (characters > 0 && !lastWasNewline)
        lines++;

    // Write results into a text file
    ofstream fout("result.txt");

    fout << "Number of Characters: " << characters << endl;
    fout << "Number of Words: " << words << endl;
    fout << "Number of Lines: " << lines << endl;

    fout.close();

    // Read contents of the result file
    ifstream fin("result.txt");

    string result((istreambuf_iterator<char>(fin)),
                  istreambuf_iterator<char>());

    fin.close();

    // Open second FIFO for writing
    int fd2 = open(fifo2, O_WRONLY);

    // Send file contents to first process
    write(fd2, result.c_str(), result.length());

    close(fd2);

    return 0;
}

