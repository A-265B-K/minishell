/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:35:52 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/02 13:36:14 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(char *str, char *envp[])
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