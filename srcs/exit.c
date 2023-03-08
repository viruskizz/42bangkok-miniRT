/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:14:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/08 22:14:49 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_exit(t_data *data, int code)
{
	if (code == ERROR_MLX)
	{
		printf("Error: MLX lib cannot operation\n");
		free(data->mlx);
	}
	else if (code == ERROR_WIN)
	{
		printf("Error: MLX WIN lib cannot operation\n");
		free(data->mlx);
		free(data->win);
	}
	return (1);
}

int	rt_close(t_data *data, int code)
{
	printf("Exit program\n");
	if (IS_LINUX)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		// mlx_destroy_display(data->mlx);
	}
	exit(code);
}
