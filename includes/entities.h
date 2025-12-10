/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:29:56 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 18:12:41 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <vector.h>
# include <color.h>
# include <matrix.h>

typedef struct s_lights
{
	t_point3	position; //origin
	t_real		brightness; //intensity
	t_color		color;
	t_vec3		direction;
	t_real		distance;
	t_real		angle;
	void		*next;
}	t_lights;

typedef struct s_cameras
{
	int			id;
	t_point3	position; //origin
	t_vec3		direction; //normal
	int			fov;
	t_real		view_range;
	t_mat4		view_matrix;
	void		*next;
}	t_cameras;

// typedef struct s_camera_list //? a integrer directement dans s_camera ?
// {
// 	int 		id;
// 	t_camera	camera;
// 	void		*next;
// }	t_camera_list;

#endif