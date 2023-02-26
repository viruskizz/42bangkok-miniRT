#include "minirt.h"

/*
* [function initialise and checking cylinder value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	cylinder_inititialize(t_data *data, char **object)
{
	int		index;
	t_obj	*cylinder;
	char	*trimed_obj;
	double	diameter;

	index = 0;
	cylinder = object_initialise(CYLIND);
	while (object[index])
	{
		if (index > 5)
			exit_error(TOO_MANY_INPUT_CY);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "cy", 3))
			exit_error(INVALID_IDENT_CY);
		else if (index == 1)
			cylinder->pos = ato_tvector(trimed_obj);
		else if (index == 2)
			cylinder->norm = ato_tvector(trimed_obj);
		else if (index == 3)
			diameter = ato_double(trimed_obj);
		else if (index == 4)
			cylinder->size = size_initialise(ato_double(trimed_obj), diameter, diameter);
		else if (index == 5)
			cylinder->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 6)
		exit_error(TOO_LESS_INPUT_CY);
	if (!tvector_inrange(cylinder->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_CY);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)cylinder));
}
