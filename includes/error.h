/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:53:39 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 04:51:41 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
* [colour-define] 
* 0 : reset
* 3 : underscore
* 30 - 37 : front colour
* 40 - 47 : background colour
*/
# define RESET	"\033[0m"
# define UNDER	"\033[3m"
# define BLACK	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define MAGEN	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define BBLACK	"\033[40m"
# define BRED	"\033[41m"
# define BGREEN	"\033[42m"
# define BYELL	"\033[43m"
# define BBLUE	"\033[44m"
# define BMAGEN	"\033[45m"
# define BCYAN	"\033[46m"
# define BWHITE	"\033[47m"

/*
* [error_string-define]
*/
# define FAIL_TRIM "ERROR::ft_strtrim is unsuccesful triming the string."
# define FAIL_ALLOC "ERROR::ft_calloc is unsuccessful allocating memmory."
# define FAIL_SPLIT "ERROR::ft_calloc is unsuccessful spliting the string."
/*
* ambient_information */
# define MANY_AM "ERROR::too many information input for ambient light."
# define INVALID_ID_A "ERROR::invalid indentifier input for ambient light."
# define LESS_AM "ERROR::too less information input for ambient light."
# define INVALID_RA_A "ERROR::invalid ratio input value for ambient light."
/*
* camera_information */
# define MANY_C "ERROR::too many information input for camara element."
# define INVALID_IDENT_C "ERROR::invalid indentifier input for camara."
# define LESS_C "ERROR::too less information input for camara element."
# define NORM_C "ERROR::invalid normalize orientation vector for camara."
# define IN_FOV "ERROR::invalid horizontal field of view value for camara."
/*
* light_infomation */
# define MANY_L "ERROR::too many information input for light element."
# define INVALID_IDENT_L "ERROR::invalid indentifier input for light."
# define LESS_L "ERROR::too less information input for light element."
# define BRIGHT_L "ERROR::invalid brightness ratio input value for light."
/*
* sphere_information */
# define MANY_SP "ERROR::too many information input for sphere element."
# define INVALID_IDENT_SP "ERROR::invalid indentifier input for sphere."
# define LESS_SP "ERROR::too less information input for sphere element."
/*
* plane_information */
# define MANY_PL "ERROR::too many information input for plane element."
# define INVALID_IDENT_PL "ERROR::invalid indentifier input for plane."
# define LESS_PL "ERROR::too less information input for plane element."
# define NORM_PL "ERROR::invalid normalize orientation vector for plane"
/*
* cylinder_information */
# define MANY_CY "ERROR::too many information input for cylinder element."
# define INVALID_IDENT_CY "ERROR::invalid indentifier input for cylinder."
# define LESS_CY "ERROR::too less information input for cylinder element."
# define NORM_CY "ERROR::invalid normalize orientation vector for cylinder."
/*
* cone_information */
# define MANY_CO "ERROR::too many information input for cone element."
# define INVALID_IDENT_CO "ERROR::invalid indentifier input for cone."
# define LESS_CO "ERROR::too less information input for cone element."
# define NORM_CO "ERROR::invalid normalize orientation vector for cone."

#endif
