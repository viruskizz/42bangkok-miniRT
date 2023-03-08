/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:30:57 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 01:30:58 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	mtx_det(float **m, int size)
{
	int		i;
	int		sign;
	float	sum;
	float	**subm;

	if (size == 2)
		return (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
	i = -1;
	sign = 1;
	sum = 0.0;
	while (++i < size)
	{
		subm = mtx_sub(m, size, 0, i);
		sum += m[0][i] * sign * mtx_det(subm, size - 1);
		mtx_free(subm, size - 1);
		sign = -sign;
	}
	return (sum);
}

void	mtx_print(float **m, int size)
{
	int	i;
	int	j;

	i = -1;
	printf("{\n");
	while (++i < size)
	{
		j = -1;
		printf("  { ");
		while (++j < size)
		{
			printf("%f", m[i][j]);
			if (j != size - 1)
				printf(", ");
		}
		printf(" }\n");
	}
	printf("}\n");
}

void	mtx_free(float **m, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(m[i]);
	free(m);
}
