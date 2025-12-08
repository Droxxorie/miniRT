/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:35:19 by eraad             #+#    #+#             */
/*   Updated: 2025/12/08 14:10:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <vector.h>

typedef t_vec3 t_color;

typedef struct s_material
{
	t_color	diffuse;
}	t_material;

#endif