/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:06:24 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 18:08:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	parse_vec3(char **line, t_vec3	*vector)
{
	if (parse_real(line, &vector->x) == EXIT_FAILURE
		|| parse_comma(line) == EXIT_FAILURE
		|| parse_real(line, &vector->y) == EXIT_FAILURE
		|| parse_comma(line) == EXIT_FAILURE
		|| parse_real(line, &vector->z) == EXIT_FAILURE)
		return (print_error(ERR_PARSE_VEC3), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
