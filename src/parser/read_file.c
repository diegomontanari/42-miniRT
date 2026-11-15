#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "minirt.h"

/* New string = the len chars of content + the n chars of buf */
static char	*append_chunk(char *content, size_t len, char *buf, ssize_t n)
{
	char	*joined;
	size_t	i;

	joined = malloc(len + n + 1);
	if (!joined)
		return (free(content), NULL);
	i = 0;
	while (i < len)
	{
		joined[i] = content[i];
		i++;
	}
	while (i < len + n)
	{
		joined[i] = buf[i - len];
		i++;
	}
	joined[i] = '\0';
	free(content);
	return (joined);
}

/* Read the whole file in chunks of READ_SIZE; NULL on read/malloc error */
static char	*read_all(int fd)
{
	char	buf[READ_SIZE];
	char	*content;
	size_t	len;
	ssize_t	n;

	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	len = 0;
	n = read(fd, buf, READ_SIZE);
	while (n > 0)
	{
		content = append_chunk(content, len, buf, n);
		if (!content)
			return (NULL);
		len += n;
		n = read(fd, buf, READ_SIZE);
	}
	if (n < 0)
		return (free(content), NULL);
	return (content);
}

/* Whole .rt file as one string; prints "Error\n" + reason on failure */
char	*read_file(const char *path)
{
	int		fd;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		perror(path);
		return (NULL);
	}
	content = read_all(fd);
	close(fd);
	if (!content)
		parse_error("cannot read the file");
	return (content);
}
