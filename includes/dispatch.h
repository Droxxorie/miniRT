/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:58:43 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 20:33:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

# include <engine.h>

typedef struct s_parse_map
{
	char	*id;
	t_status	(*func)(t_scene *scene, char **line_tokens);
}	t_parse_map;

typedef struct s_key_map
{
	int		keycode;
	t_bool	(*action)(t_scene *scene);
}	t_key_map;

typedef struct s_intersect_dispatch
{
	t_object_type	type;
	t_bool			(*func)(t_objects *objects, t_hit_record *record);
}	t_intersect_dispatch;

typedef struct s_construct_dispatch // ? redondant
{
	t_object_type	type;
	t_bool			(*func)(t_objects *objects);
}	t_construct_dispatch;

typedef struct s_shader_dispatch
{
	t_mode		mode;
	t_color		(*func)(t_scene *scene, t_hit_record *record);
}	t_shader_dispatch;

#endif