/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aa_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:20:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 11:18:59 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_aa(t_scene *scene, char **line)
{
	if (parse_dim(scene, line, &scene->aa_samples) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (scene->aa_samples > 16)
	{
		print_error_loc(scene, *line - 1, ERR_AA_OOB);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
