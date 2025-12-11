/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:35:19 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 14:26:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#include <maths.h>

typedef struct s_color
{
	t_real	r;
	t_real	g;
	t_real	b;
}			t_color;

typedef struct s_material
{
	t_color	diffuse;
}			t_material;

#endif