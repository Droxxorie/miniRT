/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_parse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:48:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 22:31:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	dispatch_shapes(t_scene *scene, char *line)
{
	if (match_and_consume(&line, "sp") == EXIT_SUCCESS)
		return (parse_sphere(scene, &line));
	if (match_and_consume(&line, "pl") == EXIT_SUCCESS)
		return (parse_plane(scene, &line));
	if (match_and_consume(&line, "cy") == EXIT_SUCCESS)
		return (parse_cylinder(scene, &line));
	if (match_and_consume(&line, "rec") == EXIT_SUCCESS)
		return (parse_rectangle(scene, &line));
	if (match_and_consume(&line, "dis") == EXIT_SUCCESS)
		return (parse_disk(scene, &line));
	if (match_and_consume(&line, "tri") == EXIT_SUCCESS)
		return (parse_triangle(scene, &line));
	if (match_and_consume(&line, "tor") == EXIT_SUCCESS)
		return (parse_torus(scene, &line));
	if (match_and_consume(&line, "con") == EXIT_SUCCESS)
		return (parse_cone(scene, &line));
	if (match_and_consume(&line, "box") == EXIT_SUCCESS)
		return (parse_box(scene, &line));
	return (-1);
}

static t_status	dispatch_fractals(t_scene *scene, char *line)
{
	if (match_and_consume(&line, "menger_sponge") == EXIT_SUCCESS)
		return (parse_menger_sponge(scene, &line));
	if (match_and_consume(&line, "mandelbulb") == EXIT_SUCCESS)
		return (parse_mandelbulb(scene, &line));
	if (match_and_consume(&line, "mandelbox") == EXIT_SUCCESS)
		return (parse_mandelbox(scene, &line));
	if (match_and_consume(&line, "julia_set") == EXIT_SUCCESS)
		return (parse_julia_set(scene, &line));
	return (-1);
}

static t_status	dispatch_entities(t_scene *scene, char *line)
{
	if (match_and_consume(&line, "A") == EXIT_SUCCESS)
		return (parse_ambient(scene, &line));
	if (match_and_consume(&line, "C") == EXIT_SUCCESS)
		return (parse_camera(scene, &line));
	if (match_and_consume(&line, "L") == EXIT_SUCCESS)
		return (parse_light(scene, &line));
	if (match_and_consume(&line, "SB") == EXIT_SUCCESS)
		return (parse_skybox(scene, &line));
	return (-1);
}

t_status	dispatch_parse(t_scene *scene, char *line)
{
	char		*start_ptr;
	t_status	status;

	start_ptr = line;
	skip_whitespace(&line);
	if (*line == '\0' || *line == '#')
		return (EXIT_SUCCESS);
	if (match_and_consume(&line, "R") == EXIT_SUCCESS)
		return (parse_resolution(scene, &line));
	if (match_and_consume(&line, "mtllib") == EXIT_SUCCESS)
		return (parse_mtl_lib(scene, &line));
	status = dispatch_entities(scene, line);
	if (status != -1)
		return (status);
	status = dispatch_shapes(scene, line);
	if (status != -1)
		return (status);
	status = dispatch_fractals(scene, line);
	if (status != -1)
		return (status);
	print_error_loc(scene, start_ptr, ERR_UID);
	return (EXIT_FAILURE);
}
