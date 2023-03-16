/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:31:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 06:23:29 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initial(t_data *data);
static int	render(t_data *data);
t_obj		*set_plain_img(t_data *data, t_obj *obj);
int			keyhandler_press(int keycode, t_data *data);
int			keyhandler_release(int keycode, t_data *data);
void		draw_square(t_data *data, int width, int height, int start);

int	main(int argc, char **argv)
{
	t_data	data;
	char	*filename;

	data = parsing_input(argc, argv);
	// print_tdata(&data);
	initial(&data);
	render_scene(&data);
	window_interface(&data, NONE);
	// mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 1L << 0, &rt_close, &data);
	mlx_hook(data.win, 2, 1L << 0, &keyhandler_press, &data);
	mlx_hook(data.win, 3, 1L << 1, &keyhandler_release, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

static void	initial(t_data *data)
{
	int	count;

	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, ERROR_MLX);
	data->win = mlx_new_window(data->mlx, WIDTH_EX, HEIGHT, "miniRT");
	if (!data->win)
		error_exit(data, ERROR_WIN);
	scene_initialise(data);
	data->ctrl_key = 0;
	data->rshift_key = 0;
	data->lshift_key = 0;
	data->selectp = -1;
	count = 0;
	while (count < 4)
		data->selectv[count++] = 0;
}
