/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:59:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:41:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	vec3_normalize(const t_vec3 v)
{
	t_real	len_sq;
	t_real	len_inv;

	len_sq = vec3_len_squared(v);
	if (len_sq == 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	len_inv = 1.0 / sqrt(len_sq);
	return (vec3_scale(v, len_inv));
}
