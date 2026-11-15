#include <stdio.h>
#include "minirt.h"

/* One labeled vector on its own line */
static void	print_vec(const char *label, t_vec3 v)
{
	printf("  %-6s (%g, %g, %g)\n", label, v.x, v.y, v.z);
}

/* Type, sizes and vectors of one shape */
static void	print_object(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		printf("sp");
	else if (obj->type == OBJ_PLANE)
		printf("pl");
	else
		printf("cy");
	printf(" d=%g h=%g\n", obj->diameter, obj->height);
	print_vec("pos", obj->pos);
	print_vec("dir", obj->dir);
	print_vec("color", obj->color);
}

/* Every field of the scene: compare it with the .rt file you gave */
void	print_scene(t_scene *scene)
{
	t_object	*obj;

	printf("A ratio=%g\n", scene->ambient.ratio);
	print_vec("color", scene->ambient.color);
	printf("C fov=%g\n", scene->camera.fov);
	print_vec("pos", scene->camera.pos);
	print_vec("dir", scene->camera.dir);
	printf("L ratio=%g\n", scene->light.ratio);
	print_vec("pos", scene->light.pos);
	print_vec("color", scene->light.color);
	obj = scene->objects;
	while (obj)
	{
		print_object(obj);
		obj = obj->next;
	}
}
