/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:21:29 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/21 18:22:13 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

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
# define ERR_CMD	": invalid command.\n"

int		ft_start_files(int argc, char **argv, int *fdin, int *fdout);
int		open_file(char *file_path, int mode);
char	*ft_join_path (char *directory, char *command);
int		ft_strichr(const char *s, int c);
char	**ft_split_command(char const *s, char c);
int		ft_here_doc(int *fdin, char **argv, int *i);
char	*get_command_path(char *command_name, char **envp);

#endif