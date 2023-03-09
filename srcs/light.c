
#include "minirt.h"

/*
* [function initialize and checking ambient light value]
* => [success] : intialize value into t_amb.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	ambient_initialise(t_data *data, char **object)
{
	int		index;
	char	*trimed_obj;

	index = 0;
	while (object[index])
	{
		if (index > 2)
			exit_error (TOO_MANY_INPUT_A);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error (FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "A", 2))
			exit_error (INVALID_IDENT_A);
		else if (index == 1)
			data->amb.ratio = ato_double(trimed_obj);
		else if (index == 2)
			data->amb.color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 3)
		exit_error(TOO_LESS_INPUT_A);
	if (data->amb.ratio < 0.0 || data->amb.ratio > 1.0)
		exit_error (INVALID_RATIO_A);
}

/*
* [function initialise and checking light value]
* => [success] : intialize value into t_lht.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	lht_initialise(t_data* data, char **object)
{
	int		index;
	char	*trimed_obj;
	t_lht	*light;

	index = 0;
	light = (t_lht *)ft_calloc(sizeof(t_lht), 1);
	if (!light)
		exit_error(FAIL_ALLOC);
	while (object[index])
	{
		if (index > 3)
			exit_error(TOO_MANY_INPUT_L);
		trimed_obj = ft_strtrim(object[index], "/t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "L", 2))
			exit_error(INVALID_IDENT_L);
		else if (index == 1)
			light->pos = ato_tvector(trimed_obj);
		else if (index == 2)
			light->bright = ato_double(trimed_obj);
		else if (index == 3)
			light->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index < 3)
		exit_error(TOO_LESS_INPUT_L);
	if (light->bright < 0.0 || light->bright > 1.0)
		exit_error(INVALID_BRIGHT_L);
	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
}

/*
 * compute light between light point and intersection point
 * reflecing the local normal surface (inside object)
 ? lvtr = light vector in normalize
 ? svtr = starting vector
*/
void	lht_illuminated(t_lht lht, t_ints *ints)
{
	t_vtr	lvtr;
	float	angle;

	lvtr = vtrnorm(vtrsub(lht.pos, ints->p));
	angle = acos(vtrdot(ints->localn, lvtr));
	ints->illum = color_to_colorf(lht.color);
	ints->illum.alpha = 0.0;
	if (angle > HALF_PI)
	{
		ints->valid = 0;
	}
	else
	{
		ints->valid = 1;
		ints->illum.alpha = lht.bright * (1.0 - (angle / HALF_PI));
	}
}
