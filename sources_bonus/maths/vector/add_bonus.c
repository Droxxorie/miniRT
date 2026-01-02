/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:14:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:41:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	vec3_add(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3	vec3_add_scalar(const t_vec3 v, const t_real k)
{
	return ((t_vec3){v.x + k, v.y + k, v.z + k});
}

t_color	color_add(const t_color c1, const t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_color	color_add_scalar(const t_color color, const t_real k)
{
	return ((t_color){color.r + k, color.g + k, color.b + k});
}
