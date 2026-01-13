/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acceleration_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:36:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 23:24:52 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCELERATION_BONUS_H
# define ACCELERATION_BONUS_H

# include "structs/s_scene_bonus.h"

//* ========================================================================= */
//*                                AABB                                       */
//* ========================================================================= */
//* Bounding boxes
t_aabb	compute_box_bounds(void);
t_aabb	compute_disk_bounds(void);
t_aabb	compute_cone_bounds(void);
t_aabb	compute_sphere_bounds(void);
t_aabb	compute_cylinder_bounds(void);
t_aabb	compute_rectangle_bounds(void);
t_aabb	compute_torus_bounds(t_object *object);
t_aabb	compute_triangle_bounds(t_object *object);
t_aabb	compute_menger_sponge_bounds(void);
t_aabb	compute_mandelbulb_bounds(void);
t_aabb	compute_mandelbox_bounds(void);

t_aabb	empty_aabb(void);
void	grow_aabb(t_aabb *box, t_point3 p);
void	compute_object_bounds(t_object *obj);
t_aabb	surrounding_box(t_aabb box0, t_aabb box1);
t_bool	hit_aabb(t_aabb *box, t_ray *ray, t_real t_min, t_real t_max);
t_bool	intersect_aabb_values(t_aabb *box, t_ray *ray,
			t_real *t_in, t_real *t_out);

//* ========================================================================= */
//*                                BVH                                        */
//* ========================================================================= */
void	build_bvh(t_scene *scene);
void	destroy_bvh(t_scene *scene);
t_real	get_box_center(t_aabb box, int axis);
void	refresh_bvh(t_scene *scene, t_object *object);
void	sort_objects_axis(t_object **objects, int axis);
t_bool	hit_bvh(t_bvh_node *node, t_ray *ray, t_hit_record *record);

#endif