/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:56:30 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/22 14:36:39 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_write_to_pipe(int *fd, char **argv);

/*	ft_get_command_path()
**	DESCRIPTION
**	Iterates over environment variables to find "PATH=" list, and then iterates
**	over all paths to find the correct executable directory.
**	PARAMETERS
**	#1. The command desired.
**	#2. The environment variables list.
**	RETURN VALUES
**	The correct directory for the executable already concatenated with command. 
**	The command name only if the search fails.
*/

char	*ft_get_command_path(char *command_name, char **envp)
{
	char	*path;
	char	*directory;
	char	*bin;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_strdup(command_name));
	path = &envp[i][5];
	while (path && ft_strichr(path, ':') != -1)
	{
		directory = ft_strndup(path, ft_strichr(path, ':'));
		bin = ft_join_path(directory, command_name);
		free(directory);
		if (access(bin, F_OK | X_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (ft_strdup(command_name));
}

/*	ft_join_path ()
**	DESCRIPTION
**	The ft_join_path() function can be used to concatenate two strings: the 
**	directory path and the command executable, joining them with a '/' char.
**	PARAMETERS
**	#1. The directory path string.
**	#2. The command executable file name.
**	RETURN VALUE
**	The function returns the full, concatenated path to the executable.
**	If there's an error, it returns NULL.
*/

char	*ft_join_path(char *directory, char *command)
{
	char	*full_path;
	int		i;
	int		j;

	full_path = malloc((ft_strlen(directory) + ft_strlen(command) + 2) * \
		sizeof(char));
	if (!full_path)
		return (NULL);
	i = 0;
	j = 0;
	while (directory[j])
		full_path[i++] = directory[j++];
	full_path[i++] = '/';
	j = 0;
	while (command[j])
		full_path[i++] = command[j++];
	full_path[i] = '\0';
	return (full_path);
}

/*	ft_strichr()
**	DESCRIPTION
**	The strichr() function is an adaptation of the ft_strchr located in the 
**	libft library. It locates the first occurrence of c (converted to a 
**	char) in the string pointed to by s. The terminating null character is 
**	considered to be part of the string; therefore if c is `\0', the functions 
**	locate the terminating `\0'.
**	PARAMETERS
**	#1. The string in which to checks for the occurence of c.
**	#2. The character to check the occurence of.
**	RETURN VALUES
**	The function strchr() returns the index position of the first occurence of c
**	or -1 if there's no occurence at all
*/

int	ft_strichr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (ch == '\0')
		return (i);
	return (-1);
}

/*	ft_here_doc()
**	DESCRIPTION
**	The ft_here_doc() function deals with the heredoc case on the pipex 
**	executable. It creates a pipe and takes all text from STDIN until a limiter
**	is written. 
**	PARAMETERS
**	#1. The argument list.
**	RETURN VALUES
**	The file descriptor for STDIN upon completion.
*/

int	ft_here_doc(char **argv)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error(3, NULL);
	pid = fork();
	if (pid == -1)
		error(4, NULL);
	if (pid)
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		ft_write_to_pipe(&fd[1], argv);
	}
	return (STDIN);
}

static void	ft_write_to_pipe(int *fd, char **argv)
{
	char	*line;
	char	*limiter;

	limiter = argv[2];
	write(STDIN, "pipex: here_doc> ", 17);
	line = get_next_line(STDIN);
	while (line)
	{
		if (!ft_strncmp(limiter, line, ft_strlen(limiter)))
			break ;
		write(*fd, line, ft_strlen(line));
		free(line);
		write(STDIN, "pipex: here_doc> ", 17);
		line = get_next_line(STDIN);
	}
	free(line);
	close(*fd);
	exit(6);
}
