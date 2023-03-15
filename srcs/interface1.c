/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:08:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/15 02:03:23 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	selected_box_statute_to_window(t_data *data, t_img *img)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
	int	colour;

	colour = rgb_to_int(224, 224, 224);
	y = 459; // * initialise of start y_point.
	end_y = y + 8;
	end_x = WIDTH + 141;
	while (y < end_y)
	{
		x = WIDTH + 128; // * initialise of strat x_point.
		while (x < end_x)
		{
			pixel_put_img(img, x, y, colour);
			x++;
		}
		y++;
	}
}

/*
* [funtion put elements colour to window]
* [square of colour width is 12. (y - end_y)]
* [square of colour height is 8. (x - end_x)]
*/
void	put_colour_to_window(t_data *data, t_img *img, int line, int colour)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = line + 4;
	end_y = line + 12;
	end_x = WIDTH + 18;
	while (y < end_y)
	{
		x = WIDTH + 4;
		while (x < end_x)
		{
			pixel_put_img(img, x, y, colour);
			x++;
		}
		y++;
	}
}

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
			if (c[COL] < start + 81)
			{
				pixel_put_img(img, c[ROW], c[COL], 0x0E0E0E0);
				pixel_put_img(img, c[ROW] + 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, WIDTH_EX - 1, c[COL], 0x0E0E0E0);
				pixel_put_img(img, WIDTH_EX - 2, c[COL], 0x0E0E0E0);
			}
			c[COL]++;
		}
	}
}

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
	// start = y;
	// while (y < HEIGHT)
	// {
	// 	x = WIDTH;
	// 	if (y <= start + 10 || y >= HEIGHT - 10)
	// 	{
	// 		if (!(y >= HEIGHT - 6 && y <= HEIGHT - 5) && !(y <= start + 6 && y >= start + 5))
	// 		{
	// 			while (x < WIDTH_EX)
	// 			{
	// 				if (!(y > start + 6 && y < HEIGHT - 6 && x >= WIDTH + 1 && x < WIDTH + 4)
	// 				 && !(y > start + 6 && y < HEIGHT - 6 && x <= WIDTH_EX - 1 && x > WIDTH_EX - 4))
	// 					pixel_put_img(&img, x, y, 0x0E0E0E0);
	// 				x++;
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		for (int i = 0; i < 6; i++)
	// 		{
	// 			if (i < 1 || i > 3)
	// 				pixel_put_img(&img, x + i, y, 0x0E0E0E0);
	// 		}
	// 		for (int i = 0; i < 6; i++)
	// 		{
	// 			if (i < 1 || i > 3)
	// 				pixel_put_img(&img, WIDTH_EX - i, y, 0x0E0E0E0);
	// 		}
	// 	}
	// 	y++;
	// }
	if (data->selectp == -1)
		selected_box_statute_to_window(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.ptr, 0, 0);
}

/*
* [helper function of put_elements_to_window]
* [put diameter and height of elements to window]
TODO write ft_floattoa and use insteant ft_itoa.
*/
int	put_size_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		colour;

	colour = color_to_int(ato_tcolor("244,244,244"));
	pointer2 = ft_itoa(object->size.h);
	if (object->type != PLANE)
		pointer1 = ft_strjoin("|HEIGHT:   ", pointer2);
	else
		pointer1 = ft_strjoin("|HEIGHT:   NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	line += 11;
	pointer2 = ft_itoa(object->size.w);
	if (object->type != PLANE)
		pointer1 = ft_strjoin("|DIAMETER: ", pointer2);
	else
		pointer1 = ft_strjoin("|DIAMETER: NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	return (line += 17);
}

/*
* [helper function of put_object_to_window]
* INDEX mode : cordition of index, add 0 to index until get 4 digit [0000].
* TYPE mode : cordition of type, join string with object's type.
*/
static char	*object_cordition_str(t_obj *object, char *string, int mode)
{
	if (mode == INDEX)
	{
		if (object->idx < 10)
			return (ft_strjoin("[000", string));
		else if (object->idx < 100)
			return (ft_strjoin("[00", string));
		else if (object->idx < 1000)
			return (ft_strjoin("[0", string));
		else
			return (ft_strjoin("[", string));
	}
	else if (mode == TYPE)
	{
		if (object->type == SPHERE)
			return (ft_strjoin("[ ]SPHERE", string));
		else if (object->type == PLANE)
			return (ft_strjoin("[ ]PLANE", string));
		else if (object->type == CYLIND)
			return (ft_strjoin("[ ]CYINDER", string));
		else if (object->type == CONE)
			return (ft_strjoin("[ ]CONE", string));
	}
	return (NULL);
}

/*
* [helper function of put_elements_to_window]
* [put type and index of elements to window]
*/
int	put_object_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		colour;

	colour = rgb_to_int(244, 244, 244);
	pointer1 = ft_itoa(object->idx);
	pointer2 = object_cordition_str(object, pointer1, INDEX);
	if (!pointer2)
		exit_error(FAIL_ALLOC);
	free(pointer1);
	pointer1 = object_cordition_str(object, pointer2, TYPE);
	if (!pointer1)
		exit_error(FAIL_ALLOC);
	free(pointer2);
	pointer2 = ft_strjoin(pointer1, "]");
	free(pointer1);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer2);
	free(pointer2);
	return (line + 11);
}

/*
* [helper function of put_elements_to_window]
* [put coordinates of elements to window]
TODO write ft_floattoa and use insteant ft_itoa.
*/
int	put_coordinates_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		count;

	count = 0;
	mlx_string_put(data->mlx, data->win, WIDTH, line, 0xE0E0E0, "|COORDINATES:");
	while (count < 3)
	{
		line += 11;
		if (count == 0)
			pointer1 = ft_strjoin("||X-[", ft_itoa(object->pos.x));
		else if (count == 1)
			pointer1 = ft_strjoin("||Y-[", ft_itoa(object->pos.y));
		else
			pointer1 = ft_strjoin("||Z-[", ft_itoa(object->pos.z));
		pointer2 = ft_strjoin(pointer1, "]");
		free(pointer1);
		mlx_string_put(data->mlx, data->win, WIDTH, line, 0xE0E0E0, pointer2);
		free(pointer2);
		count++;
	}
	return (line + 11);
}

/*
* [helper function of put_elements_to_window]
* [put none elements to window]
*/
static int	put_none_to_window(t_data *data, int line)
{
	int color;

	color = rgb_to_int(255, 255, 255);
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "[X]NONE[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "|COORDINATES:");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "||X-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "||Y-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "||Z-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "|HEIGHT:   NONE");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, color, "|DIAMETER: NONE");
	line += 17;
	return (line);
}

/*
* [function put elements identifier from data to window by put_string]
* line will start at 40.
* each line for a chracter is 11.
*/
void	put_elements_to_window(t_data *data, t_list *objects)
{
	int		count;
	// t_list	*objects;
	t_obj	*object;
	int		line;

	count = 0;
	line = 40;
	mlx_string_put(data->mlx, data->win, WIDTH + 1, 18,
		 0xE0E0E0, "[ELEMENTS-IDENTIFIER]");
	// objects = data->objs;
	while (count < 5)
	{
		if (objects)
		{
			object = objects->content;
			line = put_object_to_window(data, object, line);
			line = put_coordinates_to_window(data, object, line);
			line = put_size_to_window(data, object, line);
			objects = objects->next;
		}
		else
			line = put_none_to_window(data, line);
		count++;
	}
}
// * add 3 2 1 0
void	selecttion_to_window(t_data *data)
{
	char 	*pointer1;
	char	*pointer2;
	char	*pointer3;
	// int		select;
	int		count;
	int		colour;

	// select = 0;
	count = 0;
	colour = rgb_to_int(224, 224, 224);
	// while (count < 4)
	// 	select = (select * 10) + data->selectv[count++];
	if (data->selectp < 0)
	{
		count = 0;
		pointer2 = ft_itoa(data->selectv[count++]);
		pointer1 = ft_strjoin("[SELECTED]:[", pointer2);
		free(pointer2);
		while (count < 4)
		{
			pointer3 = ft_itoa(data->selectv[count++]);
			pointer2 = ft_strjoin_pro(pointer1, pointer3);
			pointer1 = pointer2;
		}
		pointer2 = ft_strjoin(pointer1, "][ ]");
		free(pointer1);
		pointer1 = pointer2;
		// mlx_string_put(data->mlx, data->win, WIDTH + 5, HEIGHT - 13, colour, pointer1);
		// free(pointer1);
	}
	else
	{
		// * selectv = position to add []
		count = 0;
		pointer2 = ft_itoa(data->selectv[count++]);
		if (data->selectp == 0)
		{
			pointer1 = ft_strjoin("[SELECTIN]:[", pointer2);
			pointer3 = ft_strjoin(pointer1, "]");
			free(pointer1);
			pointer1 = pointer3;
		}
		else
			pointer1 = ft_strjoin("[SELECTIN]:", pointer2);
		free(pointer2);

		while (count < 4)
		{
			pointer3 = ft_itoa(data->selectv[count++]);
			if (data->selectp == count - 1)
			{
				pointer2 = ft_strjoin(pointer1, "[");
				free(pointer1);
				pointer1 = ft_strjoin_pro(pointer2, pointer3);
				pointer2 = ft_strjoin(pointer1, "]");
				free(pointer1);
			}
			else
				pointer2 =ft_strjoin_pro(pointer1, pointer3);
			pointer1 = pointer2;
		}
		pointer2 = ft_strjoin(pointer1, "[ ]");
		free(pointer1);
		pointer1 = pointer2;
	}
	mlx_string_put(data->mlx, data->win, WIDTH + 5, HEIGHT - 13, colour, pointer1);
	free(pointer1);
}

void	window_interface(t_data *data, int mode)
{
	int			count;
	t_list		*objects;
	t_obj		*object;
	int			colour[5];
	int			index;
	static int	first = 0;

	count = 0;
	index = 0;
	if (mode == INCREASE && ft_lstsize(data->objs) - (first + 5) > 0)
		first += 5;
	else if (mode == DECREASE && first >= 5)
		first -= 5;
	// * add static int about counting range of objects.
	objects = data->objs;
	while (objects && count < first + 5)
	{
		object = objects->content;
		if (count >= first)
			colour[index++] = color_to_int(object->color);
		count++;
		objects = objects->next;
	}
	count = 0;
	objects = data->objs;
	while (objects && count < first)
	{
		object = objects->content;
		objects = objects->next;
		count++;
	}
	put_template_to_window(data, index, colour);
	put_elements_to_window(data, objects);
	selecttion_to_window(data);

	// mlx_string_put(data->mlx, data->win, WIDTH + 5, HEIGHT - 13, 0xE0E0E0, "[SELECTED]:[0000][ ]");
}