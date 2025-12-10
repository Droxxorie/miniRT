/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:13:24 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:29:52 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# define M_EPSILON 1e-8
# define M_INFINITY 1.0e30f
# define COLOR_SIZE 8
# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define INV_255 0.00392156862

//* Vector operations */
t_vec3	vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3 vec3_add_scalar(const t_vec3 v, const t_real k);
t_vec3	vec3_scale(const t_vec3 v, const t_real k);
t_vec3	vec3_prod(const t_vec3 u, const t_vec3 v);
t_real	vec3_len_squared(const t_vec3 v);
t_real	vec3_len(const t_vec3 v);
t_vec3	vec3_normalize(const t_vec3 v);

//* Color operations */
t_color	color_add(const t_color c1, const t_color c2);
t_color color_add_scalar(const t_color color, const t_real k);
t_color color_scale(const t_color color, const t_real k);
t_color	color_prod(const t_color c1, const t_color c2);

//* Matrix operations */
#endif