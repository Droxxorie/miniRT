/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_illum_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:08:36 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 14:08:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_illum(char **line, t_material **material)
{
	int	illum_model;

	if (parse_int(line, &illum_model) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (illum_model == 0 || illum_model == 1)
		(*material)->type = LAMBERT;
	else if (illum_model == 2)
		(*material)->type = PHONG;
	else if (illum_model == 3)
		(*material)->type = METAL;
	else if (illum_model == 4)
		(*material)->type = DIELECTRIC;
	else if (illum_model >= 5 && illum_model <= 9)
		(*material)->type = EMISSIVE;
	else
	{
		(*material)->type = LAMBERT;
		log_event(stderr,
			"WARNING",
			"Unknown illumination model %d. Defaulting to LAMBERT.",
			illum_model);
	}
	return (EXIT_SUCCESS);
}
