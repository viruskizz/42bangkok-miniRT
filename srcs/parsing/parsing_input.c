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

/*
* [function initialise and checking cylinder value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	cylinder_inititialize(t_data *data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	t_obj	*cylinder;
// 	char	*trimed_obj;
// 	double	diameter;

// 	index = 0;
// 	cylinder = (t_obj *)ft_calloc(sizeof(t_obj), 1);
// 	cylinder->idx = 0;
// 	cylinder->type = CYLIND;
// 	cylinder->name = NULL;
// 	if (!cylinder)
// 		exit_error("minirt: usuccesful allocating the memmory.");
// 	while (object[index])
// 	{
// 		if (index > 5)
// 			exit_error("minirt: too many information input for cylinder.");
// 		trimed_obj = ft_strtrim(object[index], "\t");
// 		if (!trimed_obj)
// 			exit_error("minirt: triming object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "cy", 3))
// 			exit_error("minirt: invalid identifier input for cylinder");
// 		else if (index == 1)
// 			cylinder->pos = ato_tvector(trimed_obj);
// 		else if (index == 2)
// 			cylinder->norm = ato_tvector(trimed_obj);
// 		else if (index == 3)
// 			diameter = ato_double(trimed_obj);
// 		else if (index == 4)
// 			cylinder->size = size_initialise(ato_double(trimed_obj), diameter, diameter);
// 		else if (index == 5)
// 			cylinder->color = ato_tcolor(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 6)
// 		exit_error("minirt: too less information input for cylinder.");
// 	if (!tvector_inrange(cylinder->norm, -1.0, 1.0))
// 		exit_error("minirt: invalid normalized orientation vector for cylinder.");
// 	ft_lstadd_back(&data->objs, ft_lstnew((void *)cylinder));
// }

/*
* [function initialise and checking plane value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	plane_initialise(t_data *data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	t_obj	*plane;
// 	char	*trimed_obj;

// 	index = 0;
// 	plane = (t_obj *)ft_calloc(sizeof(t_obj), 1);
// 	if (!plane)
// 		exit_error("minirt: unsuccesful allocating the memmory..");
// 	plane->idx = 0;
// 	plane->type = PLANE;
// 	plane->name = NULL;
// 	plane->size = size_initialise(0, 0, 0);
// 	while(object[index])
// 	{
// 		if (index > 4)
// 			exit_error("minirt: too many information input for plane.");
// 		trimed_obj = ft_strtrim(object[index], "\t");
// 		if (!trimed_obj)
// 			exit_error("minirt: triming object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "pl", 3))
// 			exit_error("minirt: invalid identifier for plane");
// 		else if (index == 1)
// 			plane->pos = ato_tvector(trimed_obj);
// 		else if (index == 2)
// 			plane->norm = ato_tvector(trimed_obj);
// 		else if (index == 3)
// 			plane->color = ato_tcolor(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 4)
// 		exit_error("minirt: too less information input for plane.");
// 	if (!tvector_inrange(plane->norm, -1.0, 1.0))
// 		exit_error("minirt: invalid normalized orirntarion vector value for plane.");
// 	ft_lstadd_back(&data->objs, ft_lstnew((void *)plane));
// }

/*
* [function initialise and checking sphere value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	sephere_initialise(t_data *data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	t_obj	*sphere;
// 	char	*trimed_obj;
// 	double	diameter;

// 	index = 0;
// 	sphere = (t_obj *)ft_calloc(sizeof(t_obj), 1);
// 	if (!sphere)
// 		exit_error("minirt: unsuccesful allocating the memmory..");
// 	sphere->type = SPHERE;
// 	sphere->idx = 0;
// 	sphere->name = NULL;
// 	sphere->norm = ato_tvector("0,0,0");
// 	while(object[index])
// 	{
// 		if (index > 3)
// 			exit_error("minirt: too many information input for sphere.");
// 		trimed_obj = ft_strtrim(object[index], "\t");
// 		if (!trimed_obj)
// 			exit_error("minirt: triming object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "sp", 3))
// 			exit_error("minirt: invalid identifier value for sphere.");
// 		else if (index == 1)
// 			sphere->pos = ato_tvector(trimed_obj);
// 		else if (index == 2)
// 		{
// 			diameter = ato_double(trimed_obj);
// 			sphere->size = size_initialise(diameter, diameter, diameter);
// 		}
// 		else if (index == 3)
// 			sphere->color = ato_tcolor(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 4)
// 		exit_error("minirt: too less information input for sphere.");
// 	ft_lstadd_back(&data->objs, ft_lstnew((void *)sphere));
// }

/*
* [utility function initialise value of t_size and return]
* => [success] : return the t_size wiht value height, width, depth.
* => [exit] : unsuccessful innitialise value cause invalid value or charactor.
*/
// t_size	size_initialise(double height, double width, double depth)
// {
// 	t_size size;

// 	if (height < 0.0)
// 		exit_error("minirt: invalid height value.");
// 	if (width < 0.0)
// 		exit_error("minirt: invalid width value.");
// 	if (depth < 0.0)
// 		exit_error("minirt: invalid depth value.");
// 	size.d = depth;
// 	size.w = width;
// 	size.h = height;
// 	return (size);
// }

/*
* [function initialise and checking light value]
* => [success] : intialize value into t_lht.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	light_initialise(t_data* data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	char	*trimed_obj;
// 	t_lht	*light;
	
// 	index = 0;
// 	light = (t_lht *)ft_calloc(sizeof(t_lht), 1);
// 	if (!light)
// 		exit_error("minirt: unsuccesful mallocing the memmory..");
// 	while (object[index])
// 	{
// 		if (index > 3)
// 			exit_error("minirt: too many information input for light.");
// 		trimed_obj = ft_strtrim(object[index], "/t");
// 		if (!trimed_obj)
// 			exit_error("minirt: triming the object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "L", 2))
// 			exit_error("minirt: invalid indentifier value for light.");
// 		else if (index == 1)
// 			light->pos = ato_tvector(trimed_obj);
// 		else if (index == 2)
// 			light->bright = ato_double(trimed_obj);
// 		else if (index == 3)
// 			light->color = ato_tcolor(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 4)
// 		exit_error("minirt: too less information input for light.");
// 	// * checking part
// 	if (light->bright < 0.0 || light->bright > 1.0)
// 		exit_error("minirt: invalid brightness value for light.");
// 	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
// }

/*
* [function initialise and checking camara value]
* => [success] : intialize value into t_cam.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	camara_initialise(t_data *data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	char	*trimed_obj;

// 	index = 0;
// 	while (object[index])
// 	{
// 		trimed_obj = ft_strtrim(object[index], "\t");
// 		if (!trimed_obj)
// 			exit_error ("minirt: triming the object is fail.");
// 		if (index > 3)
// 			exit_error ("minirt: too many information input for camara..");
// 		if (!trimed_obj)
// 			exit_error ("minirt: triming the object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "C", 2))
// 			exit_error ("minirt: invalid input value for camara.");
// 		else if (index == 1)
// 			data->cam.pos = ato_tvector(trimed_obj);
// 		else if (index == 2)
// 			data->cam.norm = ato_tvector(trimed_obj);
// 		else if (index == 3)
// 			data->cam.fov = ft_atoi(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 4)
// 		exit_error("minirt: too less information input for camara.");
// 	// * checking part //
// 	if (!tvector_inrange(data->cam.norm, -1.0, 1.0))
// 		exit_error("minirt: invalid normalized orirntarion vector value for camara.");
// 	if (data->cam.fov < 0 || data->cam.fov > 180)
// 		exit_error("minirt: invalid degree value for FOV.");
// }

/*
* [utility function check value of vactor is betaween min and max ?]
* => [1] : all vactor value is in range of min and max.
* => [0] : some vactor isn't in the range of min and max.
*/
// int	tvector_inrange(t_vtr vactor, double min, double max)
// {
// 	if (vactor.x < min || vactor.x > max)
// 		return (0);
// 	if (vactor.y < min || vactor.y > max)
// 		return (0);
// 	if (vactor.z < min || vactor.z > max)
// 		return (0);
// 	return (1);
// }

/*
* [untility function converting string into t_vtr value]
* => [return] : succesful converting string into t_vtr and return value.
* => [exit] : unsuccesful converring cause invalid amount of value or charcter.
*/
// t_vtr	ato_tvector(char *str)
// {
// 	t_vtr	result;
// 	double	vector[3];
// 	int		index;
// 	char	**value;

// 	index = 0;
// 	value = ft_split(str, ',');
// 	if (!value)
// 		exit_error("minirt: value spliting is fail in ato_tvector.");
// 	while(value[index])
// 	{
// 		if (index > 2)
// 			exit_error("minirt: too many information unput for vactor value.");
// 		vector[index] = ato_double(value[index]);
// 		index++;
// 	}
// 	if (index != 3)
// 		exit_error("minirt: too less information input for vector value.");
// 	result.x = vector[0];
// 	result.y = vector[1];
// 	result.z = vector[2];
// 	free_twopointer_char(value);
// 	return (result);
// }

/*
* [function initialize and checking ambient light value]
* => [success] : intialize value into t_amb.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
// void	ambient_initialise(t_data *data, char **object)
// {
// 	// print_twoarray_char(object);
// 	int		index;
// 	char	*trimed_obj;
// 	t_amb	ambient; // TODO when seperate checking function.

// 	index = 0;
// 	while (object[index])
// 	{
// 		if (index > 2)
// 			exit_error ("minirt: too many information input for ambient light..");
// 		trimed_obj = ft_strtrim(object[index], "\t");
// 		if (!trimed_obj)
// 			exit_error ("minirt: triming the object is fail.");
// 		if (index == 0 && ft_strncmp(trimed_obj, "A", 2))
// 			exit_error ("minirt: invalid input value for ambient light.");
// 		else if (index == 1)
// 			data->amb.ratio = ato_double(trimed_obj);
// 		else if (index == 2)
// 			data->amb.color = ato_tcolor(trimed_obj);
// 		free(trimed_obj);
// 		index++;
// 	}
// 	if (index != 3)
// 		exit_error("minirt: too less information for ambient light..");
// 	// TODO check ambient element value //
// 	// ? void checking_amb_value(t_amb ambient)
// 	ambient = data->amb;
// 	if (ambient.ratio < 0.0 || ambient.ratio > 1.0)
// 		exit_error ("minirt: invalid ambient lighting ratio value.");
// 	if (ambient.color.r < 0 || ambient.color.r > 255)
// 		exit_error ("minirt: invalid colors R value for ambient light.");
// 	if (ambient.color.g < 0 || ambient.color.g > 255)
// 		exit_error ("minirt: invalid colors G value for ambient light.");
// 	if (ambient.color.b < 0 || ambient.color.b > 255)
// 		exit_error ("minirt: invalid colors B value for ambient light.");
// }

/*
* [utility function changing string into t_colour value]
* => [return] : success converting into t_color and return that value.
* => [exit] : unsuccessful converting with invalid value or to many value.
TODO add checking colour value at the end of function..
*/
// t_color	ato_tcolor(char *str)
// {
// 	int		color[3];
// 	int		index;
// 	char	**value;
// 	t_color	result;

// 	index = 0;
// 	value = ft_split(str, ',');
// 	if (!value)
// 		exit_error("minirt: value spliting is fail in ato_tcolor.");
// 	while (value[index])
// 	{
// 		if (index > 2)
// 			exit_error("minirt: too many values for color's element.");
// 		for (int i = 0; value[index][i]; i++)
// 		{
// 			if (!ft_isdigit(value[index][i]))
// 				exit_error("minirt: invalid color's value..");
// 		}
// 		color[index] = ft_atoi(value[index]);
// 		index++;
// 	}
// 	if (index != 3)
// 		exit_error("minirt: too less values for color's element.");
// 	result.r = color[0];
// 	result.g = color[1];
// 	result.b = color[2];
// 	free_twopointer_char(value);
// 	return (result);
// }

/*
* [utility function return amount of character "c" in string "str"]
* => 0 : unfound any character "c" in string "str".
* => >0 : found and return amount of character "c" in string "str"
*/
// int	character_count(char *str, char c)
// {
// 	int index;
// 	int	count;

// 	index = 0;
// 	count = 0;
// 	while (str[index])
// 	{
// 		if (str[index] == c)
// 			count++;
// 		index++;
// 	}
// 	return (count);
// }

/* 
* [identifier checking function..]
* object -> line that splite from file_line;
* index -> alway be -1 for starting index;
* => >= 0 : position of identifier.
* =>  < 0 : invalid identifier.
*/
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

/*
* [utility function joining string "str1+str2 "and free the first argument]
* str1 -> first string
* str2 -> seccond string
*=> !NULL : new string is joined
*/
// char	*ft_strjoin_pro(char *str1, char *str2)
// {
// 	char	*result;
// 	size_t	len1;
// 	size_t	len2;
// 	size_t	len;

// 	len = 0;
// 	if (str1)
// 		len1 = ft_strlen(str1);
// 	len2 = ft_strlen(str2);
// 	if (!str1)
// 		result = (char *)ft_calloc(sizeof(char), len2 + 1);
// 	else
// 		result = (char *)ft_calloc(sizeof(char), len1 + len2 + 1);
// 	if (!result)
// 		exit_error("minirr: cannot malloc in strjoin_pro.");
// 	if (str1)
// 		len = ft_strlcpy(result, str1, len1 + 1);
// 	ft_strlcpy(&result[len], str2, len2 +1);
// 	if (str1)
// 		free(str1);
// 	return (result);
// }

/* 
*[utility function for free char** pointer]
*/
// void	free_twopointer_char(char **ptr)
// {
// 	int	index;
	
// 	index = 0;
// 	while (ptr[index])
// 		free(ptr[index++]);
// 	free(ptr);
// }

/*
* [utility function changing string to double]
* => [return] : successful converting and return value.
* => [exit] : unsucces converting with invalid character, overflow value
*/
// double	ato_double(char *str)
// {
// 	long double	result;
// 	double		sign;
// 	int			index;
// 	int			precision;
	
// 	precision = 0;
// 	sign = 1.0;
// 	index = 0;
// 	result = 0.0;
// 	if (str[0] == '.' || str[ft_strlen(str) - 1] == '.')
// 		exit_error("minirt: invalid value for element in ito_double.");
// 	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
// 		index++;
// 	if (str[index] == '-')
// 	{
// 		sign = -1.0;
// 		index++;
// 	}
// 	while (str[index])
// 	{
// 		if (!ft_isdigit(str[index]) && str[index] != '.')
// 			exit_error("minirt: invalid character for value in ito_double..");
// 		if (str[index] == '.')
// 			precision = 10;
// 		else if (precision == 0)
// 			result = (result * 10.0) + (str[index] - '0');
// 		else if (precision > 0)
// 		{
// 			result = result + ((str[index] - '0') * 1.0 / precision);
// 			precision *= 10;
// 		}
// 		if (result > DBL_MAX || result < -DBL_MAX)
// 			exit_error("minirt: invalid value for element in ito_double...");
// 		index++;
// 	}
// 	return (((double)(result * sign)));
// }

/*
* [utility function print error and exit the program.]
*/
// void	exit_error(char *str)
// {
// 	printf("%s\n", str);
// 	exit (EXIT_FAILURE);
// }
