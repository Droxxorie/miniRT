/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_texture_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:10:25 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 20:10:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	pattern_rainbow(t_hit_record *record)
{
	t_color	color;
	t_real	t;

	t = record->u * TWO_PI;
	color.r = 0.5 + 0.5 * cos(t + 0.0);
	color.g = 0.5 + 0.5 * cos(t + (TWO_PI / 3.0));
	color.b = 0.5 + 0.5 * cos(t + (2.0 * TWO_PI / 3.0));
	return (color);
}
