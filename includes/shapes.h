/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:40:15 by eraad             #+#    #+#             */
/*   Updated: 2025/12/07 18:21:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <vector.h>
# include <color.h>

typedef enum e_shape_type
{
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_CYLINDER,
	SHAPE_SQUARE,
	SHAPE_TRIANGLE,
	SHAPE_NONE
}	t_shape_type;

typedef struct s_aabb
{
	t_vec3 min;
	t_vec3 max;
	t_vec3 center;
	t_bool used;
}	t_aabb;

typedef struct s_shape
{
	void			*shape;
	t_shape_type	type;
	t_material		material;
	t_aabb			volume;
	t_bool			construct;
	void			*next;
}	t_shape;


//* -------------------- SPHERE -------------------- *//
/*

*/
typedef struct s_sphere_vars
{
	t_real t;
	t_vec3 p;
	t_real y;
	t_real x;
	t_real t1;
	t_real t2;
}	t_sphere_vars;

typedef struct s_sphere
{
	t_vec3	center;
	t_real	radius;
}	t_sphere;

//* -------------------- PLANE -------------------- *//
typedef struct s_plane_vars
{
	t_real plane;
	t_vec3 p;
	t_real t;
}	t_plane_vars;

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	normal;
}	t_plane;

#endif