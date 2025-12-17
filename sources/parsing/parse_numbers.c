/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:26:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 07:38:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	get_float_len(const char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (-1);
		}
		else if (!ft_isdigit(str[i]))
			break ;
		i++;
	}
	if (i == 0 || (i == 1 && (str[0] == '+' || str[0] == '-')))
		return (-1);
	return (i);
}

t_status	parse_int(char **line, int *value)
{
	int	len;

	skip_whitespace(line);
	len = 0;
	if ((*line)[len] == '+' || (*line)[len] == '-')
		len++;
	while (ft_isdigit((*line)[len]))
		len++;
	if (len == 0 || (len == 1 && !ft_isdigit((*line)[len - 1])))
		return (print_error(ERR_PARSE_NUM), EXIT_FAILURE);
	*value = ft_atoi(*line);
	*line += len;
	return (EXIT_SUCCESS);
}

t_status	parse_real(char **line, t_real *value)
{
	int	len;

	skip_whitespace(line);
	len = get_float_len(*line);
	if (len <= 0)
		return (print_error(ERR_PARSE_NUM), EXIT_FAILURE);
	*value = ft_atodbl(*line);
	*line += len;
	return (EXIT_SUCCESS);
}

t_status	parse_ratio(char **line, t_real *ratio, t_bool is_negative)
{
	t_real	min;

	if (is_negative == TRUE)
		min = -1.0;
	else
		min = 0.0;
	if (parse_real(line, ratio) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (*ratio < min || *ratio > 1.0)
		return (print_error(ERR_PARSE_OOR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
