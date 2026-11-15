#include "minirt.h"

/* For now: read the .rt file, print what was understood, free it */
int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		parse_error("usage: ./miniRT scene.rt");
		return (1);
	}
	if (!parse_file(argv[1], &scene))
		return (1);
	print_scene(&scene);
	scene_free(&scene);
	return (0);
}
