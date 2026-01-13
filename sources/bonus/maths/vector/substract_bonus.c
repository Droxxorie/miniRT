/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:32:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 15:01:06 by eraad            ###   ########.fr       */
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

t_vec2	vec2_sub(const t_vec2 u, const t_vec2 v)
{
	return ((t_vec2){
		u.x - v.x,
		u.y - v.y
	});
}
