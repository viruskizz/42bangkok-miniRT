#ifndef UTILS_H
# define UTILS_H

# include <float.h>

// * unit
t_color	set_color(int r, int g, int b);
t_size	set_size(float w, float h, float d);
t_ray	set_ray(t_vtr a, t_vtr b);
int		close0(const float f1, const float f2);

// * pixel
int		rgb_to_int(int r, int g, int b);
int		color_to_int(t_color color);
int		colorf_to_int(t_colorf colorf);
void	pixel_put_img(t_img *img, int x, int y, int color);

// * color
t_color		rgb_to_color(int r, int g, int b);
t_colorf	color_to_colorf(t_color color);
t_color		colorf_to_color(t_colorf cf);

// * vector
t_vtr	vtrset(float x, float y, float z);
float	vtrmag(t_vtr v);
t_vtr	vtrnorm(t_vtr v);
t_vtr	vtradd(t_vtr a, t_vtr b);
t_vtr	vtrsub(t_vtr a, t_vtr b);
t_vtr	vtrscale(t_vtr v, float s);
float	vtrdot(t_vtr a, t_vtr b);
t_vtr	vtrcross(t_vtr a, t_vtr b);
void	vtrprint(t_vtr v);
// * matrix
float	**mtx_identity(int size);
float	**mtx_trans(float **m, int size);
float	**mtx_sub(float **m, int size, int row, int col);
float	**mtx_multi(float **m1, float **m2, int size);
float	**mtx_inverse(float **m, int size);
float	mtx_det(float **m, int size);
void	mtx_print(float **m, int size);
void	mtx_free(float **m, int size);

#endif
