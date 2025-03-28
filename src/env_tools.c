/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:35:52 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/27 21:18:12 by marvin           ###   ########.fr       */
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
