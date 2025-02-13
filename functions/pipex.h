/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/13 16:23:21 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

int		main(int argc, char **argv, char **endv);
char	*parsing(char *cmd, char *path, int i);
void	free_str(char **str);
void	error(int *fd);
char	*find_absolute(char *cmd);
#endif