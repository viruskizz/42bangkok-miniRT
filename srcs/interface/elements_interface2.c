/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_interface2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:05:41 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 01:20:18 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [helper function of put_elements_to_window]
* [put diameter and height of elements to window]
*/
int	put_size_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		colour;

	colour = color_to_int(ato_tcolor("244,244,244"));
	pointer2 = ft_floattoa(object->size.h);
	if (object->type != PLANE && object->type != LIGHT)
		pointer1 = ft_strjoin("|HEIGHT:   ", pointer2);
	else
		pointer1 = ft_strjoin("|HEIGHT:   NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	line += 11;
	pointer2 = ft_floattoa(object->size.w);
	if (object->type != PLANE && object->type != LIGHT)
		pointer1 = ft_strjoin("|DIAMETER: ", pointer2);
	else
		pointer1 = ft_strjoin("|DIAMETER: NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	return (line += 17);
}

/*
* [helper function of put_elements_to_window]
* [put none elements to window]
*/
int	put_none_to_window(t_data *data, int line)
{
	int	colour;

	colour = rgb_to_int(255, 255, 255);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|[X]NONE[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|COORDINATES:");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||X-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||Y-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||Z-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line,
		colour, "|HEIGHT:   NONE");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour,
		"|DIAMETER: NONE");
	line += 17;
	return (line);
}
