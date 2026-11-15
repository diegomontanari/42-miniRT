#include "minirt.h"

/* Read "x,y,z" into v: three numbers, two commas, nothing else */
static bool	read_three(const char *s, double v[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		s = read_number(s, &v[i]);
		if (!s)
			return (false);
		if (i < 2 && *s != ',')
			return (false);
		if (i < 2)
			s++;
		i++;
	}
	return (*s == '\0');
}

/* One number with min <= value <= max (ratio, FOV, size) */
bool	parse_number(const char *s, double min, double max, double *out)
{
	double	value;

	if (!ft_atof(s, &value) || value < min || value > max)
		return (false);
	*out = value;
	return (true);
}

/* A point "x,y,z", any values */
bool	parse_vec3(const char *s, t_vec3 *out)
{
	double	v[3];

	if (!read_three(s, v))
		return (false);
	*out = vec_new(v[0], v[1], v[2]);
	return (true);
}

/* A direction: each value in [-1, 1], not all 0; stored normalized */
bool	parse_dir(const char *s, t_vec3 *out)
{
	double	v[3];
	int		i;

	if (!read_three(s, v))
		return (false);
	i = 0;
	while (i < 3)
	{
		if (v[i] < -1.0 || v[i] > 1.0)
			return (false);
		i++;
	}
	if (v[0] == 0.0 && v[1] == 0.0 && v[2] == 0.0)
		return (false);
	*out = vec_norm(vec_new(v[0], v[1], v[2]));
	return (true);
}

/* A color "R,G,B": whole numbers in [0, 255], stored with rgb() */
bool	parse_color(const char *s, t_vec3 *out)
{
	double	c[3];
	int		i;

	if (!read_three(s, c))
		return (false);
	i = 0;
	while (i < 3)
	{
		if (c[i] < 0 || c[i] > 255 || c[i] != (int)c[i])
			return (false);
		i++;
	}
	*out = rgb(c[0], c[1], c[2]);
	return (true);
}
