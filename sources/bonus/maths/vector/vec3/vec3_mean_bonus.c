/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mean_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:21:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 11:22:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	vec3_mean(t_vec3 vector)
{
	return ((vector.x + vector.y + vector.z) / 3.0);
}

t_real	color_mean(t_color color)
{
	return ((color.r + color.g + color.b) / 3.0);
}
