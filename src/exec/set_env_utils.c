/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:22:43 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/23 15:53:01 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_strchr_export(const char *s, int c)
{
	char	tmp;

	tmp = '\0';
	while (*s)
	{
		if (*s == (char)c)
		{
			if (tmp == '-')
				return (1);
		}
		tmp = *s;
		s++;
	}
	if (*s == '\0' && c == '\0')
		return (0);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(n + 1);
	if (!copy)
	{
		return (NULL);
	}
	while (i < n && s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	set_env(t_info *info, char **envp);

void	set_no_env(t_info *info)
{
	char	**envp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	envp = (char **)malloc(sizeof(char *) * 4);
	envp[0] = ft_strjoin("PWD=", cwd);
	envp[1] = ft_strjoin("SHLVL=1", cwd);
	envp[2] = ft_strjoin("_=", cwd);
	envp[3] = NULL;
	set_env(info, envp);
	ft_free_array(envp);
	free(cwd);
}
