/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation_y.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:48:28 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/25 01:55:40 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	increase_norm_to_one(t_data *data, int keycode);
static int	norm_value_y(t_data *data, int keycode, int update);
static void	helper_cordition(t_data *data, int keycode);

int	camera_rotation_y(t_data *data, int keycode)
{
	int		c;
	float	norm[3];

	c = 0;
	norm[X] = data->cam.norm.x;
	norm[Z] = data->cam.norm.z;
	if ((!data->lshift_key && data->ctrl_key)
		&& (keycode == KEY_RIGHT || keycode == KEY_LEFT))
	{
		if ((keycode == KEY_RIGHT && norm[Z] == -1 && norm[X] < 1 && !c++)
			|| (keycode == KEY_LEFT && norm[Z] == 1 && norm[X] < 1 && !c++))
			data->cam.norm.x += TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[Z] < 1 && norm[X] == 1 && !c++)
			|| (keycode == KEY_LEFT && norm[X] == -1 && norm[Z] < 1 && !c++))
			data->cam.norm.z += TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[Z] == 1 && norm[X] > -1 && !c++)
			|| (keycode == KEY_LEFT && norm[Z] == -1 && norm[X] > -1 && !c++))
			data->cam.norm.x -= TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[X] == -1 && norm[Z] > -1 && !c++)
			|| (keycode == KEY_LEFT && norm[X] == 1 && norm[Z] > -1 && !c++))
			data->cam.norm.z -= TRANSF_VALUE;
		else if (!c++)
			increase_norm_to_one(data, keycode);
	}
	return (norm_value_y(data, keycode, c));
}

static void	increase_norm_to_one(t_data *data, int keycode)
{
	if (keycode == KEY_RIGHT)
	{
		if (data->cam.norm.x >= 0 && data->cam.norm.z < 0)
			data->cam.norm.x += TRANSF_VALUE;
		else if (data->cam.norm.x > 0 && data->cam.norm.z >= 0)
			data->cam.norm.z += TRANSF_VALUE;
		else if (data->cam.norm.x <= 0 && data->cam.norm.z > 0)
			data->cam.norm.x -= TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.z <= 0)
			data->cam.norm.z -= TRANSF_VALUE;
	}
	else if (keycode == KEY_LEFT)
	{
		if (data->cam.norm.x >= 0 && data->cam.norm.z < 0)
			data->cam.norm.z -= TRANSF_VALUE;
		else if (data->cam.norm.x > 0 && data->cam.norm.z >= 0)
			data->cam.norm.x += TRANSF_VALUE;
		else if (data->cam.norm.x <= 0 && data->cam.norm.z > 0)
			data->cam.norm.z += TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.z <= 0)
			data->cam.norm.x -= TRANSF_VALUE;
	}
}

static int	norm_value_y(t_data *data, int keycode, int update)
{
	if (update)
	{
		if (data->cam.norm.x > 1)
		{
			if (keycode == KEY_LEFT)
				data->cam.norm.z -= data->cam.norm.x - 1;
			else if (keycode == KEY_RIGHT)
				data->cam.norm.z += data->cam.norm.x - 1;
			data->cam.norm.x = 1;
		}
		else if (data->cam.norm.x < -1)
		{
			if (keycode == KEY_LEFT)
				data->cam.norm.z -= data->cam.norm.x + 1;
			else if (keycode == KEY_RIGHT)
				data->cam.norm.z += data->cam.norm.x + 1;
			data->cam.norm.x = -1;
		}
		else
			helper_cordition(data, keycode);
	}
	return (update);
}

static void	helper_cordition(t_data *data, int keycode)
{
	if (data->cam.norm.z > 1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.x += data->cam.norm.z - 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.x -= data->cam.norm.z - 1;
		data->cam.norm.z = 1;
	}
	else if (data->cam.norm.z < -1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.x += data->cam.norm.z + 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.x -= data->cam.norm.z + 1;
		data->cam.norm.z = -1;
	}
}
