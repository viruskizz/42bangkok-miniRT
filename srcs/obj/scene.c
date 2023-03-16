/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:36:07 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/17 03:13:31 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_initialise(t_data *data)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->scene.color.r = 0;
	data->scene.color.g = 0;
	data->scene.color.b = 0;
	data->scene.pos.x = data->w / 2.0;
	data->scene.pos.y = data->h / 2.0;
	data->scene.size.w = data->w;
	data->scene.size.h = data->h;
	set_plane_img(data, &data->scene);
}
