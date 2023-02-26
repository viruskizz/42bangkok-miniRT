/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:53:39 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 00:35:58 by sharnvon         ###   ########.fr       */
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
# define FAIL_TRIM \
"minirt: ERROR::ft_strtrim is unsuccesful triming the string.\n"
# define FAIL_ALLOC \
"minirt: ERROR::ft_calloc is unsuccessful allocating memmory.\n"
# define FAIL_SPLIT \
"minirt: ERROR::ft_calloc is unsuccessful spliting the string.\n"
/*
* ambient_information
*/
# define TOO_MANY_INPUT_A \
"minirt: ERROR::too many information input for ambient light.\n" \
"(hint) ambient information input must be 3 in order and seperate with space.\n" \
"(hint) • identifier : A\n" \
"(hint) • ambient lighting ratio : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) A   0.2   255,255,255\n"
# define INVALID_IDENT_A \
"minirt: ERROR::invalid indentifier input for ambient light.\n" \
"(hint) • the first input must be identifier wiht 'A' character.\n"
# define TOO_LESS_INPUT_A \
"minirt: ERROR::too less information input for ambient light.\n" \
"(hint) ambient information input must be 3 in order and seperate with space.\n" \
"(hint) • identifier : A\n" \
"(hint) • ambient lighting ratio : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) A   0.2   255,255,255\n"
# define INVALID_RATIO_A \
"minirt: ERROR::invalid ration input value for ambient lighting.\n" \
"(hint) • the ambient lighting ratio input must be in range 0.0-1.0.\n"
/*
* ambient_information
*/
# define TOO_MANY_INPUT_C \
"minirt: ERROR::too many information input for camara element.\n" \
"(hint) camara information input must be 4 in order and seperate with space.\n" \
"(hint) • identifier : C\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • horizontal field of view in degree : 0-180\n" \
"(sample) C -50,0,0.20    0,0,1   70\n"
# define INVALID_IDENT_C \
"minirt: ERROR::invalid indentifier input for camara.\n" \
"(hint) • the first input must be identifier wiht 'C' character.\n"
# define TOO_LESS_INPUT_C \
"minirt: ERROR::too less information input for camara element.\n" \
"(hint) camara information input must be 4 in order and seperate with space.\n" \
"(hint) • identifier : C\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • horizontal field of view in degree : 0-180\n" \
"(sample) C -50,0,0.20    0,0,1   70\n"
# define INVALID_NORM_C \
"minirt: ERROR::invalid normalize orientation vector input value for camara\n" \
"(hint) • the normalized orientation vector input must in XYZ seperate by ','.\n" \
"(hint) • each value must be in range 0.0-1.0.\n"
# define INVALID_FOV_C \
"minirt: ERROR::invalid horizontal field of view input value for camara.\n" \
"(hint) • the field of view degree input must be in range 0-180.\n"
/*
* light_infomation
*/
# define TOO_MANY_INPUT_L \
"minirt: ERROR::too many information input for light element.\n" \
"(hint) light information input must be 3-4 in order and seperate with space.\n" \
"(hint) • identifier : L\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • brightness ratio : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) L    -40.0,50.0,0.0  0.6     10,0,255\n"
# define INVALID_IDENT_L \
"minirt: ERROR::invalid indentifier input for light.\n" \
"(hint) • the first input must be identifier wiht 'L' character.\n"
# define TOO_LESS_INPUT_L \
"minirt: ERROR::too less information input for light element.\n" \
"(hint) light information input must be 3-4 in order and seperate with space.\n" \
"(hint) • identifier : L\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • brightness ratio : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) L    -40.0,50.0,0.0  0.6     10,0,255\n"
# define INVALID_NORM_L \
"minirt: ERROR::invalid normalize orientation vector input value for camara\n" \
"(hint) • the normalized orientation vector input must in XYZ seperate by ','.\n" \
"(hint) • each value must be in range 0.0-1.0.\n"
# define INVALID_BRIGHT_L \
"minirt: ERROR::invalid brightness ratio input value for light.\n" \
"(hint) • the light brightness ratio input must be in range 0.0-1.0.\n"
/*
* sphere_information
*/
# define TOO_MANY_INPUT_SP \
"minirt: ERROR::too many information input for sphere element.\n" \
"(hint) sphere information input must be 3-4 in order and seperate with space.\n" \
"(hint) • identifier : sp\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • the sphere diameter\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) sp  0.0,0.0,20.6     12.6   10,0,255\n"
# define INVALID_IDENT_SP \
"minirt: ERROR::invalid indentifier input for sphere.\n" \
"(hint) • the first input must be identifier wiht 'sp' character.\n"
# define TOO_LESS_INPUT_SP \
"minirt: ERROR::too less information input for sphere element.\n" \
"(hint) sphere information input must be 3-4 in order and seperate with space.\n" \
"(hint) • identifier : sp\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • the sphere diameter\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) sp  0.0,0.0,20.6     12.6   10,0,255\n"
/*
* plane_information
*/
# define TOO_MANY_INPUT_PL \
"minirt: ERROR::too many information input for plane element.\n" \
"(hint) sphere information input must be 4 in order and seperate with space.\n" \
"(hint) • identifier : pl\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) pl  0.0,0.0,-10.0   0.0,1.0,0.0   10,0,255\n"
# define INVALID_IDENT_PL \
"minirt: ERROR::invalid indentifier input for plane.\n" \
"(hint) • the first input must be identifier wiht 'pl' character.\n"
# define TOO_LESS_INPUT_PL \
"minirt: ERROR::too less information input for plane element.\n" \
"(hint) sphere information input must be 4 in order and seperate with space.\n" \
"(hint) • identifier : pl\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) pl  0.0,0.0,-10.0   0.0,1.0,0.0   10,0,255\n"
# define INVALID_NORM_PL \
"minirt: ERROR::invalid normalize orientation vector input value for plane\n" \
"(hint) • the normalized orientation vector input must in XYZ seperate by ','.\n" \
"(hint) • each value must be in range 0.0-1.0.\n"
/*
* plane_information
*/
# define TOO_MANY_INPUT_CY \
"minirt: ERROR::too many information input for cylinder element.\n" \
"(hint) cylinder information input must be 6 in order and seperate with space.\n" \
"(hint) • identifier : cy\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • the cylinder diameter.\n" \
"(hint) • the cylinder height.\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) cy  50.0,0.0,20.6   0.0,0.0,1.0  14.2 21.42   10,0,255\n"
# define INVALID_IDENT_CY \
"minirt: ERROR::invalid indentifier input for cylinder.\n" \
"(hint) • the first input must be identifier wiht 'cy' character.\n"
# define TOO_LESS_INPUT_CY \
"minirt: ERROR::too less information input for cylinder element.\n" \
"(hint) cylinder information input must be 6 in order and seperate with space.\n" \
"(hint) • identifier : cy\n" \
"(hint) • coordinete in XYZ seperate with ','\n" \
"(hint) • normalize orientation vector in XYZ seperate with ',' : 0.0-1.0\n" \
"(hint) • the cylinder diameter.\n" \
"(hint) • the cylinder height.\n" \
"(hint) • color in RGB seperate with ',' : 0-255\n" \
"(sample) cy  50.0,0.0,20.6   0.0,0.0,1.0  14.2 21.42   10,0,255\n"
# define INVALID_NORM_CY \
"minirt: ERROR::invalid normalize orientation vector input value for plane\n" \
"(hint) • the normalized orientation vector input must in XYZ seperate by ','.\n" \
"(hint) • each value must be in range 0.0-1.0.\n"

#endif