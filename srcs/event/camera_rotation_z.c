/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation_z.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:31:24 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/25 01:46:13 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	increase_norm_to_one(t_data *data, int keycode);
static int	norm_value_z(t_data *data, int keycode, int update);
static void	helper_cordition(t_data *data, int keycode);

int	camera_rotation_z(t_data *data, int keycode)
{
	int		c;
	float	norm[3];

	c = 0;
	norm[X] = data->cam.norm.x;
	norm[Y] = data->cam.norm.y;
	if ((data->lshift_key && data->ctrl_key)
		&& (keycode == KEY_RIGHT || keycode == KEY_LEFT))
	{
		if ((keycode == KEY_RIGHT && norm[Y] == 1 && norm[X] < 1 && !c++)
			|| (keycode == KEY_LEFT && norm[Y] == -1 && norm[X] < 1 && !c++))
			data->cam.norm.x += TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[Y] > -1 && norm[X] == 1 && !c++)
			|| (keycode == KEY_LEFT && norm[X] == -1 && norm[Y] > -1 && !c++))
			data->cam.norm.y -= TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[Y] == -1 && norm[X] > -1 && !c++)
			|| (keycode == KEY_LEFT && norm[Y] == 1 && norm[X] > -1 && !c++))
			data->cam.norm.x -= TRANSF_VALUE;
		else if ((keycode == KEY_RIGHT && norm[X] == -1 && norm[Y] < 1 && !c++)
			|| (keycode == KEY_LEFT && norm[X] == 1 && norm[Y] < 1 && !c++))
			data->cam.norm.y += TRANSF_VALUE;
		else if (!c++)
			increase_norm_to_one(data, keycode);
	}
	return (norm_value_z(data, keycode, c));
}

static void	increase_norm_to_one(t_data *data, int keycode)
{
	if (keycode == KEY_RIGHT)
	{
		if (data->cam.norm.x > 0 && data->cam.norm.y < 0)
			data->cam.norm.x += TRANSF_VALUE;
		else if (data->cam.norm.x > 0 && data->cam.norm.y > 0)
			data->cam.norm.y -= TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.y > 0)
			data->cam.norm.x -= TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.y < 0)
			data->cam.norm.y += TRANSF_VALUE;
	}
	else if (keycode == KEY_LEFT)
	{
		if (data->cam.norm.x > 0 && data->cam.norm.y < 0)
			data->cam.norm.y += TRANSF_VALUE;
		else if (data->cam.norm.x > 0 && data->cam.norm.y > 0)
			data->cam.norm.x += TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.y > 0)
			data->cam.norm.y -= TRANSF_VALUE;
		else if (data->cam.norm.x < 0 && data->cam.norm.y < 0)
			data->cam.norm.x -= TRANSF_VALUE;
	}
}

int	norm_value_z(t_data *data, int keycode, int update)
{
	if (data->cam.norm.y > 1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.x -= data->cam.norm.y - 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.x += data->cam.norm.y - 1;
		data->cam.norm.y = 1;
	}
	else if (data->cam.norm.y < -1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.x -= data->cam.norm.y + 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.x += data->cam.norm.y + 1;
		data->cam.norm.y = -1;
	}
	else
		helper_cordition(data, keycode);
	return (update);
}

static void	helper_cordition(t_data *data, int keycode)
{
	if (data->cam.norm.x > 1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.y += data->cam.norm.x - 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.y -= data->cam.norm.x - 1;
		data->cam.norm.x = 1;
	}
	else if (data->cam.norm.x < -1)
	{
		if (keycode == KEY_LEFT)
			data->cam.norm.y += data->cam.norm.x + 1;
		else if (keycode == KEY_RIGHT)
			data->cam.norm.y -= data->cam.norm.x + 1;
		data->cam.norm.x = -1;
	}
}
