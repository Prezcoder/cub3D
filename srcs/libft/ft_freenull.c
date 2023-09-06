/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freenull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:30:26 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/18 17:42:04 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Take the address of a char * (&ptr)*/
void	ft_freenull(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}
