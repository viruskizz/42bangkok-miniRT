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
	// mlx_hook(data.win, X_EVENT_KEY_EXIT, 1L << 0, &rt_close, &data);
	// mlx_loop(data.mlx);
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
	scene_initialise(data);
	// render_scene(data);
	// float m[3][3] = {
	// 	{1.0, 2.0, 3.0},
	// 	{4.0, 5.0, 6.0},
	// 	{7.0, 8.0, 9.0},
	// };
	float **m3 = mtx_identity(3);
	m3[0][0] = 9;
	m3[0][1] = 8;
	m3[0][2] = 7;
	m3[1][0] = 1;
	m3[1][1] = 4;
	m3[1][2] = 6;
	m3[2][0] = 2;
	m3[2][1] = 8;
	m3[2][2] = 3;
	mtx_print(m3, 3);
	float **m3i = mtx_inverse(m3, 3);
	mtx_print(m3i, 3);
	float **m4 = mtx_identity(4);
	m4[0][0] = 1;
	m4[0][1] = 9;
	m4[0][2] = 3;
	m4[0][3] = 9;
	m4[1][0] = 5;
	m4[1][1] = 6;
	m4[1][2] = 7;
	m4[1][3] = 8;
	m4[2][0] = 12;
	m4[2][1] = 11;
	m4[2][2] = 10;
	m4[2][3] = 9;
	m4[3][0] = 13;
	m4[3][1] = 9;
	m4[3][2] = 15;
	m4[3][3] = 9;
	mtx_print(m4, 4);
	float **m4i = mtx_inverse(m4, 3);
	mtx_print(m4i, 3);
	// float **mm = mtx_sub(m, 4, 0, 0);
	// printf("sub matrix\n");
	// mtx_print(mm, 3);
	// float **m3 = mtx_identity(3);
	// m3[0][0] = 9;
	// m3[0][1] = 2;
	// m3[0][2] = 3;
	// m3[1][0] = 6;
	// m3[1][1] = 5;
	// m3[1][2] = 4;
	// m3[2][0] = 8;
	// m3[2][1] = 9;
	// m3[2][2] = 10;
	// float det = mtx_det(m3, 3);
	// mtx_print(m3, 3);
	// printf("det = %f\n", det);
}
