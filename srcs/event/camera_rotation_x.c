/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:48:34 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 05:45:55 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	increase_norm_to_one(t_data *data, int keycode);
static int	norm_value_x(t_data *data, int keycode, int update);
static void	helper_cordition(t_data *data, int keycode);

int	camera_rotation_x(t_data *data, int keycode)
{
	int		c;
	float	norm[3];

	c = 0;
	norm[Y] = data->cam.norm.y;
	norm[Z] = data->cam.norm.z;
	if ((!data->lshift_key && data->ctrl_key)
		&& (keycode == KEY_UP || keycode == KEY_DOWN))
	{
		if ((keycode == KEY_UP && norm[Z] == -1 && norm[Y] > -1 && !c++)
			|| (keycode == KEY_DOWN && norm[Z] == 1 && norm[Y] > -1 && !c++))
			data->cam.norm.y -= TRANSF_VALUE;
		else if ((keycode == KEY_UP && norm[Z] < 1 && norm[Y] == -1 && !c++)
			|| (keycode == KEY_DOWN && norm[Y] == 1 && norm[Z] < 1 && !c++))
			data->cam.norm.z += TRANSF_VALUE;
		else if ((keycode == KEY_UP && norm[Z] == 1 && norm[Y] < 1 && !c++)
			|| (keycode == KEY_DOWN && norm[Z] == -1 && norm[Y] < 1 && !c++))
			data->cam.norm.y += TRANSF_VALUE;
		else if ((keycode == KEY_UP && norm[Y] == 1 && norm[Z] > -1 && !c++)
			|| (keycode == KEY_DOWN && norm[Y] == -1 && norm[Z] > -1 && !c++))
				data->cam.norm.z -= TRANSF_VALUE;
		else if (!c++)
			increase_norm_to_one(data, keycode);
	}
	return (norm_value_x(data, keycode, c));
}

static void	increase_norm_to_one(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
	{
		if (data->cam.norm.y <= 0 && data->cam.norm.z < 0)
			data->cam.norm.y -= TRANSF_VALUE;
		else if (data->cam.norm.y < 0 && data->cam.norm.z >= 0)
			data->cam.norm.z += TRANSF_VALUE;
		else if (data->cam.norm.y >= 0 && data->cam.norm.z > 0)
			data->cam.norm.y += TRANSF_VALUE;
		else if (data->cam.norm.y > 0 && data->cam.norm.z <= 0)
			data->cam.norm.z -= TRANSF_VALUE;
	}
	else if (keycode == KEY_DOWN)
	{
		if (data->cam.norm.y <= 0 && data->cam.norm.z < 0)
			data->cam.norm.z -= TRANSF_VALUE;
		else if (data->cam.norm.y < 0 && data->cam.norm.z >= 0)
			data->cam.norm.y -= TRANSF_VALUE;
		else if (data->cam.norm.y >= 0 && data->cam.norm.z > 0)
			data->cam.norm.z += TRANSF_VALUE;
		else if (data->cam.norm.y > 0 && data->cam.norm.z <= 0)
			data->cam.norm.y += TRANSF_VALUE;
	}
}

static int	norm_value_x(t_data *data, int keycode, int update)
{
	if (update)
	{
		if (data->cam.norm.y > 1)
		{
			if (keycode == KEY_DOWN)
				data->cam.norm.z += data->cam.norm.y - 1;
			else if (keycode == KEY_UP)
				data->cam.norm.z -= data->cam.norm.y - 1;
			data->cam.norm.y = 1;
		}
		else if (data->cam.norm.y < -1)
		{
			if (keycode == KEY_DOWN)
				data->cam.norm.z += data->cam.norm.y + 1;
			else if (keycode == KEY_UP)
				data->cam.norm.z -= data->cam.norm.y + 1;
			data->cam.norm.y = -1;
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
		if (keycode == KEY_DOWN)
			data->cam.norm.y -= data->cam.norm.z - 1;
		else if (keycode == KEY_UP)
			data->cam.norm.y += data->cam.norm.z - 1;
		data->cam.norm.z = 1;
	}
	else if (data->cam.norm.z < -1)
	{
		if (keycode == KEY_DOWN)
			data->cam.norm.y -= data->cam.norm.z + 1;
		else if (keycode == KEY_UP)
			data->cam.norm.y += data->cam.norm.z + 1;
		data->cam.norm.z = -1;
	}
}
