/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:32:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 14:27:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <maths.h>
# include <color.h>

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	SQUARE,
	TRIANGLE,
	NONE
}	t_object_type;

typedef struct s_aabb
{
	t_point3	min;
	t_point3	max;
	t_point3	center;
	t_bool		used;
}	t_aabb;

typedef struct s_object
{
	t_object_type	type;
	t_color			color;
	// t_material		material;
	// t_aabb			volume;
	// t_bool			construct;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		// t_square			square;
		// t_triangle		triangle;
	}	data;
	struct s_object	*next;
}	t_object;

//* -------------------- SPHERE -------------------- *//
/*
Equation: Geometric Intersection
||P - C||^2 = r^2
Method: We project the sphere's center onto the ray to form a right triangle.
Then we use Pythagoras to find the intersection distance.
* t_proj: Projected length of Vector(RayOrigin -> Center) onto RayDir
* p_proj: The point on the ray closest to the sphere center
* d_ortho: Orthogonal distance (height) from Ray to Center
* d_chord: Half-length of the chord (segment inside the sphere)
* t0: First intersection distance (Entry)
* t1: Second intersection distance (Exit)
*/
typedef struct s_sphere_vars
{
	t_real		t_proj;
	t_point3	p_proj;
	t_real		d_ortho;
	t_real		d_chord;
	t_real		t0;
	t_real		t1;
}	t_sphere_vars;

typedef struct s_sphere
{
	t_point3	center;
	t_real		radius;
}	t_sphere;

//* -------------------- PLANE -------------------- *//
/*
Equation: Point-Normal Form
(P - P0) . N = 0
t = ((P0 - O) . N) / (D . N)
Method: Simple substitution of the ray equation into the plane equation.
* denom: Denominator (RayDir . PlaneNormal). Checks if parallel.
* vec_diff: Vector from RayOrigin to PlaneOrigin
* dist: Resulting distance t
*/
typedef struct s_plane_vars
{
	t_real	denom;
	t_vec3	vec_diff;
	t_real	dist;
}	t_plane_vars;

typedef struct s_plane
{
	t_point3	origin;
	t_vec3		normal;
}	t_plane;

// //* -------------------- SQUARE -------------------- *//
// /*
// Equation: Plane Intersection + Boundary Check
// 1. Solve Plane Intersection
// 2. Project intersection point P onto local axes (U, V)
// | (P - C) . U | <= size/2  AND  | (P - C) . V | <= size/2
// * denom: RayDir . Normal
// * vec_diff: Vector RayOrigin -> SquareCenter
// * dist: Distance t
// * impact_point: Point P in world space
// * vec_center_hit: Vector SquareCenter -> P
// * proj_u: Distance along local X axis (U)
// * proj_v: Distance along local Y axis (V)
// */
// typedef struct s_square_vars
// {
// 	t_real		denom;
// 	t_vec3		vec_diff;
// 	t_real		dist;
// 	t_point3	impact_point;
// 	t_vec3		vec_center_hit;
// 	t_real		proj_u;
// 	t_real		proj_v;
// }	t_square_vars;

// typedef struct s_square
// {
// 	t_point3	center;
// 	t_vec3		normal;
// 	t_vec3		u_axis;
// 	t_vec3		v_axis;
// 	t_real		side_size;
// }	t_square;

//* -------------------- CYLINDER -------------------- *//
/*
Equation: Quadratic Equation
|| (O + tD - C) x A ||^2 = r^2
Expands to: at^2 + bt + c = 0
Method:
1. Solve quadratic for infinite tube.
2. Check "height" bounds (Project intersection onto axis).
* origin: Ray origin
* dir: Ray direction
* oc: Vector RayOrigin -> CylinderCenter
* a, b, c: Quadratic Coefficients
* delta: Discriminant (b^2 - 4ac)
* two_a: Denominator 2*a stored for division
* sqrt_delta: Square root of discriminant
* is_inside: Flag: Camera is inside the cylinder?
*/
typedef struct s_cylinder_vars
{
	t_point3	origin;
	t_vec3		dir;
	t_vec3		oc;
	t_real		a;
	t_real		b;
	t_real		c;
	t_real		delta;
	t_real		two_a;
	t_real		sqrt_delta;
	t_bool		is_inside;
}	t_cylinder_vars;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	t_real		radius;
	t_real		height;
	t_point3	cap_top;
	t_point3	cap_bottom;
	t_vec3		diff;
	t_real		half_height;
	t_vec3		half_height_vec;
}	t_cylinder;

// //* -------------------- TRIANGLE -------------------- *//
// /*
// Equation: Möller-Trumbore Algorithm
// O + tD = (1 - u - v)V0 + uV1 + vV2
// Method:
// Uses Cramer's rule to solve the linear system directly for t, u, and v
// without computing the plane equation first.
// * h: Vector H = Cross(RayDir, Edge2)
// * s: Vector S = RayOrigin - V0
// * q: Vector Q = Cross(S, Edge1)
// * det: Determinant = Dot(Edge1, H)
// * inv_det: Inverse of the determinant
// * u: 1st Barycentric coordinate
// * v: 2nd Barycentric coordinate
// * t: Intersection distance

// */
// typedef struct s_triangle_vars
// // {
// // 	t_real pl;
// // 	t_real d;
// // 	t_real t;
// // 	t_real p;
// // 	t_vec3 test[3];
// // }	t_triangle_vars;
// {
// 	t_vec3	h;
// 	t_vec3	s;
// 	t_vec3	q;
// 	t_real	det;
// 	t_real	inv_det;
// 	t_real	u;
// 	t_real	v;
// 	t_real	t;
// }	t_triangle_vars;

// typedef struct s_triangle
// {
// 	t_point3	v0;
// 	t_point3	v1;
// 	t_point3	v2;
// 	t_vec3		edge1;
// 	t_vec3		edge2;
// 	t_vec3		normal;
// 	// t_real traverse;
// }	t_triangle;

#endif