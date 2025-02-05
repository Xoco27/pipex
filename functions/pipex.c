/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:05 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/05 15:25:11 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	// data->in_fd = argv[1];
	// data->out_fd = argv[4];
	argc = 2;
	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
	printf("%s\n", data->cmd1[0]);
	printf("%s\n", data->cmd2[0]);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
	{
		fprintf(stderr, "pas de path\n");
    	exit(EXIT_FAILURE);
	}
	i = 0;
	data->cmd1_path = parsing(data->cmd1[0], path, i);
	i = 0;
	data->cmd2_path = parsing(data->cmd2[0], path, i);
	if (!data->cmd1_path || !data->cmd2_path)
	{
		fprintf(stderr, "Erreur: parsing a échoué\n");
    	exit(EXIT_FAILURE);
	}
	printf("%s\n", data->cmd1_path);
	printf("%s\n", data->cmd2_path);
}

// static void	child_process(int f1, t_data *data)
// {
// 	dup2(f1, STDIN_FILENO);
// 	dup2(fd[1], STDIN_FILENO);
// 	close(fd[0]);
// 	close(f1);
// 	exit(EXIT_FAILURE);
// }

// static void	parent_process(int f2, t_data *data)
// {
// 	int	status;

// 	waitpid(-1, &status, 0);
// 	dup2(f2, fd[1]);
// 	dup2(fd[0], fd[1]);
// 	close(fd[1]);
// 	close(f2);
// 	exit(EXIT_FAILURE);
// }

// static void	pipex(int f1, int f2, t_data *data)
// {
// 	int		fd[2];
// 	pid_t	parent;

// 	pipe(fd);
// 	parent = fork();
// 	if (parent < 0)
// 		return (perror("Fork :"));
// 	if (parent == 0)
// 		child_process(f1, data);
// 	else
// 		parent_process(f2, data);
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(data));
	if (argc != 5)
		return (0);
	init_data(argc, argv, envp, data);
	// pipex(argv[1], argv[4], data);
	return (0);
}
