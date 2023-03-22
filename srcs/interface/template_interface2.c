/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_interface2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:26:36 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:01:13 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_bottom(t_img *img, int start, int x, int y)
{
	while (y < HEIGHT - 37)
	{
		x = 0;
		while (x < PANEL && y >= start + 81)
			pixel_put_img(img, x++, y, 0x0E0E0E0);
		y++;
	}
}

void	draw_side(t_img *img, int x, int y)
{
	pixel_put_img(img, x, y, 0x0E0E0E0);
	pixel_put_img(img, x++, y, 0x0E0E0E0);
	pixel_put_img(img, PANEL - 1, y, 0x0E0E0E0);
	pixel_put_img(img, PANEL - 2, y, 0x0E0E0E0);
}

/*
* [funtion draw elements colour to window]
* [square of colour width is 12. (y - end_y)]
* [square of colour height is 8. (x - end_x)]
* (1) x = WIDTH + 4 | y = line + 4 | end_x = WIDTH + 18 | end_y = line + 12
*/
void	put_colour_to_window(t_img *img, int line, int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = line + 4;
	end_y = line + 12;
	end_x = 25;
	while (y < end_y)
	{
		x = 10;
		while (x < end_x)
		{
			pixel_put_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

/*
* [helper funciion of selection_interface]
* [draw top and bottom of the box]
*/
void	draw_topbott_box(t_img *img, int y, int x, int start)
{
	if (!(y >= HEIGHT - 6 && y <= HEIGHT - 5)
		&& !(y <= start + 6 && y >= start + 5))
	{
		while (x < PANEL)
		{
			if (!(y > start + 6 && y < HEIGHT - 6
					&& x >= 1 && x < 4)
				&& !(y > start + 6 && y < HEIGHT - 6
					&& x <= 149 && x > 146))
				pixel_put_img(img, x, y, 0x0E0E0E0);
			x++;
		}
	}
	else
	{
		pixel_put_img(img, x, y, 0x0E0E0E0);
		pixel_put_img(img, PANEL, y, 0x0E0E0E0);
	}
}

/*
* [funciont draw square]
* [for this situation, draw line around window]
* strat : start position for y (column)
*/
void	draw_square(t_data *data, int width, int height, int start)
{
	t_img	img;
	int		x;
	int		y;

	img.ptr = mlx_new_image(data->mlx, width, height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			pixel_put_img(&img, x, y, 0x0E0E0E0);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, 0, start);
}
