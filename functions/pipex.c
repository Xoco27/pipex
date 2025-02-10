/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:05 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/10 18:18:40 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_str(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_str(paths);
	return (0);
}

static void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_str(cmd);
		perror("path");
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_str(cmd);
		free(path);
		perror("execve");
		error();
	}
}

static void	child_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in == -1)
	{
		perror("fd");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close(fd[1]);
	close(fd[0]);
	execute(argv[2], envp);
}

static void	parent_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("fd");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(fd[0]);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (perror("Pipe"), 1);
		pid = fork();
		if (pid < 0)
		{
			close(fd[0]);
			close(fd[1]);
			return (perror("Pipe"), 1);
		}
		if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
		close(fd[0]);
		close(fd[1]);
	}
	else
		return (1);
	return (0);
}
