/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:06:27 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 01:10:46 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [utility function changing string to double]
* => [return] : successful converting and return value.
* => [exit] : unsucces converting with invalid character, overflow value
*/
double	ato_double(char *str)
{
	long double	result;
	double		sign;
	int			index;
	int			precision;
	
	precision = 0;
	sign = 1.0;
	index = 0;
	result = 0.0;
	if (str[0] == '.' || str[ft_strlen(str) - 1] == '.')
		exit_error("minirt: invalid value for element in ito_double.");
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-')
	{
		sign = -1.0;
		index++;
	}
	while (str[index])
	{
		if (!ft_isdigit(str[index]) && str[index] != '.')
			exit_error("minirt: invalid character for value in ito_double..");
		if (str[index] == '.')
			precision = 10;
		else if (precision == 0)
			result = (result * 10.0) + (str[index] - '0');
		else if (precision > 0)
		{
			result = result + ((str[index] - '0') * 1.0 / precision);
			precision *= 10;
		}
		if (result > DBL_MAX || result < -DBL_MAX)
			exit_error("minirt: invalid value for element in ito_double...");
		index++;
	}
	return (((double)(result * sign)));
}

/*
* [utility function changing string into t_colour value]
* => [return] : success converting into t_color and return that value.
* => [exit] : unsuccessful converting with invalid value or to many value.
TODO add checking colour value at the end of function..
*/
t_color	ato_tcolor(char *str)
{
	int		color[3];
	int		index;
	char	**value;
	t_color	result;

	index = 0;
	value = ft_split(str, ',');
	if (!value)
		exit_error("minirt: value spliting is fail in ato_tcolor.");
	while (value[index])
	{
		if (index > 2)
			exit_error("minirt: too many values for color's element.");
		for (int i = 0; value[index][i]; i++)
		{
			if (!ft_isdigit(value[index][i]))
				exit_error("minirt: invalid color's value..");
		}
		color[index] = ft_atoi(value[index]);
		index++;
	}
	if (index != 3)
		exit_error("minirt: too less values for color's element.");
	result.r = color[0];
	result.g = color[1];
	result.b = color[2];
	result.intens = 1.0;
	free_twopointer_char(value);
	return (result);
}

/*
* [untility function converting string into t_vtr value]
* => [return] : succesful converting string into t_vtr and return value.
* => [exit] : unsuccesful converring cause invalid amount of value or charcter.
*/
t_vtr	ato_tvector(char *str)
{
	t_vtr	result;
	double	vector[3];
	int		index;
	char	**value;

	index = 0;
	value = ft_split(str, ',');
	if (!value)
		exit_error("minirt: value spliting is fail in ato_tvector.");
	while(value[index])
	{
		if (index > 2)
			exit_error("minirt: too many information unput for vactor value.");
		vector[index] = ato_double(value[index]);
		index++;
	}
	if (index != 3)
		exit_error("minirt: too less information input for vector value.");
	result.x = vector[0];
	result.y = vector[1];
	result.z = vector[2];
	free_twopointer_char(value);
	return (result);
}