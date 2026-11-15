#include "minirt.h"

/* True if path ends with ".rt" and has a name before it */
static bool	has_rt_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	return (len > 3 && ft_strncmp(path + len - 3, ".rt", 4) == 0);
}

/*
** ft_split cuts on one character only: turn tabs and '\r' (Windows
** line endings) into spaces, so every separator is a ' '.
*/
static void	tabs_to_spaces(char *line)
{
	while (*line)
	{
		if (*line == '\t' || *line == '\r')
			*line = ' ';
		line++;
	}
}

/* Split each line into words and give it to parse_line */
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
		tabs_to_spaces(lines[i]);
		words = ft_split(lines[i], ' ');
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
** Fill scene from the .rt file. ft_split skips empty words, so empty
** lines disappear. On error the message is printed, objects are freed.
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
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (parse_error("malloc failed"));
	ok = parse_lines(lines, scene);
	free_split(lines);
	if (!ok)
		scene_free(scene);
	return (ok);
}
