/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 20:24:40 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/20 20:33:37 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	LIBRARY
*	#include <string.h>
*	DESCRIPTION
*	The strndup() function copies at most n characters from the string s1 always 
*	NUL terminating the copied string.
*	PARAMETERS
*	#1. The string to duplicate.
*	#2. The number of characters to copy over.
*	RETURN VALUES
*	The strdup() function returns thE pointer to the copy of s1.
*/

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;

	ptr = malloc((n + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, n);
	ptr[n] = '\0';
	return (ptr);
}
