/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:18:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 13:19:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	ft_mix(t_real x, t_real y, t_real a)
{
	return (x * (1.0 - a) + y * a);
}

t_color	color_mix(t_color c1, t_color c2, t_real a)
{
	t_color	result;

	result.r = ft_mix(c1.r, c2.r, a);
	result.g = ft_mix(c1.g, c2.g, a);
	result.b = ft_mix(c1.b, c2.b, a);
	return (result);
}
