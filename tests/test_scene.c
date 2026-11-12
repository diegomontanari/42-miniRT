#include <stdio.h>
#include "minirt.h"

/* Not part of the project: prints the hardcoded test scene */

static void	print_vec(const char *label, t_vec3 v)
{
	printf("  %-6s (%g, %g, %g)\n", label, v.x, v.y, v.z);
}

int	main(void)
{
	t_scene		scene;
	t_object	*obj;
	const char	*names[3] = {"sphere", "plane", "cylinder"};

	if (!init_test_scene(&scene))
		return (printf("Error\nmalloc failed\n"), 1);
	printf("A ratio %g\n", scene.ambient.ratio);
	printf("C fov %g\n", scene.camera.fov);
	print_vec("pos", scene.camera.pos);
	printf("L ratio %g\n", scene.light.ratio);
	obj = scene.objects;
	while (obj)
	{
		printf("%s d=%g h=%g\n", names[obj->type], obj->diameter,
			obj->height);
		print_vec("pos", obj->pos);
		print_vec("dir", obj->dir);
		print_vec("color", obj->color);
		obj = obj->next;
	}
	scene_free(&scene);
	return (0);
}
