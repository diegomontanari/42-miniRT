#include "minirt.h"

/* Vector perpendicular to both a and b (right-hand rule) */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec_new(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

/* Length of the vector: sqrt(v . v) */
double	vec_len(t_vec3 v)
{
	return (sqrt(vec_dot(v, v)));
}

/* Same direction, length 1. A zero vector is returned unchanged */
t_vec3	vec_norm(t_vec3 v)
{
	double	len;

	len = vec_len(v);
	if (len == 0.0)
		return (v);
	return (vec_scale(v, 1.0 / len));
}
