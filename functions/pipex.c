/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:05 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/06 17:00:19 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int *fd, char **argv, char **envp)
{
	int fd_in;

	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd_in);
}

static void	parent_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_RDONLY);
	dup2(fd_out, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd_out);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (perror("Pipe\n"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("Fork\n"), 1);
		if (pid == 0)
			child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp);
	}
	return (0);
}
