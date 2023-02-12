/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:27:04 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 01:08:22 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"
#include <string.h>

/* 
TODO utility functions that must add into header files
*/

void	exit_error(char *str);
void	free_twopointer_char(char **ptr);
char	*ft_strjoin_pro(char *str1, char *str2);
int		character_count(char *str, char c);
double	ato_double(char *str);
t_color	ato_tcolor(char *str);
t_vtr	ato_tvector(char *str);
int		tvector_inrange(t_vtr vactor, double min, double max);
t_size	size_initialise(double height, double width, double depth);

static int	file_checking(char *file);
static void	get_input(t_data *data, int fd);
static int	identifier_checking(char **object, int index);
static void	object_lexering(t_data *data, char **object, int identifier);

void	ambient_initialise(t_data *data, char **object);
void	camara_initialise(t_data *data, char **object);
void	light_initialise(t_data* data, char **object);
void	sephere_initialise(t_data *data, char **object);
void	plane_initialise(t_data *data, char **object);
void	cylinder_inititialize(t_data *data, char **object);

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
	int		fd;

	if (argc != 2)
		exit_error("minirt: wrong argurment");
	// * file check;
	fd = file_checking(argv[1]);
	// *.attribute check;
	data.lht = NULL;
	data.objs = NULL;
	get_input(&data, fd);
	return (data);
}

/*
* [funciton checking input file that is it valid or available ?]
* => [return > 2] : valid file and openable.
* => [exit] : any invalid the function will exit.
 */
static int	file_checking(char *file)
{
	int		fd;
	char	*type;

	if (ft_strncmp(ft_strrchr(file, '.'), ".rt", 4))
		exit_error("minirt: wrong file type.");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("minirt: the file cannot open.");
	return (fd);
}

static void	get_input(t_data *data, int fd)
{
	char buff[READ_SIZE + 1];
	int	read_byte;
	char *file;
	char **file_line;

	file = NULL;
	// * read from the file
	while (1 > 0)
	{
		read_byte = read(fd, buff, READ_SIZE);
		buff[read_byte] = '\0';
		if (read_byte < READ_SIZE)
		{
			if (read_byte > 0)
				file = ft_strjoin_pro(file, buff);
			break ;
		}
		file = ft_strjoin_pro(file, buff);
	}
	
	char	**object;
	int		index;
	int		identifier;

	index = 0;
	file_line = ft_split(file, '\n');
	if (!file_line)
		exit_error("minirt: spliting file_line is failed.");
	// print_twoarray_char(file_line);

	while (file_line[index])
	{
		// * check identifier //
		object = ft_split(file_line[index], ' ');
		if (!file_line)
			exit_error("minirt: spliting line is failed.");
		// print_twoarray_char(object);
		identifier = identifier_checking(object, -1);
		if (identifier < 0)
			exit_error ("minirt: invalid identifier...");
		
		// * lexering
		object_lexering(data, object, identifier);
		free_twopointer_char(object);
		index++;
	}
}

/*
* [function changing input into value by each identifire]
* => [success] : get value of each identifier.
* => [exit] : unsuccess get value.
*/
void	object_lexering(t_data *data, char **object, int identifier)
{
	if (!ft_strncmp(object[identifier], "A", 2))
		ambient_initialise(data, object);
	else if (!ft_strncmp(object[identifier], "C", 2))
		camara_initialise(data, object);// printf("%s\n", "go to fucntion C");
	else if (!ft_strncmp(object[identifier], "L", 2))
		light_initialise(data, object);//printf("%s\n", "go to fucntion L");
	else if (!ft_strncmp(object[identifier], "sp", 3))
		sephere_initialise(data, object);//printf("%s\n", "go to fucntion sp");
	else if (!ft_strncmp(object[identifier], "pl", 3))
		plane_initialise(data, object);//printf("%s\n", "go to fucntion ol");
	else if (!ft_strncmp(object[identifier], "cy", 3))
		cylinder_inititialize(data, object);//printf("%s\n", "go to fucntion cy");
	else
		printf("%s\n", "ship hay aew\n"); // ! dont forget to delete...
}

static int	identifier_checking(char **object, int index)
{
	int 	xedni;
	char	**identifier;
	int		position_count[2];

	position_count[0] = -1;
	position_count[1] = 0;
	identifier = ft_split("A C L sp pl cy", ' ');
	if (!identifier)
		exit_error("minirt: spliting identifier constant is failed.");
	while (object[++index])
	{
		xedni = 0;
		while (identifier[xedni])
		{
			if (!(ft_strncmp(object[index], identifier[xedni++], ft_strlen(object[index]))))
			{
				position_count[0] = index;
				position_count[1]++;
			}
		}
	}
	free_twopointer_char(identifier);
	if (position_count[0] != -1 && position_count[1] == 1)
		return (position_count[0]);
	return(-1);
}
