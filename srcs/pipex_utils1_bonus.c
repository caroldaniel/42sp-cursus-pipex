/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:39:26 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/22 14:25:16 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void		ft_createsplit(char **result, char const *s, char c);
static size_t	ft_addpart(char **res, const char *prev, size_t size, char c);
static size_t	ft_split_command_count(const char *s, char c);
static int		ft_delimiter_within(const char *s, int pos);

/*	ft_split_command()
**	DESCRIPTION
**	Allocates (with malloc(3)) and returns an array of strings obtained by 
**	splitting ’s’ using the character ’c’ as a delimiter. The array must be
**	ended by a NULL pointer. Delimiters between quotation marks are not used, 
**	and the quotation marks are not printed to the final splitted string. 
**	PARAMETERS
**	#1. The string to be split.
**	#2. The delimiter character.
**	RETURN VALUES
**	The array of new strings resulting from the split. 
**	NULL if the allocation fails.
*/

char	**ft_split_command(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((ft_split_command_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	ft_createsplit(res, s, c);
	return (res);
}

static void	ft_createsplit(char **result, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	prev;
	size_t	next;

	i = 0;
	j = 0;
	prev = i;
	next = i;
	while (1)
	{
		if ((s[i] == c || s[i] == '\0') && !ft_delimiter_within(s, i))
			next = i;
		size = next - prev;
		if (size > 1 || (size == 1 && s[i - 1] != c))
			j += ft_addpart(&result[j], &s[prev], size, c);
		if (s[i] == '\0')
			break ;
		prev = next;
		i++;
	}
	result[j] = NULL;
}

static size_t	ft_addpart(char **res, const char *prev, size_t size, char c)
{
	if (*prev == c)
	{
		prev++;
		size--;
	}
	if ((*prev == 34 || *prev == 39) && (*(prev + size - 1)) == *prev)
	{
		prev++;
		size -= 2;
	}
	*res = (char *)malloc((size + 1) * sizeof(char));
	ft_strlcpy(*res, prev, size + 1);
	return (1);
}

static size_t	ft_split_command_count(const char *s, char c)
{
	size_t	i;
	size_t	prev;
	size_t	next;
	size_t	size;
	size_t	counter;

	i = 0;
	prev = i;
	next = i;
	counter = 0;
	while (1)
	{
		if ((s[i] == c || s[i] == '\0') && !ft_delimiter_within(s, i))
			next = i;
		size = next - prev;
		if (size > 1 || (size == 1 && s[i - 1] != c))
			counter++;
		if (s[i] == '\0')
			break ;
		prev = next;
		i++;
	}
	return (counter);
}

static int	ft_delimiter_within(const char *s, int pos)
{
	int		i;
	int		before;
	int		after;

	i = 0;
	before = -1;
	after = -1;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && before == -1)
			before = i;
		else if (s[i] == s[before] && after == -1)
		{
			after = i;
			if (pos > before && pos < after)
				return (1);
			before = -1;
			after = -1;
		}
		i++;
	}
	return (0);
}
