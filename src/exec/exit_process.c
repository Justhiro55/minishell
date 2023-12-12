/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:19:05 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:38:01 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exit_process(int status)
{
	if (status == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (status == EXIT_FAILURE_FILE)
		perror("File open error");
	else if (status == EXIT_FAILURE_FORK)
		perror("Fork error");
	else if (status == EXIT_FAILURE_MALLOC)
		perror("Malloc error");
	else if (status == EXIT_FAILURE_PIPE)
		perror("Pipe error");
	else if (status == EXIT_FAILURE_DUP)
		perror("Dup Error");
	exit(EXIT_FAILURE);
}
