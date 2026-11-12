#include "minirt.h"

t_vec3	vec_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (vec_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_scale(t_vec3 v, double s)
{
	return (vec_new(v.x * s, v.y * s, v.z * s));
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
