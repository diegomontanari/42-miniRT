#include <unistd.h>
#include "minirt.h"

/* Print "Error\n" and msg on stderr; returns false to stop the parser */
bool	parse_error(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}

/* Number of strings in a NULL-terminated array */
int	word_count(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

/* True if path ends with ".rt" and has a name before it */
static bool	has_rt_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 3 && ft_strcmp(path + len - 3, ".rt") == 0);
}

/* Split each line into words (\r too: Windows files) for parse_line */
static bool	parse_lines(char **lines, t_scene *scene)
{
	char	**words;
	int		seen;
	int		i;
	bool	ok;

	seen = 0;
	i = 0;
	ok = true;
	while (ok && lines[i])
	{
		words = ft_split(lines[i], " \t\r");
		if (!words)
			return (parse_error("malloc failed"));
		if (words[0])
			ok = parse_line(words, scene, &seen);
		free_split(words);
		i++;
	}
	if (ok && seen != (SEEN_A | SEEN_C | SEEN_L))
		return (parse_error("the scene needs one A, one C and one L"));
	return (ok);
}

/*
** Fill scene from the .rt file. Empty lines disappear in the split.
** On error the message is already printed and the objects are freed.
*/
bool	parse_file(const char *path, t_scene *scene)
{
	char	*content;
	char	**lines;
	bool	ok;

	scene->objects = NULL;
	if (!has_rt_extension(path))
		return (parse_error("the file name must end with .rt"));
	content = read_file(path);
	if (!content)
		return (false);
	lines = ft_split(content, "\n");
	free(content);
	if (!lines)
		return (parse_error("malloc failed"));
	ok = parse_lines(lines, scene);
	free_split(lines);
	if (!ok)
		scene_free(scene);
	return (ok);
}
