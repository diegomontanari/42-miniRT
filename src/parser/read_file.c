#include <fcntl.h>
#include <stdio.h>
#include "minirt.h"

/* Read the whole file, READ_SIZE bytes at a time, joining the chunks */
static char	*read_all(int fd)
{
	char	buf[READ_SIZE + 1];
	char	*content;
	char	*joined;
	ssize_t	n;

	content = ft_strdup("");
	n = read(fd, buf, READ_SIZE);
	while (content && n > 0)
	{
		buf[n] = '\0';
		joined = ft_strjoin(content, buf);
		free(content);
		content = joined;
		n = read(fd, buf, READ_SIZE);
	}
	if (n < 0)
	{
		free(content);
		return (NULL);
	}
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
		ft_putstr_fd("Error\n", 2);
		perror(path);
		return (NULL);
	}
	content = read_all(fd);
	close(fd);
	if (!content)
		parse_error("cannot read the file");
	return (content);
}
