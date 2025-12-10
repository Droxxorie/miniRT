/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:23:10 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 17:23:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	color_scale(const t_color color, const t_real k)
{
	return ((t_color){color.r * k, color.g * k, color.b * k});
}

t_color	color_prod(const t_color c1, const t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}
