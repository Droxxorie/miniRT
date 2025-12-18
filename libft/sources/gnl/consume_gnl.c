/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:32:49 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 12:32:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	consume_gnl(int fd, char **line)
{
	char	*temp;

	while (*line)
	{
		temp = *line;
		*line = get_next_line(fd);
		free(temp);
	}
}
