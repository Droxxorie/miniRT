/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:29:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 17:03:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_material	*find_material(t_material *materials, char *name)
{
	int	name_len;

	if (materials == NULL || name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	while (materials)
	{
		if (ft_strncmp(materials->name, name, name_len) == 0)
			return (materials);
		materials = materials->next;
	}
	return (NULL);
}

char	*extract_string(char **line)
{
	char	*start;
	char	*result;

	skip_whitespace(line);
	if (**line == '\0')
		return (NULL);
	start = *line;
	while (**line && !ft_iswhitespace(**line))
		(*line)++;
	result = ft_substr(start, 0, *line - start);
	if (result == NULL)
		print_error(ERR_MEM);
	return (result);
}

t_status	parse_texture_path(char **line, char **texture_path)
{
	char	*extracted_path;

	extracted_path = extract_string(line);
	if (extracted_path == NULL)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	*texture_path = extracted_path;
	return (EXIT_SUCCESS);
}

t_status	parse_roughness(char **line, t_material *material)
{
	t_real	ns;
	t_real	roughtness_sq;

	if (parse_real(line, &ns) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ns = ft_clamp(ns, 0.0, 1000.0);
	material->roughness = 1.0 - (ns / 1000.0);
	material->roughness = ft_clamp(material->roughness, EPSILON, 1.0);
	roughtness_sq = material->roughness * material->roughness;
	material->a = 1.0 - (0.5 * roughtness_sq / (roughtness_sq + 0.33));
	material->b = 0.45 * (roughtness_sq / (roughtness_sq + 0.09));
	return (EXIT_SUCCESS);
}
