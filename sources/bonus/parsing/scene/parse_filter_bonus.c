/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filter_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 10:00:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	create_and_append_filter_entry(t_scene *scene,
	t_filter_type filter_type, t_real param)
{
	t_filter_entry	*entry;
	t_filter_entry	*current_entry;

	entry = ft_calloc(1, sizeof(t_filter_entry));
	if (!entry)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	entry->type = filter_type;
	entry->param = param;
	entry->next = NULL;
	if (!scene->filters)
		scene->filters = entry;
	else
	{
		current_entry = scene->filters;
		while (current_entry->next)
			current_entry = current_entry->next;
		current_entry->next = entry;
	}
	return (EXIT_SUCCESS);
}

static t_status	parse_filter_parameter_positive(t_scene *scene, char **line,
	t_filter_type filter_type, t_real default_value)
{
	char	*start;
	t_real	value;

	start = *line;
	skip_whitespace(line);
	value = default_value;
	if (**line != '\0' && **line != '#')
	{
		if (parse_real(line, &value) == EXIT_FAILURE)
			return (print_error_loc(scene, start, ERR_FILTER_VAL),
				EXIT_FAILURE);
		if (value <= 0)
			return (print_error_loc(scene, start, ERR_FILTER_OOB),
				EXIT_FAILURE);
	}
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (create_and_append_filter_entry(scene, filter_type, value));
}

static t_status	parse_filter_parameter_non_negative(t_scene *scene, char **line,
	t_filter_type filter_type, t_real default_value)
{
	char	*start;
	t_real	value;

	start = *line;
	skip_whitespace(line);
	value = default_value;
	if (**line != '\0' && **line != '#')
	{
		if (parse_real(line, &value) == EXIT_FAILURE)
			return (print_error_loc(scene, start, ERR_FILTER_VAL),
				EXIT_FAILURE);
		if (value < 0)
			return (print_error_loc(scene, start, ERR_FILTER_OOB),
				EXIT_FAILURE);
	}
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (create_and_append_filter_entry(scene, filter_type, value));
}

static t_status	parse_filter_without_parameter(t_scene *scene, char **line,
	t_filter_type filter_type)
{
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (create_and_append_filter_entry(scene, filter_type, 0.0));
}

t_status	parse_filter(t_scene *scene, char **line)
{
	char	*start;

	start = *line;
	skip_whitespace(line);
	if (match_and_consume(line, "SOBEL") == EXIT_SUCCESS)
		return (parse_filter_without_parameter(scene, line, FILTER_SOBEL));
	if (match_and_consume(line, "BNW") == EXIT_SUCCESS)
		return (parse_filter_without_parameter(scene, line, FILTER_BNW));
	if (match_and_consume(line, "GAUSSIAN") == EXIT_SUCCESS)
		return (parse_filter_parameter_positive(scene, line,
				FILTER_GAUSSIAN, 2.0));
	if (match_and_consume(line, "SEPIA") == EXIT_SUCCESS)
		return (parse_filter_without_parameter(scene, line, FILTER_SEPIA));
	if (match_and_consume(line, "SHARPEN") == EXIT_SUCCESS)
		return (parse_filter_parameter_positive(scene, line,
				FILTER_SHARPEN, 1.0));
	if (match_and_consume(line, "CONTRAST") == EXIT_SUCCESS)
		return (parse_filter_parameter_non_negative(scene, line,
				FILTER_CONTRAST, 1.0));
	if (match_and_consume(line, "SATURATION") == EXIT_SUCCESS)
		return (parse_filter_parameter_non_negative(scene, line,
				FILTER_SATURATION, 1.0));
	print_error_loc(scene, start, ERR_FILTER_UID);
	return (EXIT_FAILURE);
}
