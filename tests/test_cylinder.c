#include <stdio.h>
#include "minirt.h"

/*
** Not part of the project: checks hit_cylinder on simple cases.
** Cylinder of the tests: center (0,0,0), axis y, diameter 2, height 4,
** so the side is x^2 + z^2 = 1 for -2 <= y <= 2.
*/

static t_object	g_cy = {OBJ_CYLINDER, {0, 0, 0}, {0, 1, 0}, 2, 4,
	{1, 0, 0}, NULL};

/* Shoot one ray; want_t < 0 means "no hit expected" */
static int	check(const char *name, t_ray ray, double start_t, double want_t)
{
	t_hit	hit;
	bool	got;
	int		ok;

	hit.t = start_t;
	got = hit_cylinder(ray, &g_cy, &hit);
	if (want_t < 0)
		ok = !got;
	else
		ok = got && fabs(hit.t - want_t) < 1e-6;
	printf("%-5s %-34s hit=%d t=%g", ok ? "OK" : "FAIL", name, got, hit.t);
	if (got)
		printf(" normal (%g, %g, %g)", hit.normal.x, hit.normal.y,
			hit.normal.z);
	printf("\n");
	return (!ok);
}

static t_ray	ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	r;

	r.origin = origin;
	r.dir = vec_norm(dir);
	return (r);
}

static int	tilted_test(void)
{
	t_object	saved;
	int			err;

	saved = g_cy;
	g_cy.dir = vec_norm(vec_new(1, 1, 0));
	err = check("tilted axis (1,1,0)", ray(vec_new(0.5, 0, -5),
				vec_new(0, 0, 1)), INFINITY, 5 - sqrt(0.875));
	g_cy = saved;
	return (err);
}

int	main(void)
{
	int	err;

	err = 0;
	err += check("front, toward center", ray(vec_new(0, 0, -5),
				vec_new(0, 0, 1)), INFINITY, 4);
	err += check("front, off center x=0.6", ray(vec_new(0.6, 0, -5),
				vec_new(0, 0, 1)), INFINITY, 5 - 0.8);
	err += check("miss beside", ray(vec_new(5, 0, -5),
				vec_new(0, 0, 1)), INFINITY, -1);
	err += check("miss above (y=3 > h/2)", ray(vec_new(0, 3, -5),
				vec_new(0, 0, 1)), INFINITY, -1);
	err += check("parallel to axis", ray(vec_new(0, -10, 0),
				vec_new(0, 1, 0)), INFINITY, -1);
	err += check("from inside, inner wall", ray(vec_new(0, 0, 0),
				vec_new(1, 0, 0)), INFINITY, 1);
	err += check("behind the ray", ray(vec_new(0, 0, 5),
				vec_new(0, 0, 1)), INFINITY, -1);
	err += check("closer hit already found", ray(vec_new(0, 0, -5),
				vec_new(0, 0, 1)), 2, -1);
	err += check("open top, sees inner wall", ray(vec_new(0, 3, -1.5),
				vec_new(0, -1, 1)), INFINITY, sqrt(2) * 2.5);
	err += tilted_test();
	printf("%d test falliti\n", err);
	return (err != 0);
}
