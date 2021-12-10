/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:21:26 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/22 15:57:40 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_open_file(char *file_path, int mode);
static void	ft_execute(char *command, char **envp);

/*	./pipex
**	DESCRIPTION
**	The ./pipex executable redirects commands output to the input of following
**	commands. In the mandatory version, pipex deals with any command available
**	redirecting only one pipe, and truncating existing output files.
**	For the bonus part, it must deal with any number of pipes and also here_doc
**	input, appending the output to any already existing file.  
**	USAGE
**	./pipex file1 cmd1 cmd2 [cmd3 ... cmdN] file2
**	# < file1 cmd1 | cmd2 [ | cmd3 | ... | cmdN ] > file2
**	./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] file 2
**	# cmd1 << LIMITER | cmd2 [ | cmd3 | ... | cmdN ] >> file2
*/

int	main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;
	int	i;

	if (argc != 5)
		error(1, NULL);
	else
	{
		i = ft_start_files(argc, argv, &fdin, &fdout);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		ft_redirect(argv[i++], envp);
		ft_execute(argv[i], envp);
	}
	return (0);
}

/*	ft_start_files()
**	DESCRIPTION
**	The ft_start_files() function directs the opening of each file passed as 
**	parameter, also dealing with the here_doc option of writing on file by 
**	appending.  
**	PARAMETERS
**	#1. Number of parameters passed on executable.
**	#2. Array of parameters passed on executable.
**	#3. Pointer to input file descriptor.
**	#4. Pointer to output file descriptor.
**	RETURN VALUES
**	It returns the index for the first command on argv[]. 
*/

int	ft_start_files(int argc, char **argv, int *fdin, int *fdout)
{
	int	i;

	i = 1;
	*fdin = ft_open_file(argv[i++], IN);
	*fdout = ft_open_file(argv[argc - 1], OUTWRITE);
	return (i);
}

static int	ft_open_file(char *file_path, int mode)
{
	if (mode == IN)
	{
		if (access(file_path, F_OK))
			error(2, file_path);
		return (open(file_path, O_RDONLY));
	}
	else if (mode == OUTWRITE)
		return (open(file_path, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	else
		return (open(file_path, O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

/*	ft_redirect()
**	DESCRIPTION
**	The ft_redirect() function created a pipe and the fork its process in order
**	to switch the input and output for each command passed, and then executes it
**	properly. 
**	PARAMETERS
**	#1. The command to execute.
**	#2. The environment variables list.
**	RETURN VALUES
**	--
*/

void	ft_redirect(char *command, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(3, NULL);
	pid = fork();
	if (pid == -1)
		error(4, NULL);
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(-1, NULL, WNOHANG);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		ft_execute(command, envp);
	}
}

static void	ft_execute(char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		i;

	cmd_args = ft_split_command(command, ' ');
	if (ft_strchr (cmd_args[0], '/'))
		cmd_path = cmd_args[0];
	else
		cmd_path = ft_get_command_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
	free(cmd_path);
	error(5, command);
}
