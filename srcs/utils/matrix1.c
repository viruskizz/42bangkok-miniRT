/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:11:59 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/10 13:46:56 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**mtx_identity(int size)
{
	float	**m;
	int		i;
	int		j;

	m = ft_calloc(size, sizeof(float *));
	i = 0;
	while (i < size)
	{
		m[i] = ft_calloc(size, sizeof(float));
		j = 0;
		while (j < size)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

float	**mtx_trans(float **m, int size)
{
	float	**mm;
	int		i;
	int		j;

	mm = ft_calloc(size, sizeof(float *));
	i = -1;
	while (++i < size)
	{
		j = -1;
		mm[i] = ft_calloc(size, sizeof(float));
		while (++j < size)
			mm[i][j] = m[j][i];
	}
	return (mm);
}

float	**mtx_sub(float **m, int size, int row, int col)
{
	float	**mm;
	int		i;
	int		j;
	int		x;
	int		y;

	mm = ft_calloc(size - 1, sizeof(float *));
	i = -1;
	y = 0;
	while (++i < size)
	{
		if (i == row)
			continue ;
		mm[y] = ft_calloc(size - 1, sizeof(float));
		j = -1;
		x = 0;
		while (++j < size)
		{
			if (j == col)
				continue ;
			mm[y][x++] = m[i][j];
		}
		y++;
	}
	return (mm);
}

float	**mtx_multi(float **m1, float **m2, int size)
{
	float	**mm;
	float	sum;
	int		i;
	int		j;
	int		k;

	mm = ft_calloc(size, sizeof(float *));
	i = -1;
	while (++i < size)
	{
		j = -1;
		mm[i] = ft_calloc(size, sizeof(float));
		while (++j < size)
		{
			sum = 0;
			k = -1;
			while (++k < size)
				sum += m1[i][k] * m2[k][j];
			mm[i][j] = sum;
		}
	}
	return (mm);
}

/*
* variable c is 2 dimention array counter, c[0] = column, c[1] = row.
*/
float	**mtx_inverse(float **m, int size)
{
	float	**mm;
	float	**subm;
	float	**mmt;
	float	det;
	int		c[2];

	c[COL] = -1;
	det = mtx_det(m, size);
	mm = ft_calloc(size, sizeof(float *));
	while (++c[COL] < size)
	{
		c[ROW] = -1;
		mm[c[COL]] = ft_calloc(size, sizeof(float));
		while (++c[1] < size)
		{
			subm = mtx_sub(m, size, c[COL], c[ROW]);
			mm[c[COL]][c[ROW]] = powf(-1, c[COL] + c[ROW])
				* mtx_det(subm, size - 1) / det;
			mtx_free(subm, size - 1);
		}
	}
	mmt = mtx_trans(mm, 4);
	mtx_free(mm, 4);
	return (mmt);
}
