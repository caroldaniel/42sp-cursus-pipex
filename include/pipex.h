/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:21:29 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/22 14:37:34 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define STDIN		0
# define STDOUT		1
# define STDERR		2

enum	e_mode
{
	IN,
	OUTWRITE,
	OUTAPPEND	
};

# define ERR_ARG	"Wrong usage. Invalid number of arguments.\n"
# define ERR_FILE	": invalid file.\n"
# define ERR_PIPE	"Error on initializing pipe.\n"
# define ERR_FORK	"Error on forking.\n"
# define ERR_CMD	": command not found.\n"

// Functions of pipex main flow
int		ft_start_files(int argc, char **argv, int *fdin, int *fdout);
void	ft_redirect(char *command, char **envp);

// Auxiliary functions
char	**ft_split_command(char const *s, char c);
char	*ft_get_command_path(char *command_name, char **envp);
char	*ft_join_path(char *directory, char *command);
int		ft_strichr(const char *s, int c);

// Here_doc function
int		ft_here_doc(char **argv);

// Error management
void	error(int exit_code, char *name);

#endif