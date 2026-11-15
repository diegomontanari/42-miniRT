#include "minirt.h"

/* Max digits in one number: a double stores ~15 exact decimal digits */
#define MAX_DIGITS 15

/* Append the digits at *s to *value (as an integer), counting them */
static void	read_digits(const char **s, double *value, int *count)
{
	while (ft_isdigit(**s))
	{
		*value = *value * 10 + (**s - '0');
		(*count)++;
		(*s)++;
	}
}

/*
** Read one number [+-]digits[.digits] at the start of s.
** "20.6": all digits give 206, one decimal digit, so 206 / 10^1.
** Returns the position just after the number, or NULL if s is not one.
*/
const char	*read_number(const char *s, double *out)
{
	double	sign;
	double	value;
	int		int_digits;
	int		dec_digits;

	sign = 1.0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1.0;
		s++;
	}
	value = 0.0;
	int_digits = 0;
	dec_digits = 0;
	read_digits(&s, &value, &int_digits);
	if (*s == '.')
	{
		s++;
		read_digits(&s, &value, &dec_digits);
	}
	if (int_digits + dec_digits == 0 || int_digits + dec_digits > MAX_DIGITS)
		return (NULL);
	*out = sign * value / pow(10, dec_digits);
	return (s);
}

/* String to double; false unless the whole string is one number */
bool	ft_atof(const char *s, double *out)
{
	s = read_number(s, out);
	return (s && *s == '\0');
}
