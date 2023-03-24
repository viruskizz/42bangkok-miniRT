/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:14:02 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/24 18:18:18 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	texture_argument(t_obj *object, char *trimed_obj);
static int	reflect_shine_argument(t_obj *object, char *trimed_obj);

void	bonus_argument(t_obj *object, char *trimed_obj, int *check, char *err)
{
	if (trimed_obj[0] != '+' && trimed_obj[0] != 'm')
	{
		free(trimed_obj);
		free(object);
		exit_error(err);
	}
	if (trimed_obj[0] == '+')
		check[0] += texture_argument(object, trimed_obj);
	else
		check[1] += reflect_shine_argument(object, trimed_obj);
	if (check[0] > 1 || check[1] > 1)
	{
		free(trimed_obj);
		free(object);
		exit_error(err);
	}
}

static int	texture_argument(t_obj *object, char *trimed_obj)
{
	int		fd;
	char	*type;

	object->texture = ft_substr(trimed_obj, 1, ft_strlen(trimed_obj) - 1);
	if (ft_strncmp(object->texture, "checkerboard", 13))
	{
		type = ft_strrchr(object->texture, '.');
		if (!type)
			exit_error("ERORO::the texture file type is incorect.");
		if (ft_strncmp(type, ".xpm", 5))
			exit_error("ERORO::the texture file type is incorect.");
		fd = open(object->texture, O_RDONLY);
		if (fd < 0)
			exit_error("ERROR::the texture file cannot open.");
		close(fd);
	}
	return (1);
}

static int	reflect_shine_argument(t_obj *object, char *trimed_obj)
{
	char	*trimed_value;
	char	**split_value;
	int		count;

	count = 0;
	split_value = ft_split(&trimed_obj[1], ',');
	while (split_value[count])
	{
		if (count > 1)
			exit_error("ERROR::too many input for reflectin/shine value.");
		trimed_value = ft_strtrim(split_value[count], "\t");
		if (count++ == 0)
			object->mat.reflc = ato_float(trimed_value);
		else
			object->mat.shin = ato_float(trimed_value);
		free(trimed_value);
	}
	if (count < 2)
		exit_error("ERROR::too less input for reflection/shine value.");
	if (object->mat.reflc < 0.0f || object->mat.reflc > 1.0f)
		exit_error("ERROR::the reflecttion value must be between 0.0-0.1.");
	if (object->mat.shin < 0.0f)
		exit_error("ERROR::invalid shine value, value must be positive.");
	free_twopointer_char(split_value);
	return (1);
}
