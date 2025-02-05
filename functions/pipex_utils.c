/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:55:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/05 15:23:31 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse(char *temp, char *full_path, char *cmd)
{
	int	k;
	int	l;

	k = 0;
	while (temp[k] != '\0')
	{
		full_path[k] = temp[k];
		k++;
	}
	full_path[k++] = '/';
	l = 0;
	while (cmd[l] != '\0')
		full_path[k++] = cmd[l];
	full_path[k] = '\0';
}

char	*parsing(char *cmd, char *path, int i)
{
	char	*full_path;
	char	temp[512];
	int		j;

	j = 0;
	full_path = malloc(512);
	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			temp[j] = '\0';
			parse(temp, full_path, cmd);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			j = 0;
		}
		else
			temp[j++] = path[i];
		i++;
	}
	temp[j] = '\0';
	parse(temp, full_path, cmd);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}
