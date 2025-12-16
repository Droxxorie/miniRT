/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:32:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 18:51:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <maths.h>

# define MAX_OBJECTS 100

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_color			color;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
	}	data;
	struct s_object	*next;
}	t_object;

//* -------------------- SPHERE -------------------- *//
/*
Equation: Quadratic Equation
at^2 + bt + c = 0
where:
a = D . D
b = 2(OC . D)
c = OC . OC - r^2
Method: Substitute the ray equation into the sphere equation and solve
for t using the quadratic formula.
* oc: Vector from RayOrigin to SphereCenter
* a, half_b, c: Quadratic coefficients
* delta: Discriminant (b^2 - 4ac)
* sqrt_delta: Square root of discriminant
* root: Potential intersection distance
*/
typedef struct s_poly
{
	t_real	a;
	t_real	half_b;
	t_real	c;
	t_real	min;
	t_real	max;
	t_real	root1;
	t_real	root2;
} t_poly;

typedef struct s_sphere
{
	t_point3	center;
	t_real		radius;
	t_real		radius_squared;
}	t_sphere;

//* -------------------- PLANE -------------------- *//
typedef struct s_plane
{
	t_point3	origin;
	t_vec3		normal;
	t_real		d; //distance from origin
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
Equation: Quadratic Equation (Infinite Cylinder) + Height Check
*/
typedef struct s_cylinder_vars
{
	t_poly	eq_vars;
	t_vec3	oc;
	t_real	dot_dir_axis;
	t_real	dot_oc_axis;
	t_real	half_height;
	t_real	projection;
}	t_cylinder_vars;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	t_real		radius;
	t_real		radius_squared;
	t_real		height;
	// t_point3	cap_top;
	// t_point3	cap_bottom;
	// t_vec3		diff;
	// t_real		half_height;
	// t_vec3		half_height_vec;
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