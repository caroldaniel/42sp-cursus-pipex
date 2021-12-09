/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:12:21 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/22 14:37:48 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(int exit_code, char *name)
{
	if (exit_code == 1)
		write(STDERR, ERR_ARG, ft_strlen(ERR_ARG));
	else if (exit_code == 2)
	{
		write(STDERR, name, ft_strlen(name));
		write(STDERR, ERR_FILE, ft_strlen(ERR_FILE));
	}
	else if (exit_code == 3)
		write(STDERR, ERR_PIPE, ft_strlen(ERR_PIPE));
	else if (exit_code == 4)
		write(STDERR, ERR_FORK, ft_strlen(ERR_FORK));
	else if (exit_code == 5)
	{
		write(STDERR, name, ft_strlen(name));
		write(STDERR, ERR_CMD, ft_strlen(ERR_CMD));
	}
	exit(exit_code);
}
