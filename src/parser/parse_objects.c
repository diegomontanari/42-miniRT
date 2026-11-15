#include "minirt.h"

/* Copy the parsed fields of o into a new shape at the end of the list */
static bool	add_parsed(t_scene *scene, t_object *o)
{
	t_object	*obj;

	obj = object_new(o->type, o->pos, o->dir, o->color);
	if (!obj)
		return (parse_error("malloc failed"));
	obj->diameter = o->diameter;
	obj->height = o->height;
	scene_add_object(scene, obj);
	return (true);
}

/* sp x,y,z diameter R,G,B */
bool	parse_sphere(char **w, t_scene *scene)
{
	t_object	o;

	if (word_count(w) != 4)
		return (parse_error("sp: expected 'sp x,y,z diameter R,G,B'"));
	o.type = OBJ_SPHERE;
	o.dir = vec_new(0, 0, 0);
	o.height = 0.0;
	if (!parse_vec3(w[1], &o.pos))
		return (parse_error("sp: center must be x,y,z"));
	if (!parse_number(w[2], 0.0, INFINITY, &o.diameter) || o.diameter == 0)
		return (parse_error("sp: diameter must be a number > 0"));
	if (!parse_color(w[3], &o.color))
		return (parse_error("sp: color must be R,G,B in [0, 255]"));
	return (add_parsed(scene, &o));
}

/* pl x,y,z nx,ny,nz R,G,B */
bool	parse_plane(char **w, t_scene *scene)
{
	t_object	o;

	if (word_count(w) != 4)
		return (parse_error("pl: expected 'pl x,y,z nx,ny,nz R,G,B'"));
	o.type = OBJ_PLANE;
	o.diameter = 0.0;
	o.height = 0.0;
	if (!parse_vec3(w[1], &o.pos))
		return (parse_error("pl: point must be x,y,z"));
	if (!parse_dir(w[2], &o.dir))
		return (parse_error("pl: normal must be x,y,z in [-1, 1]"));
	if (!parse_color(w[3], &o.color))
		return (parse_error("pl: color must be R,G,B in [0, 255]"));
	return (add_parsed(scene, &o));
}

/* cy x,y,z ax,ay,az diameter height R,G,B */
bool	parse_cylinder(char **w, t_scene *scene)
{
	t_object	o;

	if (word_count(w) != 6)
		return (parse_error("cy: expected 'cy x,y,z ax,ay,az d h R,G,B'"));
	o.type = OBJ_CYLINDER;
	if (!parse_vec3(w[1], &o.pos))
		return (parse_error("cy: center must be x,y,z"));
	if (!parse_dir(w[2], &o.dir))
		return (parse_error("cy: axis must be x,y,z in [-1, 1]"));
	if (!parse_number(w[3], 0.0, INFINITY, &o.diameter) || o.diameter == 0)
		return (parse_error("cy: diameter must be a number > 0"));
	if (!parse_number(w[4], 0.0, INFINITY, &o.height) || o.height == 0)
		return (parse_error("cy: height must be a number > 0"));
	if (!parse_color(w[5], &o.color))
		return (parse_error("cy: color must be R,G,B in [0, 255]"));
	return (add_parsed(scene, &o));
}
