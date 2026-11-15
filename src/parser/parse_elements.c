#include "minirt.h"

/* A ratio R,G,B */
bool	parse_ambient(char **w, t_scene *scene)
{
	if (word_count(w) != 3)
		return (parse_error("A: expected 'A ratio R,G,B'"));
	if (!parse_number(w[1], 0.0, 1.0, &scene->ambient.ratio))
		return (parse_error("A: ratio must be in [0, 1]"));
	if (!parse_color(w[2], &scene->ambient.color))
		return (parse_error("A: color must be R,G,B in [0, 255]"));
	return (true);
}

/* C x,y,z dx,dy,dz fov */
bool	parse_camera(char **w, t_scene *scene)
{
	if (word_count(w) != 4)
		return (parse_error("C: expected 'C x,y,z dx,dy,dz fov'"));
	if (!parse_vec3(w[1], &scene->camera.pos))
		return (parse_error("C: position must be x,y,z"));
	if (!parse_dir(w[2], &scene->camera.dir))
		return (parse_error("C: direction must be x,y,z in [-1, 1]"));
	if (!parse_number(w[3], 0.0, 180.0, &scene->camera.fov))
		return (parse_error("C: fov must be in [0, 180]"));
	return (true);
}

/* L x,y,z ratio [R,G,B]: the color is unused in mandatory, white if absent */
bool	parse_light(char **w, t_scene *scene)
{
	if (word_count(w) != 3 && word_count(w) != 4)
		return (parse_error("L: expected 'L x,y,z ratio R,G,B'"));
	if (!parse_vec3(w[1], &scene->light.pos))
		return (parse_error("L: position must be x,y,z"));
	if (!parse_number(w[2], 0.0, 1.0, &scene->light.ratio))
		return (parse_error("L: ratio must be in [0, 1]"));
	scene->light.color = rgb(255, 255, 255);
	if (w[3] && !parse_color(w[3], &scene->light.color))
		return (parse_error("L: color must be R,G,B in [0, 255]"));
	return (true);
}
