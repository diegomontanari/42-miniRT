#include <stdio.h>
#include "minirt.h"

/* Not part of the project: quick check of the vec3 functions */

static int	check(const char *name, t_vec3 got, t_vec3 want)
{
	int	ok;

	ok = fabs(got.x - want.x) < 1e-9 && fabs(got.y - want.y) < 1e-9
		&& fabs(got.z - want.z) < 1e-9;
	printf("%-5s %-28s got (%g, %g, %g)\n", ok ? "OK" : "FAIL", name,
		got.x, got.y, got.z);
	return (!ok);
}

static int	check_d(const char *name, double got, double want)
{
	int	ok;

	ok = fabs(got - want) < 1e-9;
	printf("%-5s %-28s got %g\n", ok ? "OK" : "FAIL", name, got);
	return (!ok);
}

int	main(void)
{
	int	err;

	err = 0;
	err += check("add (1,2,3)+(4,5,6)", vec_add(vec_new(1, 2, 3),
				vec_new(4, 5, 6)), vec_new(5, 7, 9));
	err += check("sub (4,5,6)-(1,2,3)", vec_sub(vec_new(4, 5, 6),
				vec_new(1, 2, 3)), vec_new(3, 3, 3));
	err += check("scale (1,-2,3)*2", vec_scale(vec_new(1, -2, 3), 2),
			vec_new(2, -4, 6));
	err += check_d("dot (1,2,3).(4,5,6)", vec_dot(vec_new(1, 2, 3),
				vec_new(4, 5, 6)), 32);
	err += check_d("dot perpendicular", vec_dot(vec_new(1, 0, 0),
				vec_new(0, 1, 0)), 0);
	err += check("cross x * y", vec_cross(vec_new(1, 0, 0),
				vec_new(0, 1, 0)), vec_new(0, 0, 1));
	err += check("cross y * x", vec_cross(vec_new(0, 1, 0),
				vec_new(1, 0, 0)), vec_new(0, 0, -1));
	err += check_d("len (3,4,0)", vec_len(vec_new(3, 4, 0)), 5);
	err += check("norm (3,4,0)", vec_norm(vec_new(3, 4, 0)),
			vec_new(0.6, 0.8, 0));
	err += check("norm (0,0,0)", vec_norm(vec_new(0, 0, 0)),
			vec_new(0, 0, 0));
	printf("%d test falliti\n", err);
	return (err != 0);
}
