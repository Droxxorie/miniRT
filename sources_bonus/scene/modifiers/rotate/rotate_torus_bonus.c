/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_torus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:50:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 01:06:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_torus(t_object *object, t_vec3 rotation_axis)
{
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;
	t_mat4		old_transform;
	t_point3	center;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	center.x = object->transform.m[0][3];
	center.y = object->transform.m[1][3];
	center.z = object->transform.m[2][3];
	old_transform = object->transform;
	old_transform.m[0][3] = 0.0;
	old_transform.m[1][3] = 0.0;
	old_transform.m[2][3] = 0.0;
	object->transform = mat4_mult_mat4(rotation_matrix, old_transform);
	object->transform.m[0][3] = center.x;
	object->transform.m[1][3] = center.y;
	object->transform.m[2][3] = center.z;
	set_transform(object, object->transform);
}

/*
** Cette fonction applique une rotation "Monde" au Tore.
** Contrairement au triangle, on ne bouge pas de points, on modifie la matrice.
**
** 1. On extrait la position actuelle (le centre).
** 2. On remet la matrice à l'origine (0,0,0).
** 3. On applique la rotation :
** - Pour éviter l'effet "Toupie", on multiplie souvent dans l'ordre inverse
** ou on s'assure d'appliquer la rotation par rapport au repère global.
** 4. On remet la position.
*/
// void    rotate_torus(t_object *object, t_vec3 rotation_axis)
// {
//     t_real      angle;
//     t_vec3      axis_input;
//     t_mat4      rotation_matrix;
//     t_mat4      old_transform;
//     t_point3    center;

//     angle = vec3_len(rotation_axis);
//     if (angle < EPSILON)
//         return ;

//     axis_input = vec3_normalize(rotation_axis);
//     rotation_matrix = matrix_axis_angle(axis_input, angle);

//     // 1. Sauvegarde du centre (comme pour ton triangle)
//     center.x = object->transform.m[0][3];
//     center.y = object->transform.m[1][3];
//     center.z = object->transform.m[2][3];

//     // 2. Isolation de la rotation actuelle (sans la position)
//     old_transform = object->transform;
//     old_transform.m[0][3] = 0.0;
//     old_transform.m[1][3] = 0.0;
//     old_transform.m[2][3] = 0.0;

//     // 3. Application de la rotation (Cas Spécial Tore)
//     // ESSAI 1 : Rotation Monde (Global)
// -> Souvent ce qu'on veut pour éviter la toupie
//
// La rotation (rotation_matrix) est appliquée "par-dessus" l'ancienne transfo
//     object->transform = mat4_mult_mat4(rotation_matrix, old_transform);

//
// SI L'ESSAI 1 NE MARCHE PAS (Si l'axe X semble toujours mort ou bizarre) :
//     // Essaie d'inverser juste cette ligne :
//     // object->transform = mat4_mult_mat4(old_transform, rotation_matrix);

//     // 4. On remet le centre
//     object->transform.m[0][3] = center.x;
//     object->transform.m[1][3] = center.y;
//     object->transform.m[2][3] = center.z;

//     // 5. Recalcul des inverses (CRUCIAL pour l'intersection du tore)
//     set_transform(object, object->transform);

//     // Note: On ne met PAS à jour torus->axis ici.
//
// L'orientation est entièrement contenue dans la matrice `object->inverse`
//     // utilisée par hit_torus.
// }

// void	rotate_torus(t_object *object, t_vec3 rotation_axis)
// {
// 	t_real		angle;
// 	t_vec3		axis_input;
// 	t_mat4		rotation_matrix;
// 	t_torus		*torus;

// 	angle = vec3_len(rotation_axis);
// 	if (angle < EPSILON)
// 		return ;
// 	torus = &object->u_data.torus;
// 	axis_input = vec3_normalize(rotation_axis);
// 	rotation_matrix = matrix_axis_angle(axis_input, angle);
// 	apply_rotation_to_matrix(object, rotation_matrix);
// 	torus->axis = vec3_normalize(torus->axis);
// }
