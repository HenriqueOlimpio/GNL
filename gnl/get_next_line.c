#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "get_next_line.h"

static void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

static int	find_line(char *buf, char **line )
{
	int		i;
	int		j;
	int		flag_line;
	char	*find_line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag_line = 0;
	if (buf[i] == '\n')
		flag_line= 1;
	find_line = ft_calloc(i + flag_line + 1, 1);
	if (find_line == NULL)
		return (-1);
	while (j < i + flag_line)
	{
		find_line[j] = buf[j];
		j++;
	}
	*line = ft_strjoin(*line, find_line);
	if (line == NULL)
		return (-1);
	ft_strcpy(buf, &buf[i + flag_line]);
	return (flag_line);
}

static char	*free_line(char **line)
{
	if (*line != NULL)
		free(*line);
		return(NULL);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char		*line;
	int			count_byte;
	int			flag_line;

	line = NULL;
	flag_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL)
	while (flag_line == 0)
	{
		flag_line = find_line(buf, &line);
		if (flag_line == -1)
			return (free_line(&line));
		if (flag_line == 0)
		{
			count_byte = read(fd, buf, BUFFER_SIZE);
			if (count_byte == 0 && *line)
				flag_line = 1;
			else if (count_byte <= 0)
				return(free_line(&line));
				buf[count_byte] = '\0'
		}
	}
	return (line);
}

int main()
{
	int	fd;
	char *str;
	size_t	bytes;
	bytes = BUFFER_SIZE;
	fd = open("test.txt", O_RDONLY);
	if(fd < 0)
		return (1);
	str = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));
	str[BUFFER_SIZE] = '\0';
	while(bytes == BUFFER_SIZE)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		
		printf("%s", str);
	}
}
