/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:57:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 23:26:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	vec2_len_squared(const t_vec2 v)
{
	return ((v.x * v.x) + (v.y * v.y));
}

t_real	vec2_len(const t_vec2 v)
{
	return (sqrt(vec2_len_squared(v)));
}

t_real	vec3_len_squared(const t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

t_real	vec3_len(const t_vec3 v)
{
	return (sqrt(vec3_len_squared(v)));
}
