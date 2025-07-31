#define BUFFER_SIZE 2
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

char    *ft_strdupp(char *src)
{
    char *dest;
    int i;

    i = 0;
    while(src[i])
        i++;
    dest = malloc(sizeof(char) * i + 1);
    i = 0;
    while(src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int  buffer_read;
    static int  buffer_pos;
    char    line[70000];
    int     i;
    i = 0;
    while(1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        line[i++] = buffer[buffer_pos++]; 
        if (buffer[buffer_pos] == '\n')
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdupp(line));    
}