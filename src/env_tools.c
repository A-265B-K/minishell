/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:35:52 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/28 17:34:37 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_get(char *str, char **envp)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
		{
			while (envp[i][length] != '\0')
				length++;
			return (ft_substr(envp[i], ft_strlen(str) + 1, length));
		}
		i++;
	}
	return (ft_memcpy(mem_add(1, sizeof(char)), "", 1));
}

int	all_space(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
