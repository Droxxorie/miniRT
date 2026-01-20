/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_mtl_line_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:28:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 15:05:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	dispatch_scalars(t_material *current, char *line)
{
	if (match_and_consume(&line, "Ns") == EXIT_SUCCESS)
		return (parse_roughness(&line, current));
	if (match_and_consume(&line, "Ni") == EXIT_SUCCESS)
		return (parse_real(&line, &current->ior));
	if (match_and_consume(&line, "d") == EXIT_SUCCESS)
		return (parse_real(&line, &current->transparency));
	if (match_and_consume(&line, "uv_scale") == EXIT_SUCCESS)
		return (parse_real(&line, &current->uv_scale));
	if (match_and_consume(&line, "wave") == EXIT_SUCCESS)
	{
		current->has_wave = TRUE;
		return (EXIT_SUCCESS);
	}
	return (-1);
}

static t_status	dispatch_maps(t_material *current, char *line)
{
	if (match_and_consume(&line, "map_Kd") == EXIT_SUCCESS)
		return (parse_texture_path(&line, &current->albedo_texture_path));
	if (match_and_consume(&line, "map_Bump") == EXIT_SUCCESS
		|| match_and_consume(&line, "Bump") == EXIT_SUCCESS)
		return (parse_texture_path(&line, &current->normal_texture_path));
	if (match_and_consume(&line, "map_Pr") == EXIT_SUCCESS
		|| match_and_consume(&line, "map_Ns") == EXIT_SUCCESS)
		return (parse_texture_path(&line, &current->roughness_texture_path));
	if (match_and_consume(&line, "map_Ke") == EXIT_SUCCESS)
		return (parse_texture_path(&line, &current->emission_texture_path));
	return (-1);
}

static t_status	dispatch_properties(t_material *current, char *line)
{
	if (match_and_consume(&line, "Kd") == EXIT_SUCCESS)
		return (parse_color_mtl(&line, &current->color));
	if (match_and_consume(&line, "Ks") == EXIT_SUCCESS)
		return (parse_color_mtl(&line, &current->specular_color));
	if (match_and_consume(&line, "Ke") == EXIT_SUCCESS)
		return (parse_color_mtl(&line, &current->emission_color));
	if (match_and_consume(&line, "Ka") == EXIT_SUCCESS)
		return (parse_color_mtl(&line, &current->ambient_color));
	if (match_and_consume(&line, "illum") == EXIT_SUCCESS)
		return (parse_illum(&line, &current));
	return (-1);
}

t_status	dispatch_mtl_line(t_scene *scene, t_material **current, char *line)
{
	t_status	status;

	skip_whitespace(&line);
	if (*line == '\0' || *line == '#' || *line == '\n')
		return (EXIT_SUCCESS);
	if (match_and_consume(&line, "newmtl") == EXIT_SUCCESS)
		return (parse_newmtl(scene, current, &line));
	if (*current == NULL)
		return (print_error_loc(scene, line, ERR_MTL_DEF), EXIT_FAILURE);
	status = dispatch_properties(*current, line);
	if (status != -1)
		return (status);
	status = dispatch_scalars(*current, line);
	if (status != -1)
		return (status);
	status = dispatch_maps(*current, line);
	if (status != -1)
		return (status);
	return (print_error_loc(scene, line, ERR_MTL_UID), EXIT_FAILURE);
}
