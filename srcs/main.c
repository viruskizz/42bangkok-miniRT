/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:31:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 00:43:47 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initial(t_data *data);
static int	render(t_data *data);
t_obj	*set_plain_img(t_data *data, t_obj *obj);

int main(int argc, char **argv)
{
	t_data	data;
	char *filename;

	data = parsing_input(argc, argv);
	print_tdata(&data);
	initial(&data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 1L << 0, &rt_close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

static void	initial(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, ERROR_MLX);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		error_exit(data, ERROR_WIN);
	// t_img	img;
	// img.img = mlx_new_image(data->mlx, data->w, data->h);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.lh, &img.endian);
	// data->scene.img = img;
	// data->scene.img.img = mlx_new_image(data->mlx, data->w, data->h);
	data->scene.color.r = 128;
	data->scene.color.g = 128;
	data->scene.color.b = 128;
	data->scene.pos.x = 0;
	data->scene.pos.y = 0;
	data->scene = *set_plain_img(data, &data->scene);
}

static int	render(t_data *data)
{
	// render_objects(data);
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.img, 0, 0);
	return (0);
}

// static int	render(t_data *data)
// {
// 	int width = data->w;
// 	int height = data->h;
// 	t_ray	camray;
// 	t_vtr	inter_point;
// 	t_vtr	local_normal;
// 	t_vtr	local_color;
// 	double x_fact = 1.0 / ((double)data->w / 2.0);
// 	double y_fact = 1.0 / ((double)data->h / 2.0);
// 	double min_d = 1e6;
// 	double max_d = 0.0;
// 	int	x = 0;
// 	int	y = 0;
// 	// if (data->scene.img.img)
// 	// 	mlx_destroy_image(data->mlx, data->scene.img.img);
// 	while (y < data->h)
// 	{
// 		while (x < data->w)
// 		{
// 			// normalize the x and y coordinates
// 			// printf("fact: %f, %f\n", x_fact, y_fact);
// 			double norm_x = ((double) x * x_fact) - 1.0;
// 			double norm_y = ((double) y * y_fact) - 1.0;
// 			// printf("norm: %f, %f\n", norm_x, norm_y);
// 			camray = raygen(data->cam, norm_x, norm_y);
// 			int inter = sphere_inter(camray);
// 			int color;
// 			if (inter)
// 			{
// 				color = rgb_to_int(255, 0, 0);
// 			}
// 			else
// 			{
// 				color = rgb_to_int(255, 0, 0);
// 			}
// 			pixel_put_img(&data->scene.img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.img, 10, 10);
// 	return (0);
// }

// t_obj	*set_plain_img(t_data *data, t_obj *obj)
// {
// 	double	x;
// 	double	y;
// 	int		color;

// 	obj->img.img = mlx_new_image(data->mlx, obj->size.w, obj->size.h);
// 	obj->img.addr = mlx_get_data_addr(obj->img.img, &obj->img.bpp, &obj->img.lh, &obj->img.endian);
// 	y = 0;
// 	while (y < obj->size.h)
// 	{
// 		x = 0;
// 		while(x < obj->size.w)
// 		{
// 			color = rgb_to_int(obj->color.r, obj->color.g, obj->color.b);
// 			pixel_put_img(&obj->img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (obj);
// }
