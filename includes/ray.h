/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:37:26 by eraad             #+#    #+#             */
/*   Updated: 2025/12/07 16:38:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <vector.h>

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	min;
	t_vec3	max;
}	t_ray;

#endif