/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukkan <tlaukkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:13 by tlaukkan          #+#    #+#             */
/*   Updated: 2020/01/16 11:18:10 by tlaukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

/*
** removes the block from the map.
*/

void	remove_block(t_tetr *tetris, char *block, int x, int y)
{
	int i;
	int	reset_x;

	i = 0;
	reset_x = x;
	while (block[i])
	{
		if (block[i] == '\n')
		{
			x = reset_x;
			y++;
		}
		else
		{
			if (block[i] != '.')
				tetris->map[y][x] = '.';
			x++;
		}
		i++;
	}
}

/*
** to the given spot (x, y) it places the block.
*/

void	insert_block(t_tetr *tetris, char *block, int x, int y)
{
	int i;
	int	reset_x;

	i = 0;
	reset_x = x;
	while (block[i])
	{
		if (block[i] == '\n')
		{
			x = reset_x;
			y++;
		}
		else
		{
			if (block[i] != '.')
				tetris->map[y][x] = block[i];
			x++;
		}
		i++;
	}
}

/*
** This function finds a spot for the block and checks if it fits or not.
** reset_x, resets the x to the original spot when the function was called
**	because of /n.
*/

int		find_block(t_tetr *tetris, char *block, int x, int y)
{
	int i;
	int	reset_x;

	i = 0;
	reset_x = x;
	while (block[i])
	{
		if (block[i] == '\n')
		{
			x = reset_x;
			y++;
		}
		else
		{
			if (x >= tetris->size || y >= tetris->size)
				return (0);
			if (block[i] != '.' && tetris->map[y][x] != '.')
				return (0);
			x++;
		}
		i++;
	}
	return (1);
}

int		place_it(t_tetr *tetris, char **block, int index)
{
	int x;
	int y;

	y = 0;
	while (y < tetris->size)
	{
		x = 0;
		while (x < tetris->size)
		{
			if (find_block(tetris, block[index], x, y))
			{
				insert_block(tetris, block[index], x, y);
				if (index == (tetris->bc - 1) ||
							place_it(tetris, block, index + 1))
					return (1);
				else
				{
					remove_block(tetris, block[index], x, y);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	solver(t_tetr *tetris, int size)
{
	tetris->map = create_map(tetris, size);
	tetris->size = size;
	if (!(place_it(tetris, tetris->shapes, 0)))
	{
		clean(tetris->map);
		solver(tetris, tetris->size + 1);
	}
	else
	{
		map_printer(tetris->map);
		clean(tetris->map);
	}
}
