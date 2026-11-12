#include "minirt.h"

/* A, C and L lines of the page 11 example */
static void	set_test_lights(t_scene *scene)
{
	scene->ambient.ratio = 0.2;
	scene->ambient.color = rgb(255, 255, 255);
	scene->camera.pos = vec_new(-50, 0, 20);
	scene->camera.dir = vec_new(0, 0, 1);
	scene->camera.fov = 70;
	scene->light.pos = vec_new(-40, 0, 30);
	scene->light.ratio = 0.7;
	scene->light.color = rgb(255, 255, 255);
}

/* Add obj to the scene; on a failed malloc free everything */
static bool	add_or_fail(t_scene *scene, t_object *obj)
{
	if (!obj)
	{
		scene_free(scene);
		return (false);
	}
	scene_add_object(scene, obj);
	return (true);
}

/* pl, sp and cy lines of the page 11 example */
bool	init_test_scene(t_scene *scene)
{
	t_object	*obj;

	scene->objects = NULL;
	set_test_lights(scene);
	obj = object_new(OBJ_PLANE, vec_new(0, 0, 0), vec_new(0, 1, 0),
			rgb(255, 0, 225));
	if (!add_or_fail(scene, obj))
		return (false);
	obj = object_new(OBJ_SPHERE, vec_new(0, 0, 20), vec_new(0, 0, 0),
			rgb(255, 0, 0));
	if (!add_or_fail(scene, obj))
		return (false);
	obj->diameter = 20;
	obj = object_new(OBJ_CYLINDER, vec_new(50, 0, 20.6), vec_new(0, 0, 1),
			rgb(10, 0, 255));
	if (!add_or_fail(scene, obj))
		return (false);
	obj->diameter = 14.2;
	obj->height = 21.42;
	return (true);
}
