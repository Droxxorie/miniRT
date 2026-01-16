/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:58:58 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 14:06:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	vec3_abs(const t_vec3 v)
{
	return ((t_vec3){fabs(v.x), fabs(v.y), fabs(v.z)});
}

t_vec2	vec2_abs(const t_vec2 v)
{
	return ((t_vec2){fabs(v.x), fabs(v.y)});
}
