/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:35:19 by eraad             #+#    #+#             */
/*   Updated: 2025/12/07 16:36:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <vector.h>

typedef t_vec3 t_rgb;

typedef struct s_material
{
	t_rgb	diffuse;
}	t_material;

#endif