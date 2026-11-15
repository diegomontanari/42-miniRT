#include <stdio.h>
#include "minirt.h"

/*
** Not part of the project: prints the hardcoded test scene with the same
** print_scene used by ./miniRT, so the two outputs can be compared:
** ./miniRT scenes/subject.rt > a.txt; ./test_scene > b.txt; diff a.txt b.txt
*/

int	main(void)
{
	t_scene	scene;

	if (!init_test_scene(&scene))
		return (printf("Error\nmalloc failed\n"), 1);
	print_scene(&scene);
	scene_free(&scene);
	return (0);
}
