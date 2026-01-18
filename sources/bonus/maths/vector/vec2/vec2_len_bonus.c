/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_len_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:08:36 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 20:08:41 by eraad            ###   ########.fr       */
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
