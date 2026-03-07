/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_illum_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:08:36 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 22:14:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_illum(char **line, t_material **material)
{
	int	model;

	if (parse_int(line, &model) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (model == 0)
		(*material)->type = EMISSIVE;
	else if (model == 1)
		(*material)->type = LAMBERT;
	else if (model == 2)
		(*material)->type = PHONG;
	else if (model == 3)
		(*material)->type = METAL;
	else if (model == 4)
		(*material)->type = DIELECTRIC;
	else if (model == 5)
		(*material)->type = OREN_NAYAR;
	else if (model == 6)
		(*material)->type = COOK_TORRANCE;
	else
	{
		(*material)->type = LAMBERT;
		log_event(stderr, "WARNING",
			"Unknown illumination model %d. Defaulting to LAMBERT.\n", model);
	}
	return (EXIT_SUCCESS);
}
