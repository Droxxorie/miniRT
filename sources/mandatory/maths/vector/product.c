/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:20:56 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 16:47:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	vec3_scale(const t_vec3 v, const t_real k)
{
	return ((t_vec3){v.x * k, v.y * k, v.z * k});
}

t_vec3	vec3_prod(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x * v.x, u.y * v.y, u.z * v.z});
}

t_color	color_scale(const t_color color, const t_real k)
{
	return ((t_color){color.r * k, color.g * k, color.b * k});
}

t_color	color_prod(const t_color c1, const t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}
