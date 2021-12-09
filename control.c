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
        char in[1024] = {0};
        int toWorker = open("mario", O_WRONLY | O_TRUNC, 0644);
        printf("Enter something for the child to destroy:\n");
        read(STDIN_FILENO, in, sizeof(char) * 1023);
        write(toWorker, in, strlen(in) * sizeof(char));

        int fromWorker = open("luigi", O_RDONLY, 0644);
        char result[1024] = {0};
        read(fromWorker, result, sizeof(result));

        printf("Response: %s\n", result);

        //     char toEdit[1024] = {0};
        //     read(pipes[0], toEdit, sizeof(toEdit));
        //     close(pipes[0]);
        //     int i;
        //     for (i = 0; i < 1024 && toEdit[i]; i++){
        //         toEdit[i] += 1;
        //         if (toEdit[i] == 'a' || toEdit[i] == 'A'){
        //             toEdit[i] = '4';
        //         }else if (toEdit[i] == 'e' || toEdit[i] == 'E'){
        //             toEdit[i] = '3';
        //         }else if (toEdit[i] == 'I' || toEdit[i] == 'i'){
        //             toEdit[i] = '1';
        //         }
        //     }
        //     write(pipes[3], toEdit, sizeof(toEdit));
        //     return 0;
        // }
    }
}