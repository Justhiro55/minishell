/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leakdetect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:36:21 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/12 17:44:59 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void leak_detect_init()
// {
//     for (int i = 0; i < N; i++)
//     {
//         mi[i].p = NULL;
//         mi[i].size = 0;
//         mi[i].file = NULL;
//         mi[i].line = 0;
//     }
// }

// void *leak_detelc_malloc(size_t size,  const char *file, unsigned int line)
// {
// 	void *p;

// 	if (!(p = malloc(size)))
// 		return NULL;
// 	if (file != NULL)
// 	{
// 		printf("%s\n", file);
// 		printf("%d\n", line);
// 	}
// 	(void)file;
// 	(void)line;
// 	return p;
// }

// void	*leak_detelc_ft_calloc(size_t i, size_t num, const char *file, unsigned int line)
// {
// 	void	*p;

// 	printf("calloc\n");
// 	if (!(p = malloc(i * num)))
// 		return NULL;
// 	memset(p, 0, i * num);
// 	printf("%p\n", p);
// 	if (file != NULL)
// 	{
// 		printf("%s\n", file);
// 		printf("%d\n", line);
// 	}
// 	return p;
// }

// char	*leak_detelc_strdup(const char *str, const char *file, unsigned int line)
// {
// 	char	*p;

// 	printf("strdup\n");
// 	p = strdup(str);
// 	if (p == NULL)
// 		return NULL;
// 	printf("%p\n", &p);
// 	printf("%s\n", file);
// 	printf("%d\n", line);
// 	return p;
// }
