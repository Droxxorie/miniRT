/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_len_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:16:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 20:17:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	vec4_len_squared(t_vec4 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

t_real	vec4_len(t_vec4 v)
{
	return (sqrtf(vec4_len_squared(v)));
}
