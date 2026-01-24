/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:20:56 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 08:24:47 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	vec3_scale(const t_vec3 v, const t_real k)
{
	return ((t_vec3){v.x * k, v.y * k, v.z * k});
}

t_color	color_scale(const t_color color, const t_real k)
{
	return ((t_color){color.r * k, color.g * k, color.b * k});
}

t_color	color_div(const t_color color, const t_real k)
{
	t_real	inv_k;

	inv_k = 1.0 / k;
	return ((t_color){color.r * inv_k, color.g * inv_k, color.b * inv_k});
}

t_vec3	vec3_div(const t_vec3 v, const t_real k)
{
	t_real	inv_k;

	inv_k = 1.0 / k;
	return ((t_vec3){v.x * inv_k, v.y * inv_k, v.z * inv_k});
}
