/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:06:41 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 16:30:22 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	header_identifier_interface(t_data *data, t_img *img);
void		body_indentifier_interface(t_data *data, t_img *img, int objects, int *colour);
static void	put_colour_to_window(t_data *data, t_img *img, int line, int color);
static void		selection_interface(t_data *data, t_img *img);
static void	selected_box_statute_to_window(t_data *data, t_img *img);
static void	draw_topbott_box(t_img *img, int y, int x, int start);
void		draw_square(t_data *data, int width, int height, int start);

/*
* [function draw interface onto image and put to window]
* 150 = WIDTH_EX - WIDTH
*/
void	put_template_to_window(t_data *data, int objects, int *colour)
{
	t_img	img;

	img.ptr = mlx_new_image(data->mlx, 150, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	header_identifier_interface(data, &img);
	body_indentifier_interface(data, &img, objects, colour);
	selection_interface(data, &img);
	if (data->selectp == -1)
		selected_box_statute_to_window(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, WIDTH, 0);
	// draw_square(data, WIDTH_EX, 3, 0);
	draw_square(data, WIDTH_EX, 3, HEIGHT - 3);
	draw_square(data, 2, HEIGHT, 0);
	// real_world_interface(data);
	// * [real world] tag.
}

/*
* [function draw header of element identifier on image]
* [header is sqaure with empty on the mindle for string]
* (1) y = 0 | x = WIDTH
*/
static void	header_identifier_interface(t_data *data, t_img *img)
{
	int	y;
	int	x;
	int	colour;

	y = 0;
	colour = rgb_to_int(224, 224, 224);
	while (y < 28)
	{
		x = 0;
		if (y <= 4 || y >= 23)
		{
			while (x < 150)
				pixel_put_img(img, x++, y, colour);
		}
		else
		{
			pixel_put_img(img, x, y, colour);
			pixel_put_img(img, x + 1, y, colour);
			// pixel_put_img(img, 150, y, colour);
			pixel_put_img(img, 149, y, colour);
			pixel_put_img(img, 148, y, colour);
		}
		y++;
	}
}

/*
* [function draw solid outline boxes for body of element indetifier]
* [constant 5 is number of boxes amount]
* c[COL] : y | c[ROW] : x
* (1) y = 28 | x = WIDTH | 
*/
void	body_indentifier_interface(t_data *data, t_img *img, int objects, int *colour)
{
	int	c[2];
	int	start;
	int	count;

	count = -1;
	c[COL] = 28;
	while (++count < 5)
	{
		start = c[COL];
		if (count < objects)
			put_colour_to_window(data, img, c[COL], colour[count]);
		while (c[COL] <= start + 82)
		{
			c[ROW] = 0;
			while (c[ROW] < 150 && c[COL] >= start + 81)
				pixel_put_img(img, c[ROW]++, c[COL], 0x0E0E0E0);
			if (c[COL]++ < start + 81)
			{
				pixel_put_img(img, c[ROW], --c[COL], 0x0E0E0E0);
				pixel_put_img(img, c[ROW] + 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, 150 - 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, 150 - 2, c[COL]++, 0x0E0E0E0);
			}
		}
	}
}

/*
* [funtion draw elements colour to window]
* [square of colour width is 12. (y - end_y)]
* [square of colour height is 8. (x - end_x)]
* (1) x = WIDTH + 4 | y = line + 4 | end_x = WIDTH + 18 | end_y = line + 12
*/
static void	put_colour_to_window(t_data *data, t_img *img, int line, int color)
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
* [function draw soild box for selection part of interface]
* (1) y = 443 | x  = WIDTH
*/
static void	selection_interface(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	start;
	int	count;

	y = 443;
	start = y;
	while (y < HEIGHT)
	{
		x = 0;
		if (y <= start + 10 || y >= HEIGHT - 10)
			draw_topbott_box(img, y, x, start);
		else
		{
			count = 0;
			while (count < 6)
			{
				pixel_put_img(img, x + count, y, 0x0E0E0E0);
				pixel_put_img(img, 150 - count++, y, 0x0E0E0E0);
			}
		}
		y++;
	}
}

/*
* [helper funciion of selection_interface]
* [draw top and bottom of the box]
*/
static void	draw_topbott_box(t_img *img, int y, int x, int start)
{
	if (!(y >= HEIGHT - 6 && y <= HEIGHT - 5)
		&& !(y <= start + 6 && y >= start + 5))
	{
		while (x < 150)
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
		pixel_put_img(img, 150, y, 0x0E0E0E0);
	}
}

/*
* [function draw selection status symbol to window]
* [selection status symbol is mini squere]
* [put to window when status is selecting]
* (1) y = 459 | x = WIDTH + 141 | end_x = WIDTH +152 | end_y = y + 8
*/
static void	selected_box_statute_to_window(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	colour;

	colour = rgb_to_int(224, 224, 224);
	y = 459;
	end_y = y + 8;
	end_x = 141;
	while (y < end_y)
	{
		x = 128;
		while (x < end_x)
		{
			pixel_put_img(img, x, y, colour);
			x++;
		}
		y++;
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

void	real_world_interface(t_data *data)
{
	int		colour;
	int		x;
	int		y;
	t_img	img;

	img.ptr = mlx_new_image(data->mlx, WIDTH_EX, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	if (data->selectp < 0)
		colour = rgb_to_int(224, 224, 224);
	else
		colour = rgb_to_int(160, 160, 160);
	y = 0;
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, 0, 0);
	mlx_string_put(data->mlx, data->win, 20, 20, colour, "[REAL-WORLD]");
}
