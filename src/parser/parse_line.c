#include "minirt.h"

/* Set bit in *seen; error if that capital element was already found */
static bool	mark_once(int *seen, int bit)
{
	if (*seen & bit)
		return (parse_error("A, C and L can be declared only once"));
	*seen |= bit;
	return (true);
}

/* Choose the parser from the first word of the line */
bool	parse_line(char **words, t_scene *scene, int *seen)
{
	if (ft_strcmp(words[0], "A") == 0)
		return (mark_once(seen, SEEN_A) && parse_ambient(words, scene));
	if (ft_strcmp(words[0], "C") == 0)
		return (mark_once(seen, SEEN_C) && parse_camera(words, scene));
	if (ft_strcmp(words[0], "L") == 0)
		return (mark_once(seen, SEEN_L) && parse_light(words, scene));
	if (ft_strcmp(words[0], "sp") == 0)
		return (parse_sphere(words, scene));
	if (ft_strcmp(words[0], "pl") == 0)
		return (parse_plane(words, scene));
	if (ft_strcmp(words[0], "cy") == 0)
		return (parse_cylinder(words, scene));
	return (parse_error("unknown element: use A, C, L, sp, pl or cy"));
}
