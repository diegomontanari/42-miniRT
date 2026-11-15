#include "minirt.h"

/*
** Side of a finite cylinder (the two caps come in a later step).
** Idea: look at the scene from the top of the axis. The cylinder becomes
** a circle of radius r and the ray a 2D line: remove from every vector
** its part along the axis, then solve |xp + t * dp|^2 = r^2, that is
** (dp.dp) t^2 + 2 (dp.xp) t + (xp.xp - r^2) = 0.
** The axis (obj->dir) must be normalized: the parser does it.
*/

/* v without its component along axis: what is left is perpendicular */
static t_vec3	remove_axis(t_vec3 v, t_vec3 axis)
{
	return (vec_sub(v, vec_scale(axis, vec_dot(v, axis))));
}

/*
** Roots of a t^2 + b t + c = 0 with t[0] <= t[1]; false if none.
** a == 0 only for a ray exactly parallel to the axis: not EPSILON,
** a ray just slightly tilted has a tiny a but still hits the side.
*/
static bool	solve_quadratic(double a, double b, double c, double t[2])
{
	double	disc;

	if (a == 0.0)
		return (false);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	t[0] = (-b - sqrt(disc)) / (2 * a);
	t[1] = (-b + sqrt(disc)) / (2 * a);
	return (true);
}

/*
** Keep t only if it is a closer hit (contract) and the point is within
** the height: m = distance from the center along the axis, |m| <= h/2.
** Normal: from the axis point at height m to the hit point, length 1.
*/
static bool	try_side_hit(t_ray ray, t_object *obj, double t, t_hit *hit)
{
	t_vec3	point;
	double	m;

	if (t <= EPSILON || t >= hit->t)
		return (false);
	point = vec_add(ray.origin, vec_scale(ray.dir, t));
	m = vec_dot(vec_sub(point, obj->pos), obj->dir);
	if (fabs(m) > obj->height / 2)
		return (false);
	hit->t = t;
	hit->point = point;
	hit->normal = vec_norm(vec_sub(point,
				vec_add(obj->pos, vec_scale(obj->dir, m))));
	hit->color = obj->color;
	return (true);
}

/*
** a = 0 means the ray is parallel to the axis: it can't touch the side.
** Try the nearer root first; the farther one is the inside wall, seen
** through an open end or when the ray starts inside the cylinder.
*/
bool	hit_cylinder(t_ray ray, t_object *obj, t_hit *hit)
{
	t_vec3	dp;
	t_vec3	xp;
	double	r;
	double	t[2];

	r = obj->diameter / 2;
	dp = remove_axis(ray.dir, obj->dir);
	xp = remove_axis(vec_sub(ray.origin, obj->pos), obj->dir);
	if (!solve_quadratic(vec_dot(dp, dp), 2 * vec_dot(dp, xp),
			vec_dot(xp, xp) - r * r, t))
		return (false);
	if (try_side_hit(ray, obj, t[0], hit))
		return (true);
	return (try_side_hit(ray, obj, t[1], hit));
}
