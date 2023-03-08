/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:24 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 00:36:07 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_setup(t_data *data, char *filename)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->frame = 0;
	data->objs = NULL;
	set_objs(data);
	return (0);
}
