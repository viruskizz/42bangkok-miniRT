/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:14:47 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:05:56 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_setup(t_data *data)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->update = 0;
	data->objs = NULL;
	set_objs(data);
	return (0);
}
