#include "minirt.h"

/* Convert a 0-255 color from the .rt file to a vector in [0, 1] */
t_vec3	rgb(int r, int g, int b)
{
	return (vec_new(r / 255.0, g / 255.0, b / 255.0));
}

/* Allocate a shape; diameter and height are set by the caller */
t_object	*object_new(t_obj_type type, t_vec3 pos, t_vec3 dir, t_vec3 color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->pos = pos;
	obj->dir = dir;
	obj->diameter = 0.0;
	obj->height = 0.0;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

/* Append obj at the end of the list, keeping the file order */
void	scene_add_object(t_scene *scene, t_object *obj)
{
	t_object	*last;

	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	last = scene->objects;
	while (last->next)
		last = last->next;
	last->next = obj;
}

/* Free every shape of the list and leave the scene empty */
void	scene_free(t_scene *scene)
{
	t_object	*next;

	while (scene->objects)
	{
		next = scene->objects->next;
		free(scene->objects);
		scene->objects = next;
	}
}
