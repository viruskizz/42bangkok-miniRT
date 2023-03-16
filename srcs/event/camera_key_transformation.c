/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_key_transformation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:45:52 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/17 01:29:16 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rotation_key_check(t_data *data, int keycode);
static void	moving_key_check(t_data *data, int keycode);

void	camera_key_transformation(t_data *data, int keycode)
{
	if (!rotation_key_check(data, keycode))
		moving_key_check(data, keycode);
	// if (data->ctrl_key && data->rshift_key && keycode == KEY_RIGHT)
	// {
	// 	// * rotate camera right along z-axis.
	// 	printf("change up?? 1\n");
	// 	// data->cam.pos.z += 1;
	// }
	// else if (data->ctrl_key && data->rshift_key && keycode == KEY_LEFT)
	// {
	// 	// * rotate camera left along z-axis.
	// 	printf("change up?? 2\n");
	// 	// data->cam.pos.z -= 1;
	// }
	// else if (data->ctrl_key && keycode == KEY_RIGHT)
	// {
	// 	// * rotate camera right.
	// 	data->cam.lookat.x += 1;
	// 	if (data->cam.lookat.x > 180)
	// 		data->cam.lookat.x = -180; 
	// 	// data->cam.pos.x += position_value;
	// }
	// else if (data->ctrl_key && keycode == KEY_LEFT)
	// {
	// 	// * rotate camera left.
	// 	data->cam.lookat.x -= TRANSF_VALUE;
	// }
	// else if (data->ctrl_key && keycode == KEY_UP)
	// {
	// 	// * rotate camera up.
	// 	data->cam.lookat.y -= TRANSF_VALUE;
	// }
	// else if (data->ctrl_key && keycode == KEY_DOWN)
	// {
	// 	// * rotate camera down
	// 	data->cam.lookat.y += TRANSF_VALUE;
	// }
	// *
	// else if (data->shift_key && keycode == KEY_UP)
	// {
	// 	// * move camera forward.
	// 	data->cam.pos.z -= 1;
	// }
	// else if (data->shift_key && keycode == KEY_DOWN)
	// {
	// 	// * move camera backward.
	// 	data->cam.pos.z += 1;
	// }
	// else if (keycode == KEY_RIGHT)
	// {
	// 	// * move camera right.
	// 	data->cam.pos.x += TRANSF_VALUE;
	// 	data->cam.lookat.x += TRANSF_VALUE;
	// }
	// else if (keycode == KEY_LEFT)
	// {
	// 	// * move camera left.
	// 	data->cam.pos.x -= TRANSF_VALUE;
	// 	data->cam.lookat.x -= TRANSF_VALUE;
	// }
	// else if (keycode == KEY_UP)
	// {
	// 	// * move camera up.
	// 	data->cam.pos.y -= TRANSF_VALUE;
	// 	data->cam.lookat.y -= TRANSF_VALUE;
	// }
	// else if (keycode == KEY_DOWN)
	// {
	// 	// * move camera down
	// 	data->cam.pos.y += TRANSF_VALUE;
	// 	data->cam.lookat.y += TRANSF_VALUE;
	// }
}

static int	rotation_key_check(t_data *data, int keycode)
{
	int check;

	check = 0;
	if (data->ctrl_key && data->rshift_key && keycode == KEY_RIGHT && !check++)
	{
		// * rotate camera right along z-axis.
		printf("change up?? 1\n");
		// data->cam.pos.z += 1;
	}
	else if (data->ctrl_key && data->rshift_key && keycode == KEY_LEFT && !check++)
	{
		// * rotate camera left along z-axis.
		printf("change up?? 2\n");
		// data->cam.pos.z -= 1;
	}
	else if (data->ctrl_key && keycode == KEY_RIGHT && !check++)
	{
		// * rotate camera right.
		data->cam.lookat.x += TRANSF_VALUE;
		if (data->cam.lookat.x > 180)
			data->cam.lookat.x = -180; 
		// data->cam.pos.x += position_value;
	}
	else if (data->ctrl_key && keycode == KEY_LEFT && !check++)
		data->cam.lookat.x -= TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_UP && !check++)
		data->cam.lookat.y -= TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_DOWN && !check++)
		data->cam.lookat.y += TRANSF_VALUE;
	return (check);
}

static void	moving_key_check(t_data *data, int keycode)
{
	if (data->lshift_key && keycode == KEY_UP)
	{
		// * move camera forward.
		data->cam.pos.z -= 1;
	}
	else if (data->lshift_key && keycode == KEY_DOWN)
	{
		// * move camera backward.
		data->cam.pos.z += 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		// * move camera right.
		data->cam.pos.x += TRANSF_VALUE;
		data->cam.lookat.x += TRANSF_VALUE;
	}
	else if (keycode == KEY_LEFT)
	{
		// * move camera left.
		data->cam.pos.x -= TRANSF_VALUE;
		data->cam.lookat.x -= TRANSF_VALUE;
	}
	else if (keycode == KEY_UP)
	{
		// * move camera up.
		data->cam.pos.y -= TRANSF_VALUE;
		data->cam.lookat.y -= TRANSF_VALUE;
	}
	else if (keycode == KEY_DOWN)
	{
		// * move camera down
		data->cam.pos.y += TRANSF_VALUE;
		data->cam.lookat.y += TRANSF_VALUE;
	}
}
