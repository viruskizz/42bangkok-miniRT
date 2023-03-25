/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:27:50 by tsomsa            #+#    #+#             */
/*   Updated: 2023/03/26 02:18:53 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	txtr_checker_colorf(t_vtr uvz, float **mtrans)
{
	t_vtr	couv;
	int		pos;

	couv = txtr_vtr(uvz, mtrans);
	pos = ((int) floorf(couv.x)) + ((int) floorf(couv.y));
	if (pos % 2 == 0)
		return (colorf_set(1.0, 1.0, 1.0));
	else
		return (colorf_set(1, 0, 0));
}

/*
 * Start testing
 * c[ROW] = y;
 * c[COL] = x;
*/
t_img	txtr_checker_test(t_data *data)
{
	t_img		img;
	t_vtr		uvz;
	t_colorf	cf;
	float		**txt_mtx;
	int			c[2];

	txt_mtx = txtr_mtx_trans(vtrset(0, 0, 0), PI / 4, vtrset(4, 4, 0));
	mtx_print(txt_mtx, 3);
	img.ptr = mlx_new_image(data->mlx, (int) WIDTH, (int) HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	c[ROW] = -1;
	while (++c[ROW] < HEIGHT)
	{
		c[COL] = -1;
		while (++c[COL] < WIDTH)
		{
			uvz.x = ((float) c[COL] / ((float) WIDTH / 2.0)) - 1.0;
			uvz.y = ((float) c[ROW] / ((float) HEIGHT / 2.0)) - 1.0;
			uvz.z = 0;
			cf = txtr_checker_colorf(uvz, txt_mtx);
			pixel_put_img(&img, c[COL], c[ROW],
				color_to_int(colorf_to_color(cf)));
		}
	}
	return (img);
}
