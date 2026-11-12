#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>

/* 3D vector: used for points, directions and RGB colors (0.0 - 1.0) */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* Ray: every point on it is origin + t * dir (dir normalized) */
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/* Closest hit found so far: distance, point, surface normal, color */
typedef struct s_hit
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}	t_hit;

/* Vector math: vec3_basic.c */
t_vec3	vec_new(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double s);
double	vec_dot(t_vec3 a, t_vec3 b);

/* Vector math: vec3_utils.c */
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_len(t_vec3 v);
t_vec3	vec_norm(t_vec3 v);

#endif
