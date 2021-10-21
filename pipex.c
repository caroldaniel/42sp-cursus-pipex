/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:21:26 by cado-car          #+#    #+#             */
/*   Updated: 2021/10/21 18:47:53 by cado-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
static void	redirect(char *command, char **envp);
static void	execute(char *command, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;
	int i;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		write(STDERR, ERR_ARG, ft_strlen(ERR_ARG));
	else
	{
		i = ft_start_files(argc, argv, &fdin, &fdout);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		redirect(argv[i++], envp);
		while (i < argc - 2)
			redirect(argv[i++], envp);
		execute(argv[i], envp);
		if (!ft_strncmp(argv[1], "here_doc", 8))
			unlink("here_doc");
	}
	return (0);
}

int	ft_start_files(int argc, char **argv, int *fdin, int *fdout)
{
	int	i;

	i = 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		*fdin = ft_here_doc(fdin, argv, &i);
		*fdout = open_file(argv[argc - 1], OUTAPPEND);		
	}
	else
	{
		*fdin = open_file(argv[i++], IN);
		*fdout = open_file(argv[argc - 1], OUTWRITE);			
	}
	return (i);
}

int	open_file(char *file_path, int mode)
{
	if (mode == IN)
	{
		if (access(file_path, F_OK))
		{
			write(STDERR, file_path, ft_strlen(file_path));
			write(STDERR, ERR_FILE, ft_strlen(ERR_FILE));
			exit(1);
		}
		return (open(file_path, O_RDONLY));
	}
	else if (mode == OUTWRITE)
		return (open(file_path, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	else
		return (open(file_path, O_WRONLY | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

static void	redirect(char *command, char **envp)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		execute(command, envp);
	}
}

static void	execute(char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split_command(command, ' ');
	if (ft_strchr (cmd_args[0], '/'))
		cmd_path = cmd_args[0];
	else
		cmd_path = get_command_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
	write(STDERR, command, ft_strlen(command));
	write(STDERR, ERR_CMD, ft_strlen(ERR_FILE));
	exit(2);
}

