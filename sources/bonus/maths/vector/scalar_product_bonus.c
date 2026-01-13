/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_product_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:30:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 23:55:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_real	vec2_dot(const t_vec2 u, const t_vec2 v)
{
	return ((u.x * v.x) + (u.y * v.y));
}

t_real	color_dot(const t_color c1, const t_color c2)
{
	return ((c1.r * c2.r) + (c1.g * c2.g) + (c1.b * c2.b));
}
