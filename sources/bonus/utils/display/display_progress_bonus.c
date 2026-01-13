/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_progress_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:03:08 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:50:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	display_progress(int current, int total)
{
	int		filled_width;
	int		percentage;
	int		i;

	percentage = (current * 100) / total;
	if (current != 0 && percentage == ((current - 1) * 100) / total)
		return ;
	filled_width = (50 * percentage) / 100;
	ft_putstr_fd("\r", 1);
	i = -1;
	while (++i < 50)
	{
		if (i < filled_width)
			ft_putstr_fd("█", 1);
		if (i > filled_width)
			ft_putstr_fd("░", 1);
	}
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(percentage, 1);
	ft_putstr_fd("%", 1);
	if (current >= total)
		ft_putstr_fd("\r\033[2K", 1);
}
