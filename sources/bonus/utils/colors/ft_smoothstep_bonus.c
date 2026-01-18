/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smoothstep_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:18:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 13:19:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	ft_smoothstep(t_real edge0, t_real edge1, t_real x)
{
	t_real	t;

	t = ft_clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
	return (t * t * (3.0 - 2.0 * t));
}
