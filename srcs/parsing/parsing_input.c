/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:27:04 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/19 03:03:03 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"
// #include <string.h>

/*
TODO utility functions that must add into header files
*/

static void		set_data(t_data *data, char *filedata);
static char		*read_file(char *filename);
static void		object_lexering(t_data *data, char **object, int identifier);
static t_data	data_initialize(void);

/*
* [function parsing input from the file and conveting into struct data]
* => [return] :
* => [exit] :
TODO check lists amount of "data.lht" | 0 < lht_amount < 3 |
TODO check lists amount of "data.objs" | 0 < objs_amount |
TODO add mlx, window init when parsing is okay + init.obj->img.
*/
t_data	parsing_input(int argc, char **argv)
{
	t_data	data;
	char	*filedata;

	if (argc != 2)
		exit_error("minirt: wrong argurment");
	filedata = read_file(argv[1]);
	data = data_initialize();
	set_data(&data, filedata);
	return (data);
}

static t_data	data_initialize(void)
{
	t_data	data;
	int		count;

	data.mlx = NULL;
	data.win = NULL;
	data.w = WIDTH;
	data.h = HEIGHT;
	data.update = 0;
	data.ctrl_key = 0;
	data.lshift_key = 0;
	data.rshift_key = 0;
	data.selectp = -1;
	count = 0;
	while (count < 4)
		data.selectv[count++] = 0;
	data.lht = NULL;
	data.objs = NULL;
	return (data);
}

static char	*read_file(char *filename)
{
	char	buff[READ_SIZE + 1];
	int		read_byte;
	char	*str;
	int		fd;

	str = NULL;
	fd = validate_file(filename);
	while (1 > 0)
	{
		read_byte = read(fd, buff, READ_SIZE);
		buff[read_byte] = '\0';
		if (read_byte < READ_SIZE)
		{
			if (read_byte > 0)
				str = ft_strjoin_pro(str, buff);
			break ;
		}
		str = ft_strjoin_pro(str, buff);
	}
	return (str);
}

static void	set_data(t_data *data, char *filedata)
{
	char	**line;
	char	**obj;
	int		i;
	int		code;

	i = 0;
	line = ft_split(filedata, '\n');
	if (!line)
		exit_error("minirt: spliting file_line is failed.");
	data->lht = NULL;
	while (line[i])
	{
		obj = ft_split(line[i], ' ');
		if (!line)
			exit_error("minirt: spliting line is failed.");
		if (*obj[0] == '#' && i++)
			continue ;
		code = validate_code(obj, -1);
		if (code < 0)
			exit_error ("minirt: invalid identifier...");
		object_lexering(data, obj, code);
		free_twopointer_char(obj);
		i++;
	}
}

/*
* [function changing input into value by each identifire]
* => [success] : get value of each identifier.
* => [exit] : unsuccess get value.
*/
void	object_lexering(t_data *data, char **object, int identifier)
{
	static int	index = 1;

	if (index < 10000)
	{
		if (!ft_strncmp(object[identifier], "A", 2))
			ambient_initialise(data, object);
		else if (!ft_strncmp(object[identifier], "C", 2))
			cam_initialise(data, object);
		else if (!ft_strncmp(object[identifier], "L", 2))
			lht_initialise(data, object, index++);
		else if (!ft_strncmp(object[identifier], "sp", 3))
			sphere_initialise(data, object, index++);
		else if (!ft_strncmp(object[identifier], "pl", 3))
			plane_initialise(data, object, index++);
		else if (!ft_strncmp(object[identifier], "cy", 3))
			cylinder_inititialize(data, object, index++);
		else if (!ft_strncmp(object[identifier], "cn", 3))
			cone_inititialize(data, object, index++);
		else
			printf("%s\n", "ship hay aew\n");
	}
	else
		exit_error("minirt: too many objects..");
}
