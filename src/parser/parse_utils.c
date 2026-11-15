#include "minirt.h"

/* Print "Error\n" and msg on stderr; returns false to stop the parser */
bool	parse_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (false);
}

/* Number of strings in a NULL-terminated array */
int	word_count(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

/* Free a NULL-terminated array of strings (from ft_split) and the array */
void	free_split(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}
