/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_order_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 22:55:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	get_dx(int dir)
{
	if (dir == 0)
		return (1);
	if (dir == 2)
		return (-1);
	return (0);
}

static int	get_dy(int dir)
{
	if (dir == 1)
		return (1);
	if (dir == 3)
		return (-1);
	return (0);
}

static void	spiral_arm(int *state, int dir, int len, t_scene *s)
{
	int	i;

	i = 0;
	while (i < len)
	{
		state[0] += get_dx(dir);
		state[1] += get_dy(dir);
		if (state[0] >= 0 && state[0] < s->tiles_per_row
			&& state[1] >= 0 && state[1] < s->tiles_per_col)
		{
			s->tile_order[state[2]] = state[1]
				* s->tiles_per_row + state[0];
			state[2]++;
		}
		i++;
	}
}

static void	spiral_layer(int *state, int *ds, t_scene *s)
{
	spiral_arm(state, ds[0], ds[1], s);
	ds[0] = (ds[0] + 1) % 4;
	spiral_arm(state, ds[0], ds[1], s);
	ds[0] = (ds[0] + 1) % 4;
	ds[1]++;
}

//* state[0] = current x tile
//* state[1] = current y tile
//* state[2] = tiles filled
//* ds[0] = current direction (0=right, 1=down, 2=left, 3=up)
//* ds[1] = current arm length
void	build_spiral_order(t_scene *s)
{
	int	state[3];
	int	ds[2];
	int	max_dim;

	s->tile_order = malloc(sizeof(int) * s->total_tiles);
	if (!s->tile_order)
		return ;
	state[0] = s->tiles_per_row / 2;
	state[1] = s->tiles_per_col / 2;
	state[2] = 0;
	s->tile_order[0] = state[1] * s->tiles_per_row + state[0];
	state[2] = 1;
	ds[0] = 0;
	ds[1] = 1;
	max_dim = s->tiles_per_row + s->tiles_per_col;
	while (state[2] < s->total_tiles && ds[1] < max_dim)
		spiral_layer(state, ds, s);
}
