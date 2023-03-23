/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:21:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 03:21:49 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# ifdef __linux__
#  define KEY_LSHIFT		65505
#  define KEY_RSHIFT		65506
#  define KEY_LCTRL			65507
#  define KEY_RCTRL			65508
#  define KEY_ENTER			65293
#  define KEY_SPACE			32
#  define KEY_ESC			65307
#  define KEY_LEFT			65361
#  define KEY_RIGHT			65363
#  define KEY_UP			65362
#  define KEY_DOWN			65364
#  define KEY_A				97
#  define KEY_S				115
#  define KEY_D				100
#  define KEY_W				119
#  define KEY_R				114
#  define KEY_1				49
#  define KEY_2				50
#  define KEY_3				51
#  define KEY_4				52
#  define KEY_5				53
#  define KEY_6				54
#  define KEY_7				55
#  define KEY_8				56
#  define KEY_9				57
#  define KEY_0				48
#  define KEY_PLUS			61
#  define KEY_MINUS			45
# else
#  define KEY_LSHIFT		257
#  define KEY_RSHIFT		258
#  define KEY_LCTRL			260
#  define KEY_RCTRL			259
#  define KEY_ENTER			36
#  define KEY_SPACE			49
#  define KEY_ESC			53
#  define KEY_LEFT			123
#  define KEY_RIGHT			124
#  define KEY_UP			126
#  define KEY_DOWN			125
#  define KEY_A				0
#  define KEY_S				1
#  define KEY_D				2
#  define KEY_W				13
#  define KEY_R				15
#  define KEY_1				18
#  define KEY_2				19
#  define KEY_3				20
#  define KEY_4				21
#  define KEY_5				23
#  define KEY_6				22
#  define KEY_7				26
#  define KEY_8				28
#  define KEY_9				25
#  define KEY_0				29
#  define KEY_PLUS			24
#  define KEY_MINUS			27
# endif

#endif
