/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:27:04 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/24 22:25:13 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"
#include <string.h>

void		exit_error(char *str); // * add to .h
void		free_twopointer_char(char **ptr); // * add to .h
char		*ft_strjoin_pro(char *str1, char *str2); // * add to .h
void		printTwoArray(char **str); // * debuging
static int	file_checking(char *file);
static void	get_input(t_data *data, int fd);
static int	identifier_checking(char **object, int index);
static void	object_lexering(t_data *data, char **object, int identifier);

t_data	*parsing_input(int argc, char **argv)
{
	t_data	*data;
	int		fd;

	if (argc != 2)
		exit_error("minirt: wrong argurment");
	fd = file_checking(argv[1]);
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit_error("minirt: data mallocing is failed in parsing_input");
	// *.attribute check;
	get_input(data, fd);
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
	// * read form the file
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
		printf("%s\n", "go to fucntion A");	// * void	ambient_innit (t_data *data, char **object);
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

void	printTwoArray(char **str)
{
	for (int i = 0; str[i]; i++)
		printf("%s\n", str[i]);
}

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}