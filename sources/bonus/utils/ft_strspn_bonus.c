/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:45:09 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 15:50:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// size_t	ft_strcspn(const char *str, const char *reject)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_strchr(reject, str[i]))
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(accept, str[i]) == NULL)
			return (i);
		i++;
	}
	return (i);
}
