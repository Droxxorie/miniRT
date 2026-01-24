/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:15:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 08:17:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	vec3_sub(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){
		u.x - v.x,
		u.y - v.y,
		u.z - v.z
	});
}

t_color	color_sub(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b
	});
}
