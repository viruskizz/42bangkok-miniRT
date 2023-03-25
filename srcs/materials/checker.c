/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:27:50 by tsomsa            #+#    #+#             */
/*   Updated: 2023/03/25 15:27:52 by tsomsa           ###   ########.fr       */
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
		return colorf_set(1.0, 1.0, 1.0);
	else
		return colorf_set(1, 0, 0);
}

/**
 * Start testing
*/
t_img	txtr_checker_test(t_data *data)
{
	t_img	img;
	t_vtr	uvz;
	t_colorf cf;
	float	**txt_mtx;

	txt_mtx =	txtr_mtx_trans(
					vtrset(0, 0, 0),
					PI/4,
					vtrset(4, 4, 0)
				);
	mtx_print(txt_mtx, 3);
	img.ptr = mlx_new_image(data->mlx, (int) WIDTH, (int) HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lh, &img.endian);
	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			uvz.x = ((float) x / ((float) WIDTH / 2.0)) - 1.0;
			uvz.y = ((float) y / ((float) HEIGHT / 2.0)) - 1.0;
			uvz.z = 0;
			cf = txtr_checker_colorf(uvz, txt_mtx);
			pixel_put_img(&img, x, y, color_to_int(colorf_to_color(cf)));
			x++;
		}
		y++;
	}
	return (img);
}