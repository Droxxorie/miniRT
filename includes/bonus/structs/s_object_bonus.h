/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_object_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 16:07:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_OBJECT_BONUS_H
# define S_OBJECT_BONUS_H

# include "s_ray_bonus.h"

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	RECTANGLE,
	DISK,
	TRIANGLE,
	TORUS,
	CONE,
	BOX,
	NONE
}						t_object_type;

typedef struct s_sphere
{
	t_point3			center;
	t_real				radius;
}						t_sphere;

typedef struct s_plane
{
	t_point3			origin;
	t_vec3				normal;
}						t_plane;

typedef enum e_cylinder_element
{
	BODY,
	BOTTOM_CAP,
	TOP_CAP,
	NONE_ELEMENT
}						t_cylinder_element;

typedef struct s_cylinder_hit
{
	t_ray				ray;
	t_real				t;
	t_cylinder_element	type;
	t_quadratic			quadratic_vars;
}						t_cylinder_hit;

typedef struct s_cylinder
{
	t_point3			center;
	t_vec3				axis;
	t_real				radius;
	t_real				height;
}						t_cylinder;

typedef struct s_rectangle
{
	t_point3			center;
	t_vec3				normal;
	t_real				width;
	t_real				height;
}						t_rectangle;

typedef struct s_disk
{
	t_point3			center;
	t_vec3				normal;
	t_real				radius;
}						t_disk;

typedef struct s_triangle_hit
{
	t_vec3				h;
	t_vec3				s;
	t_vec3				q;
	t_real				a;
	t_real				f;
	t_real				u;
	t_real				v;
	t_real				t;
}						t_triangle_hit;

typedef struct s_triangle
{
	t_point3			p1;
	t_point3			p2;
	t_point3			p3;
	t_vec3				edge1;
	t_vec3				edge2;
	t_vec3				normal;
}						t_triangle;

typedef struct s_torus
{
	t_point3			center;
	t_vec3				axis;
	t_real				major_radius;
	t_real				minor_radius;
	t_real				initial_major_radius;
	t_real				initial_minor_radius;
	t_real				major_radius_sq;
	t_real				minor_radius_sq;
	t_real				diff_radius_sq;
}						t_torus;

typedef t_cylinder_hit	t_cone_hit;

typedef struct s_cone
{
	t_point3			base_center;
	t_vec3				axis;
	t_real				height;
	t_real				radius;
}						t_cone;

typedef struct s_box
{
	t_point3			center;
	t_vec3				axis;
	t_real				width;
	t_real				height;
	t_real				depth;
}						t_box;

typedef struct s_object
{
	t_object_type		type;
	t_color				color;
	t_mat4				transform;
	t_mat4				initial_transform;
	t_mat4				inverse;
	t_mat4				transposed_inverse;
	t_aabb				aabb;
	t_bool				visible;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		t_rectangle		rectangle;
		t_disk			disk;
		t_triangle		triangle;
		t_torus			torus;
		t_cone			cone;
		t_box			box;
	} u_data;
	struct s_object		*next;
}						t_object;

#endif