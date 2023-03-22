/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:18:36 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 03:18:37 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANS_H
# define TRANS_H

float	**trans_homo(t_vtr trans, t_vtr rotate, t_vtr scale);
void	trans_rot_xyz(t_vtr rotate, float ***result);
t_vtr	trans_vtr(t_vtr v, float **mtxtrans);
t_ray	trans_ray(t_ray ray, float **mtxtrans);
t_vtr	trans_norm_vtr_rot(t_vtr norm);

#endif
