/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:16:09 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 21:11:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

long	get_time_ms(void)
{
	struct timeval	value;

	if (gettimeofday(&value, NULL) == -1)
		return (-1);
	return (value.tv_sec * 1000 + value.tv_usec / 1000);
}
