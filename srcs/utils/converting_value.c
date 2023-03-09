/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:06:27 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 23:42:23 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		color_convert(char **value, int *color);
static double	float_convert(int index, char *str);

/*
* [utility function changing string to float]
* => [return] : successful converting and return value.
* => [exit] : unsucces converting with invalid character, overflow value
*/
float	ato_float(char *str)
{
	double		result;
	float		sign;
	int			index;

	sign = 1.0;
	index = 0;
	if (str[0] == '.' || str[ft_strlen(str) - 1] == '.')
		exit_error("minirt: invalid value for element in ito_float.");
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-')
	{
		sign = -1.0;
		index++;
	}
	result = float_convert(index, str);
	return (((float)(result * sign)));
}

/*
* [helper function of ato_float convert str to float]
* => [double] : valid chracter and value, coverted to float then return.
* => [exit] : invalid chracter or value is overflow, printed error and exit.
*/
static double	float_convert(int index, char *str)
{
	int		precision;
	double	result;

	precision = 0;
	result = 0.0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]) && str[index] != '.')
			exit_error("minirt: invalid character for value in ito_float..");
		if (str[index] == '.')
			precision = 10;
		else if (precision == 0)
			result = (result * 10.0) + (str[index] - '0');
		else if (precision > 0)
		{
			result = result + ((str[index] - '0') * 1.0 / precision);
			precision *= 10;
		}
		if (result > FLT_MAX || result < -FLT_MAX)
			exit_error("minirt: invalid value for element in ito_float...");
		index++;
	}
	return (result);
}

/*
* [utility function changing string into t_colour value]
* => [return] : success converting into t_color and return that value.
* => [exit] : unsuccessful converting with invalid value or to many value.
*/
t_color	ato_tcolor(char *str)
{
	int		color[3];
	char	**value;
	t_color	result;

	value = ft_split(str, ',');
	if (!value)
		exit_error("minirt: value spliting is fail in ato_tcolor.");
	color_convert(value, color);
	result.r = color[0];
	result.g = color[1];
	result.b = color[2];
	result.intens = 1.0;
	free_twopointer_char(value);
	return (result);
}

/*
* [helper function of ato_tcolor check and covert string to intiger.]
* => [success] : covert string value into int and store in color.
* => [unsuccess] : the string value is invalid, print error and exit program.
*/
static void	color_convert(char **value, int *color)
{
	int	index;
	int	chracter;

	index = 0;
	while (value[index])
	{
		if (index > 2)
			exit_error("minirt: too many values for color's element.");
		chracter = 0;
		while (value[index][chracter])
		{
			if (!ft_isdigit(value[index][chracter]))
				exit_error("minirt: invalid color's value..");
			chracter++;
		}
		color[index] = ft_atoi(value[index]);
		if (color[index] < 0 || color[index] > 255)
			exit_error("minirt: invalid value of color.\n"
				"• (hint) the value of color must be between 0 - 255.");
		index++;
	}
	if (index != 3)
		exit_error("minirt: too less values for color's element.");
}

/*
* [untility function converting string into t_vtr value]
* => [return] : succesful converting string into t_vtr and return value.
* => [exit] : unsuccesful converring cause invalid amount of value or charcter.
*/
t_vtr	ato_tvector(char *str)
{
	t_vtr	result;
	float	vector[3];
	int		index;
	char	**value;

	index = 0;
	value = ft_split(str, ',');
	if (!value)
		exit_error("minirt: value spliting is fail in ato_tvector.");
	while (value[index])
	{
		if (index > 2)
			exit_error("minirt: too many information input for vactor value.");
		vector[index] = ato_float(value[index]);
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
