/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:58:43 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:17:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

# include <engine.h>

typedef struct s_parse_map
{
	char		*id;
	t_status	(*func)(t_scene *scene, char **line_tokens);
}	t_parse_map;

typedef struct s_key_map
{
	int		keycode;
	t_bool	(*action)(t_scene *scene);
}	t_key_map;

typedef struct s_hit_dispatch
{
	t_object_type	type;
	t_bool			(*func)(t_object *objects, t_ray *ray, t_hit_record *record);
}	t_hit_dispatch;

typedef struct s_resize_map
{
	t_object_type	type;
	void			(*func)(t_object *object, int key);
}	t_resize_map;

typedef struct s_translate_map
{
	t_object_type	type;
	void			(*func)(t_object *object, t_vec3 transform);
}	t_translate_map;

typedef struct s_rotate_map
{
	t_object_type	type;
	void			(*func)(t_object *object, t_vec3 rot_axis);
}	t_rotate_map;

#endif