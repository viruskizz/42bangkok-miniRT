/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:31:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/24 19:39:38 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

static void	initial(t_data *data, char *filename);
static int	render(t_data *data);

int main(int argc, char **argv)
{
	t_data	*data;

	data = parsing_input(argc, argv);
	return (EXIT_SUCCESS);
}

static void	initial(t_data *data, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, ERROR_MLX);
	rt_setup(data, filename);
	data->win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "miniRT");
	if (!data->win)
		error_exit(data, ERROR_WIN);
}

static int	render(t_data *data)
{
	// if (data->frame == FRAME_RATE)
	// 	data->frame = 0;
	// else
	// 	data->frame += 1;
	render_objects(data);
	return (0);
}
