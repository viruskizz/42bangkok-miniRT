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
	scene_initialise(data);
	render_scene(data);
}
