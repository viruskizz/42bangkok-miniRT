#include "minirt.h"

static void	cam_value_check(int	inputs, t_data *data);

void	cam_geometry(t_cam *cam)
{
	t_vtr	l;
	t_vtr	u;
	t_vtr	v;

	l = vtrnorm(vtrsub(cam->lookat, cam->pos));
	u = vtrnorm(vtrcross(l, cam->up));
	v = vtrnorm(vtrcross(u, l));
	cam->proj_c = vtradd(cam->pos, vtrscale(l, cam->length));
	cam->proj_u = vtrscale(u, cam->horz);
	cam->proj_v = vtrscale(v, (cam->horz / cam->ratio));
}

/*
 * generate ray from camera position to projection screen
 */
t_ray	cam_ray(t_cam cam, float proj_x, float proj_y)
{
	t_vtr	world1;
	t_vtr	screen_pos;

	world1 = vtradd(cam.proj_c, vtrscale(cam.proj_u, proj_x));
	screen_pos = vtradd(world1, vtrscale(cam.proj_v, proj_y));
	return rayset(cam.pos, screen_pos);
}


/*
* [function initialise and checking camara value]
* => [success] : intialize value into t_cam.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	cam_initialise(t_data *data, char **object)
{
	int		index;
	char	*trimed_obj;

	index = 0;
	while (object[index])
	{
		if (index > 3)
			exit_error (TOO_MANY_INPUT_C);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error (FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "C", 2))
			exit_error (INVALID_IDENT_C);
		else if (index == 1)
			data->cam.pos = ato_tvector(trimed_obj);
		else if (index == 2)
			data->cam.norm = ato_tvector(trimed_obj);
		else if (index == 3)
			data->cam.fov = ft_atoi(trimed_obj);
		free(trimed_obj);
		index++;
	}
	cam_value_check(index, data);
	data->cam.pos = vtrset(0, 0, -10.0);
	data->cam.lookat = vtrset(0, 0, 0);
	data->cam.up = vtrset(0, 1.00, 0);
	data->cam.length = 1.0;
	data->cam.horz = 0.25;
	data->cam.ratio = 16.0 / 9.0;
	cam_geometry(&data->cam);
}

/*
* [helper function of camara_initialise checking camara value]
* => [success] : all value is valid.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
static void	cam_value_check(int	inputs, t_data *data)
{
	if (inputs != 4)
		exit_error(TOO_LESS_INPUT_C);
	if (!tvector_inrange(data->cam.norm, -1.0, 1.0))
		exit_error(INVALID_NORM_C);
	if (data->cam.fov < 0 || data->cam.fov > 180)
		exit_error(INVALID_FOV_C);
}