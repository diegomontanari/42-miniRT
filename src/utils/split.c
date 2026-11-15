#include "minirt.h"

/* How many words: runs of non-separator characters */
static size_t	count_words(const char *s, const char *seps)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_sep(*s, seps))
			s++;
		if (*s)
			count++;
		while (*s && !is_sep(*s, seps))
			s++;
	}
	return (count);
}

/* Copy the first len characters of s into a new string */
static char	*word_dup(const char *s, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

/* Free a NULL-terminated array of strings and the array itself */
void	free_split(char **words)
{
	size_t	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

/*
** Cut s into words at any char of seps; empty words are skipped,
** so "a  b\n\nc" gives "a", "b", "c". The array ends with NULL.
*/
char	**ft_split(const char *s, const char *seps)
{
	char	**words;
	size_t	i;
	size_t	len;

	words = malloc(sizeof(char *) * (count_words(s, seps) + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_sep(*s, seps))
			s++;
		if (!*s)
			break ;
		len = 0;
		while (s[len] && !is_sep(s[len], seps))
			len++;
		words[i] = word_dup(s, len);
		if (!words[i])
			return (free_split(words), NULL);
		s += len;
		i++;
	}
	words[i] = NULL;
	return (words);
}
