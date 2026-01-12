/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:30:48 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 16:48:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_real	vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_real	color_dot(const t_color c1, const t_color c2)
{
	return ((c1.r * c2.r) + (c1.g * c2.g) + (c1.b * c2.b));
}
