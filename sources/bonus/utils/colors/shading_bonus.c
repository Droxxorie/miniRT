/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:51:35 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 13:51:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	apply_shading(t_color color, t_real n)
{
	t_real	inside;
	t_color	contrast_color;
	t_color	gray_color;
	t_real	grey_value;

	inside = ft_smoothstep(14.0, 15.0, n);
	color = color_prod(color, color_add((t_color){0.45, 0.42, 0.40},
				color_scale((t_color){0.55, 0.58, 0.60}, inside)));
	contrast_color.r = color.r * color.r * (3.0 - 2.0 * color.r);
	contrast_color.g = color.g * color.g * (3.0 - 2.0 * color.g);
	contrast_color.b = color.b * color.b * (3.0 - 2.0 * color.b);
	color = color_mix(contrast_color, color, inside);
	grey_value = color_dot(color, (t_color){0.3333, 0.3333, 0.3333});
	gray_color = (t_color){grey_value, grey_value, grey_value};
	return (color_mix(color_mix(color, gray_color, -0.4), color, inside));
}
