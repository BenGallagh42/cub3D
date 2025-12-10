#include "get_next_line.h"

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (*s == (char)c)
        return ((char *)s);
    return (NULL);
}

size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return (NULL);
    result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!result)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';
    return (result);
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len;
    size_t i;

    len = ft_strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *extract_line(char *buffer)
{
    char *line;
    size_t i;

    i = 0;
    if (!buffer[i])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
        return (NULL);
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *update_buffer(char *buffer)
{
    char *new_buffer;
    size_t i;
    size_t j;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    new_buffer = malloc(ft_strlen(buffer) - i + 1);
    if (!new_buffer)
        return (NULL);
    i++;
    j = 0;
    while (buffer[i])
        new_buffer[j++] = buffer[i++];
    new_buffer[j] = '\0';
    free(buffer);
    return (new_buffer);
}

char *read_and_store(int fd, char *buffer)
{
    char *temp;
    char *new_buffer;
    int bytes_read;

    temp = malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(temp);
            free(buffer);
            return (NULL);
        }
        temp[bytes_read] = '\0';
        new_buffer = ft_strjoin(buffer, temp);
        free(buffer);
        buffer = new_buffer;
    }
    free(temp);
    return (buffer);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buffer)
    {
        buffer = ft_strdup("");
        if (!buffer)
            return (NULL);
    }
    buffer = read_and_store(fd, buffer);
    if (!buffer)
        return (NULL);
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    return (line);
}