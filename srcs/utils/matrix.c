#include "minirt.h"

float	**mtx_identity(int size)
{
	float	**m;
	int		i;
	int		j;

	m = ft_calloc(size, sizeof(float));
	i = 0;
	while (i < size)
	{
		m[i] = ft_calloc(size, sizeof(float));
		j = 0;
		while (j < size)
		{
			if (i == j)
				m[i][j] = 1.0;
			else
				m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (m);
}

float	**mtx_multi(float **m1, float **m2, int size)
{
	float	**mm;
	float	sum;
	int		i;
	int		j;
	int		k;

	mm = malloc(sizeof(float) * size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		mm[i] = malloc(sizeof(float) * size);
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

float	**mtx_inverse(float **m, int size)
{
	float	**mm;
	float	**subm;
	float	det;
	int	i;
	int	j;

	i = -1;
	det = mtx_det(m, size);
	mm = ft_calloc(size, sizeof(float));
	while (++i < size)
	{
		j = -1;
		mm[i] = ft_calloc(size, sizeof(float));
		while (++j < size)
		{
			subm = mtx_sub(m, size, i, j);
			mm[i][j] = powf(-1, i + j) * mtx_det(subm, size - 1) / det;
			mtx_free(subm, size - 1);
		}
	}
	return (mm);
}

float	mtx_det(float **m, int size)
{
	int i;
	int	sign;
	float sum;
	if (size == 2)
		return (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
	i = -1;
	sign = 1;
	sum = 0.0;
	while (++i < size)
	{
		float **subm = mtx_sub(m, size, 0, i);
		sum += m[0][i] * sign * mtx_det(subm, size - 1);
		mtx_free(subm, size - 1);
		sign = -sign;
	}
	return (sum);
}

float	**mtx_sub(float **m, int size, int row, int col)
{
	float	**mm;
	int		i;
	int		j;
	int		x;
	int		y;

	mm = ft_calloc(size - 1, sizeof(float));
	i = -1;
	y = 0;
	while (++i < size)
	{
		if (i == row)
			continue;
		mm[y] = ft_calloc(size - 1, sizeof(float));
		j = -1;
		x = 0;
		while(++j < size)
		{
			if (j == col)
				continue;;
			mm[y][x] = m[i][j];
			x++;
		}
		y++;
	}
	return (mm);
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
