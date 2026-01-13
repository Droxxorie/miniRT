/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:38:58 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 23:39:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDF_BONUS_H
# define SDF_BONUS_H

# include "../structs/s_scene_bonus.h"

t_bool	ray_march(t_object *object, t_ray *world_ray,
			t_hit_record *record);
t_real	sdf_sphere(t_point3 p);
t_real	sdf_cylinder(t_point3 p);
t_real	sdf_cone(t_point3 p);
t_real	sdf_torus(t_point3 p, t_real major_radius, t_real minor_radius);
t_real	sdf_box(t_point3 p);
t_real	sdf_disk(t_point3 p);
t_real	sdf_rectangle(t_point3 p);
t_real	sdf_triangle(t_point3 p, t_object *object);
// t_real	sdf_menger_sponge(t_point3 p, t_object *object);
t_real	sdf_mandelbulb(t_point3 p, t_object *object);
// t_real	sdf_mandelbox(t_point3 p, t_object *object);

#endif