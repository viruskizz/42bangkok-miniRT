/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_interface1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:06:41 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:16:02 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	header_identifier_interface(t_img *img);
static void	body_indentifier_interface(t_img *img, int objects, int *colour);
static void	selection_interface(t_img *img);
static void	selected_box_status_to_window(t_img *img);
void		put_colour_to_window(t_img *img, int line, int color);
void		draw_topbott_box(t_img *img, int y, int x, int start);
void		draw_square(t_data *data, int width, int height, int start);
void		draw_side(t_img *img, int x, int y);
void		draw_bottom(t_img *img, int start, int x, int y);

/*
* [function draw interface onto image and put to window]
* 150 = WIDTH_EX - WIDTH
*/
void	put_template_to_window(t_data *data, int objects, int *colour)
{
	t_img	img;

	img.ptr = mlx_new_image(data->mlx, PANEL, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	header_identifier_interface(&img);
	body_indentifier_interface(&img, objects, colour);
	selection_interface(&img);
	if (data->selectp == -1)
		selected_box_status_to_window(&img);
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, WIDTH, 0);
	draw_square(data, WIDTH + PANEL, 3, 0);
	draw_square(data, WIDTH + PANEL, 3, HEIGHT - 3);
	draw_square(data, 2, HEIGHT, 0);
}

/*
* [function draw header of element identifier on image]
* [header is sqaure with empty on the mindle for string]
* (1) y = 0 | x = WIDTH
*/
static void	header_identifier_interface(t_img *img)
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
			while (x < PANEL)
				pixel_put_img(img, x++, y, colour);
		}
		else
		{
			pixel_put_img(img, x, y, colour);
			pixel_put_img(img, x + 1, y, colour);
			pixel_put_img(img, PANEL - 1, y, colour);
			pixel_put_img(img, PANEL - 2, y, colour);
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
static void	body_indentifier_interface(t_img *img, int objects, int *colour)
{
	int	c[2];
	int	start;
	int	count;
	int	boxes_amount;

	count = -1;
	c[COL] = 28;
	boxes_amount = (HEIGHT - 28 - 37) / 83;
	while (++count < boxes_amount)
	{
		start = c[COL];
		if (count < objects)
			put_colour_to_window(img, c[COL], colour[count]);
		while (c[COL] <= start + 82)
		{
			c[ROW] = 0;
			while (c[ROW] < PANEL && c[COL] >= start + 81)
				pixel_put_img(img, c[ROW]++, c[COL], 0x0E0E0E0);
			if (c[COL]++ < start + 81)
				draw_side(img, c[ROW], c[COL] - 1);
		}
	}
	draw_bottom(img, start, c[ROW], c[COL]);
}

/*
* [function draw soild box for selection part of interface]
* (1) y = 443 | x  = WIDTH
*/
static void	selection_interface(t_img *img)
{
	int	x;
	int	y;
	int	start;
	int	count;

	y = HEIGHT - 37;
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
				pixel_put_img(img, PANEL - count++, y, 0x0E0E0E0);
			}
		}
		y++;
	}
}

/*
* [function draw selection status symbol to window]
* [selection status symbol is mini squere]
* [put to window when status is selecting]
* (1) y = 459 | x = WIDTH + 141 | end_x = WIDTH +152 | end_y = y + 8
*/
static void	selected_box_status_to_window(t_img *img)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	colour;

	colour = rgb_to_int(224, 224, 224);
	y = HEIGHT - 21;
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
