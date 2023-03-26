/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:18:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 03:19:50 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <float.h>

// * unit
t_color		set_color(int r, int g, int b);
t_size		set_size(float w, float h, float d);
t_ray		set_ray(t_vtr a, t_vtr b);
int			close0(const float f1, const float f2);
float		degree_radian(float degree);

// * pixel
int			rgb_to_int(int r, int g, int b);
int			color_to_int(t_color color);
int			colorf_to_int(t_colorf colorf);
void		pixel_put_img(t_img *img, int x, int y, int color);

// * color
t_color		rgb_to_color(int r, int g, int b);
<<<<<<< HEAD
t_color		colorf_to_color(t_colorf cf);
t_colorf	color_to_colorf(t_color color);
t_colorf	colorf_add(t_colorf c1, t_colorf c2);
t_colorf	colorf_set(float r, float g, float b);
=======
t_colorf	color_to_colorf(t_color color);
t_color		colorf_to_color(t_colorf cf);
>>>>>>> main

// * vector
t_vtr		vtrset(float x, float y, float z);
float		vtrmag(t_vtr v);
t_vtr		vtrnorm(t_vtr v);
t_vtr		vtradd(t_vtr a, t_vtr b);
t_vtr		vtrsub(t_vtr a, t_vtr b);
t_vtr		vtrscale(t_vtr v, float s);
float		vtrdot(t_vtr a, t_vtr b);
t_vtr		vtrcross(t_vtr a, t_vtr b);
void		vtrprint(t_vtr v);
// * matrix
float		**mtx_identity(int size);
float		**mtx_trans(float **m, int size);
float		**mtx_sub(float **m, int size, int row, int col);
float		**mtx_multi(float **m1, float **m2, int size);
float		**mtx_inverse(float **m, int size);
float		mtx_det(float **m, int size);
void		mtx_print(float **m, int size);
void		mtx_free(float **m, int size);

// * utils from sharnvon..
void		exit_error(char *str);
void		free_twopointer_char(char **ptr);
char		*ft_strjoin_pro(char *str1, char *str2);
char		*ft_floattoa(float number);
int			character_count(char *str, char c);
float		ato_float(char *str);
t_color		ato_tcolor(char *str);
t_vtr		ato_tvector(char *str);
int			tvector_inrange(t_vtr vactor, float min, float max);
t_size		size_initialise(float height, float width, float depth);

#endif
