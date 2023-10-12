/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:57:49 by emman             #+#    #+#             */
/*   Updated: 2023/10/12 14:37:18 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tabsize(char **src)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (src[i++])
		count++;
	return (count);
}

char	**ft_tabdup(char **src)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	new = ft_calloc(ft_tabsize(src) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
			return (ft_freeall(new));
		i++;
	}
	return (new);
}
