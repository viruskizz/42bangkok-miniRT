/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:27:04 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/25 02:10:12 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"
#include <string.h>

void	exit_error(char *str); // * add to .h
void	free_twopointer_char(char **ptr); // * add to .h
char	*ft_strjoin_pro(char *str1, char *str2); // * add to .h
int		character_count(char *str, char c);
double	ato_double(char *str);
t_color	ato_tcolor(char *str);

void		printTwoArray(char **str); // * debuging

static int	file_checking(char *file);
static void	get_input(t_data *data, int fd);
static int	identifier_checking(char **object, int index);
static void	object_lexering(t_data *data, char **object, int identifier);

void	ambient_initialise(t_data *data, char **object);

t_data	parsing_input(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		exit_error("minirt: wrong argurment");
	// * file check;
	fd = file_checking(argv[1]);
	// *.attribute check;
	get_input(&data, fd);
	return (data);
}

static int	file_checking(char *file)
{
	int		fd;
	char	*type;

	// * check file type  --> [hello.rt] [hello.rt.rt] [hello.as.rt] [hello.rt.as]
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
	printTwoArray(file_line);

	while (file_line[index])
	{
		// * check identifier //
		object = ft_split(file_line[index], ' ');
		if (!file_line)
			exit_error("minirt: spliting line is failed.");
		// printTwoArray(object);
		identifier = identifier_checking(object, -1);
		if (identifier < 0)
			exit_error ("minirt: invalid identifier...");
		
		// * lexering
		object_lexering(data, object, identifier);
		free_twopointer_char(object);
		index++;
	}
}

void	object_lexering(t_data *data, char **object, int identifier)
{
	if (!ft_strncmp(object[identifier], "A", 2))
		ambient_initialise(data, object);
	else if (!ft_strncmp(object[identifier], "C", 2))
		printf("%s\n", "go to fucntion C");
	else if (!ft_strncmp(object[identifier], "L", 2))
		printf("%s\n", "go to fucntion L");
	else if (!ft_strncmp(object[identifier], "sp", 3))
		printf("%s\n", "go to fucntion sp");
	else if (!ft_strncmp(object[identifier], "pl", 3))
		printf("%s\n", "go to fucntion ol");
	else if (!ft_strncmp(object[identifier], "cy", 3))
		printf("%s\n", "go to fucntion cy");
	else
		printf("%s\n", "ship hay aew\n");
	
}

void	ambient_initialise(t_data *data, char **object)
{
	printTwoArray(object);
	int		index;
	char	*trimed_obj;

	index = 0;
	while (object[index])
	{
		if (index > 2)
			exit_error ("minirt: too many elements for ambient light...");
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error ("minirt: triming the object is fail.");
		if (character_count(trimed_obj, ',') == 2)
			data->amb.color = ato_tcolor(trimed_obj);
		else if (character_count(trimed_obj, '.') == 1)
			data->amb.ratio = ato_double(trimed_obj);
		index++;
		free(trimed_obj);
	}
	// * check ambient element value //
}

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
	result.r = color[0];
	result.g = color[1];
	result.b = color[2];
	free_twopointer_char(value);
	return (result);
}

int	character_count(char *str, char c)
{
	int index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

/* [identifier checking function..]
	object -> line thar splite from file_line;
	index -> alway be -1 for starting index;
	=> >= 0 : position of identifier
	=>  < 0 : invalid identifier */
int	identifier_checking(char **object, int index)
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

/* [string joining fucntion "str1+str2 "and free the first argument]
	str1 -> first string
	str2 -> seccond string
	=> !NULL : new string is joined*/
char	*ft_strjoin_pro(char *str1, char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len;

	len = 0;
	if (str1)
		len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!str1)
		result = (char *)ft_calloc(sizeof(char), len2 + 1);
	else
		result = (char *)ft_calloc(sizeof(char), len1 + len2 + 1);
	if (!result)
		exit_error("minirr: cannot malloc in strjoin_pro.");
	if (str1)
		len = ft_strlcpy(result, str1, len1 + 1);
	ft_strlcpy(&result[len], str2, len2 +1);
	if (str1)
		free(str1);
	return (result);
}

/* [free char** pointer function] */
void	free_twopointer_char(char **ptr)
{
	int	index;
	
	index = 0;
	while (ptr[index])
		free(ptr[index++]);
	free(ptr);
}

double	ato_double(char *str)
{
	long double	result;
	double	sign;
	int		index;
	int		precision;
	
	precision = 0;
	sign = 1.0;
	index = 0;
	result = 0.0;
	if (str[0] == '.' || str[ft_strlen(str) - 1] == '.')
		exit_error("minirt: invalid value for element in ito_double.");
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-')
		sign = -1.0;
	while (str[index])
	{
		if (!ft_isalnum(str[index]) && str[index] != '.')
		{
			printf("|%c|\n", str[index]);
			exit_error("minirt: invalid value for element in ito_double..");
		}
		if (str[index] == '.')
			precision = 10;
		else if (precision == 0)
			result = (result * 10.0) + (str[index] - '0');
		else if (precision >= 1)
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

void	printTwoArray(char **str)
{
	for (int i = 0; str[i]; i++)
		printf("[%d]:|%s|\n", i, str[i]);
}

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}

void	print_data(t_data *data)
{
	//* ambient light
	printf("\n[ambient light]\n");
	printf("ratio: %f\n", data->amb.ratio);
	printf("color: %d,%d,%d\n", data->amb.color.r, data->amb.color.g, data->amb.color.b);
	// *camara
}
