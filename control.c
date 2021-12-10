#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    mkfifo("mario", 0644);
    mkfifo("luigi", 0644);
    while (1)
    {
        // read from standard in and sends it via mario pipe to worker
        char in[1024] = {0};
        int toWorker = open("mario", O_WRONLY);
        printf("Enter something for the child to destroy:\n");
        read(STDIN_FILENO, in, sizeof(char) * 1023);
        write(toWorker, in, strlen(in) * sizeof(char));
        close(toWorker);

        // read result from luigi pipe and prints result
        int fromWorker = open("luigi", O_RDONLY);
        char result[1024] = {0};
        read(fromWorker, result, sizeof(result));

        printf("Response: %s\n", result);

        close(fromWorker);
    }
}