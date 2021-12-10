#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    while (1)
    {   
        // read from mario pipe and processes what went through
        int fromControl = open("mario", O_RDONLY);
        char toEdit[1024] = {0};
        read(fromControl, toEdit, sizeof(toEdit));
        close(fromControl);
        
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

        // write the manipulated string and sends it to luigi pipe and control
        int toControl = open("luigi", O_WRONLY);
        write(toControl, toEdit, sizeof(toEdit));
        close(toControl);
    }
}