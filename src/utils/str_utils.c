#include "minirt.h"

/* Number of characters before the final '\0' */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/* 0 if a and b are equal, otherwise the difference of the first mismatch */
int	ft_strcmp(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

/* True if c is one of the separator characters (never true for '\0') */
bool	is_sep(char c, const char *seps)
{
	while (*seps)
	{
		if (c == *seps)
			return (true);
		seps++;
	}
	return (false);
}
