/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:14:22 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 00:28:39 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_window_value_cordition(int count_x, int *start_x, int *width);

void	init_window_value(int *start_x, int *y, int *height, int *width)
{
	static int	count_x = 0;
	static int	start_y = 0;
	static int	c = 0;

	++count_x;
	*y = start_y;
	*height = HEIGHT / 4 + *y;
	if (!init_window_value_cordition(count_x, start_x, width))
	{
		*start_x = WIDTH / 2 + WIDTH / 4;
		*width = WIDTH;
		if (++c < 4)
			start_y += HEIGHT / 4;
		else
		{
			start_y = 0;
			c = 0;
		}
	}
}

static int	init_window_value_cordition(int count_x, int *start_x, int *width)
{
	int result;

	result = 0;
	if (count_x % 4 == 0)
	{
		*start_x = 0;
		*width = WIDTH / 4;
		++result;
	}
	else if (count_x % 4 == 1)
	{
		*start_x = WIDTH / 4;
		*width = WIDTH / 2;
		++result;
	}
	else if (count_x % 4 == 2)
	{
		*start_x = WIDTH / 2;
		*width = WIDTH / 2 + WIDTH / 4;
		++result;
	}
	return (result);
}
