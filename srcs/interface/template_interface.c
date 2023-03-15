/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:06:41 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 02:24:51 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_topbott_box(t_img *img, int y, int x, int start);

/*
* [function draw selection status symbol to window]
* [selection status symbol is mini squere]
* [put to window when status is selecting]
* (1) y = 459 | x = WIDTH + 141 | end_x = WIDTH +152 | end_y = y + 8
*/
void	selected_box_statute_to_window(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	colour;

	colour = rgb_to_int(224, 224, 224);
	y = 459;
	end_y = y + 8;
	end_x = WIDTH + 141;
	while (y < end_y)
	{
		x = WIDTH + 128;
		while (x < end_x)
		{
			pixel_put_img(img, x, y, colour);
			x++;
		}
		y++;
	}
}

/*
* [funtion draw elements colour to window]
* [square of colour width is 12. (y - end_y)]
* [square of colour height is 8. (x - end_x)]
* (1) x = WIDTH + 4 | y = line + 4 | end_x = WIDTH + 18 | end_y = line + 12
*/
void	put_colour_to_window(t_data *data, t_img *img, int line, int colour)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = line + 4;
	end_y = line + 12;
	end_x = WIDTH + 25;
	while (y < end_y)
	{
		x = WIDTH + 10;
		while (x < end_x)
		{
			pixel_put_img(img, x, y, colour);
			x++;
		}
		y++;
	}
}

/*
* [function draw header of element identifier on image]
* [header is sqaure with empty on the mindle for string]
* (1) y = 0 | x = WIDTH
*/
void	header_identifier_interface(t_data *data, t_img *img)
{
	int	y;
	int	x;
	int	colour;

	y = 0;
	colour = rgb_to_int(224, 224, 224);
	while (y < 28)
	{
		x = WIDTH;
		if (y <= 4 || y >= 23)
		{
			while (x < WIDTH_EX)
				pixel_put_img(img, x++, y, colour);
		}
		else
		{
			pixel_put_img(img, x, y, colour);
			pixel_put_img(img, x + 1, y, colour);
			pixel_put_img(img, WIDTH_EX, y, colour);
			pixel_put_img(img, WIDTH_EX - 1, y, colour);
			pixel_put_img(img, WIDTH_EX - 2, y, colour);
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
	int c[2];
	int start;
	int count;

	count = -1;
	c[COL] = 28;
	while (++count < 5)
	{
		start = c[COL];
		if (count < objects)
			put_colour_to_window(data, img, c[COL], colour[count]);
		while (c[COL] <= start + 82)
		{
			c[ROW] = WIDTH;
			while (c[ROW] < WIDTH_EX && c[COL] >= start + 81)
				pixel_put_img(img, c[ROW]++, c[COL], 0x0E0E0E0);
			if (c[COL]++ < start + 81)
			{
				pixel_put_img(img, c[ROW], --c[COL], 0x0E0E0E0);
				pixel_put_img(img, c[ROW] + 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, WIDTH_EX - 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, WIDTH_EX - 2, c[COL]++, 0x0E0E0E0);
			}
		}
	}
}

/*
void	selection_interface(t_data *data, t_img *img)
{
	int x;
	int y;
	int start;
	int count;

	y = 443;
	start = y;
	while (y < HEIGHT)
	{
		x = WIDTH;
		if (y <= start + 10 || y >= HEIGHT - 10)
		{
			if (!(y >= HEIGHT - 6 && y <= HEIGHT - 5) && !(y <= start + 6 && y >= start + 5))
			// if ((y <= HEIGHT - 6 && y >= HEIGHT - 5) && (y <= start + 6 && y >= start + 5))
			{
				while (x < WIDTH_EX)
				{
					if (!(y > start + 6 && y < HEIGHT - 6 && x >= WIDTH + 1 && x < WIDTH + 4)
						&& !(y > start + 6 && y < HEIGHT - 6 && x <= WIDTH_EX - 1 && x > WIDTH_EX - 4))
						pixel_put_img(img, x, y, 0x0E0E0E0);
					x++;
				}
			}
		}
		else
		{
			count = 0;
			while (count < 6)
			{
				if (count < 1 || count > 3)
				{
					pixel_put_img(img, x + count, y, 0x0E0E0E0);
					pixel_put_img(img, WIDTH_EX - count, y, 0x0E0E0E0);
				}
				count++;
			}
		}
		y++;
	}
}
*/

/*
* [function draw soild box for selection part of interface]
* (1) y = 443 | x  = WIDTH
*/
void	selection_interface(t_data *data, t_img *img)
{
	int x;
	int y;
	int start;
	int count;

	y = 443;
	start = y;
	while (y < HEIGHT)
	{
		x = WIDTH;
		if (y <= start + 10 || y >= HEIGHT - 10)
			draw_topbott_box(img, y, x, start);
		else
		{
			count = 0;
			while (count < 6)
			{
				pixel_put_img(img, x + count, y, 0x0E0E0E0);
				pixel_put_img(img, WIDTH_EX - count++, y, 0x0E0E0E0);
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
		while (x < WIDTH_EX)
		{
			if (!(y > start + 6 && y < HEIGHT - 6 
				&& x >= WIDTH + 1 && x < WIDTH + 4)
				&& !(y > start + 6 && y < HEIGHT - 6
				&& x <= WIDTH_EX - 1 && x > WIDTH_EX - 4))
				pixel_put_img(img, x, y, 0x0E0E0E0);
			x++;
		}
	}
	else
	{
		pixel_put_img(img, x, y, 0x0E0E0E0);
		pixel_put_img(img, WIDTH_EX, y, 0x0E0E0E0);
	}
}

/*
* [function draw interface onto image and put to window]
TODO change size of image and put it into x = WIDTH for solving rerandering problem.
*/
void	put_template_to_window(t_data *data, int objects, int *colour)
{
	t_img	img;
	int		column;
	int		count = 0;
	int		start;

	img.ptr = mlx_new_image(data->mlx, WIDTH_EX, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	// * white box around window.
	// y = 0;
	// while (y < HEIGHT)
	// {
	// 	start = y;
	// 	x = 0;
	// 	if (y <= 3 || y >= HEIGHT - 3)
	// 	{
	// 		while (x < WIDTH)
	// 		{
	// 			pixel_put_img(&img, x, y, 0x0E0E0E0);
	// 			x++;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		pixel_put_img(&img, x, y, 0x0E0E0E0);
	// 		pixel_put_img(&img, x + 1, y, 0x0E0E0E0);
	// 		pixel_put_img(&img, x + 2, y, 0x0E0E0E0);
	// 	}
	// 	y++;
	// }
	header_identifier_interface(data, &img);
	body_indentifier_interface(data, &img, objects, colour);
	selection_interface(data, &img);
	if (data->selectp == -1)
		selected_box_statute_to_window(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, 0, 0);
	// * top line
	// * left line
	// * bottom line
	// * [real world] tag.
}