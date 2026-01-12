/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:06:24 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 19:40:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_vec3(t_scene *scene, char **line, t_vec3 *vector)
{
	char	*start_line;

	start_line = *line;
	if (parse_real(line, &vector->x) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_X), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_line = *line;
	if (parse_real(line, &vector->y) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_Y), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_line = *line;
	if (parse_real(line, &vector->z) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_Z), 1);
	return (EXIT_SUCCESS);
}

t_status	parse_axis(t_scene *scene, char **line, t_vec3 *axis)
{
	char	*start_line;

	start_line = *line;
	if (parse_real(line, &axis->x) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_X), 1);
	if (axis->x < -1.0 || axis->x > 1.0)
		return (print_error_loc(scene, start_line, ERR_UX_OOB), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_line = *line;
	if (parse_real(line, &axis->y) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_Y), 1);
	if (axis->y < -1.0 || axis->y > 1.0)
		return (print_error_loc(scene, start_line, ERR_UY_OOB), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_line = *line;
	if (parse_real(line, &axis->z) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_Z), 1);
	if (axis->z < -1.0 || axis->z > 1.0)
		return (print_error_loc(scene, start_line, ERR_UZ_OOB), 1);
	if (vec3_len_squared(*axis) == 0.0)
		return (print_error_loc(scene, start_line, ERR_VEC3_ZERO), 1);
	*axis = vec3_normalize(*axis);
	return (EXIT_SUCCESS);
}
