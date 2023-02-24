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
	// mlx_loop_hook(data.mlx, &render, &data);
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
	data->w = WIDTH;
	data->h = HEIGHT;
	data->scene.color.r = 255;
	data->scene.color.g = 255;
	data->scene.color.b = 255;
	data->scene.pos.x = 0;
	data->scene.pos.y = 0;
	data->scene.size.w = data->w;
	data->scene.size.h = data->h;
	set_plain_img(data, &data->scene);
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	render(data);
}

// static int	render(t_data *data)
// {
// 	render_objects(data);
// 	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.img, 0, 0);
// 	return (0);
// }

static int	render(t_data *data)
{
	int width = data->w;
	int height = data->h;
	t_ray	camray;
	t_vtr	ivtr;
	t_vtr	local_normal;
	t_vtr	local_color;
	double x_fact = 1.0 / ((double)data->w / 2.0);
	double y_fact = 1.0 / ((double)data->h / 2.0);
	double mind = 1e6;
	double maxd = 0.0;
	int	x = 0;
	int	y = 0;
	if (data->scene.img.ptr)
		mlx_destroy_image(data->mlx, data->scene.img.ptr);
	data->scene.img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->scene.img.addr = mlx_get_data_addr(data->scene.img.ptr, &data->scene.img.bpp, &data->scene.img.lh, &data->scene.img.endian);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// normalize the x and y coordinates
			// printf("fact: %f, %f\n", x_fact, y_fact);
			double norm_x = ((double) x * x_fact) - 1.0;
			double norm_y = ((double) y * y_fact) - 1.0;
			camray = raygen(data->cam, norm_x, norm_y);
			int inter = sphere_inter(camray, &ivtr);
			if (inter == 1)
				printf("%f,%f,%f = %d\n", ivtr.x, ivtr.y, ivtr.z, inter);
			int color;
			if (inter)
			{
				double d = vtrmag(vtrsub(ivtr, camray.a));
				if (d > maxd)
					maxd = d;
				if (d < mind)
					mind = d;
				int r = 255.0 - ((d - 9.0) / 0.94605 * 255.0);
				color = rgb_to_int(r, 0, 0);
			}
			else
			{
				color = rgb_to_int(0, 0, 0);
			}
			pixel_put_img(&data->scene.img, x, y, color);
			x++;
		}
		y++;
	}
	printf("min/max = %f/%f", mind, maxd);
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}
