#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    while (1)
    {
        int fromControl = open("mario", O_WRONLY | O_TRUNC, 0644);
        char toEdit[1024] = {0};
        read(fromControl, toEdit, sizeof(toEdit));
        int i;
        for (i = 0; i < 1024 && toEdit[i]; i++)
        {
            toEdit[i] += 1;
            if (toEdit[i] == 'a' || toEdit[i] == 'A')
            {
                toEdit[i] = '4';
            }
            else if (toEdit[i] == 'e' || toEdit[i] == 'E')
            {
                toEdit[i] = '3';
            }
            else if (toEdit[i] == 'I' || toEdit[i] == 'i')
            {
                toEdit[i] = '1';
            }
        }
        int toControl = open("luigi", O_RDONLY, 0644);
        write(toControl, toEdit, sizeof(toEdit));
    }
}