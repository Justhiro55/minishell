/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:48:20 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/06 17:28:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	command_ls(const char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_path);
	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
}
