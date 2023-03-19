/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:49:49 by araiva            #+#    #+#             */
/*   Updated: 2023/03/19 19:49:50 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

/*
* [funciton checking input file that is it valid or available ?]
* => [return > 2] : valid file and openable.
* => [exit] : any invalid the function will exit.
 */
int	validate_file(char *file)
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

int	validate_code(char **objs, int idx)
{
	int		xedni;
	char	**code;
	int		pos[2];

	pos[0] = -1;
	pos[1] = 0;
	code = ft_split("A C L sp pl cy cn", ' ');
	if (!code)
		exit_error("minirt: spliting code constant is failed.");
	while (objs[++idx])
	{
		xedni = 0;
		while (code[xedni])
		{
			if (!(ft_strncmp(objs[idx], code[xedni++], ft_strlen(objs[idx]))))
			{
				pos[0] = idx;
				pos[1]++;
			}
		}
	}
	free_twopointer_char(code);
	if (pos[0] != -1 && pos[1] == 1)
		return (pos[0]);
	return (-1);
}
