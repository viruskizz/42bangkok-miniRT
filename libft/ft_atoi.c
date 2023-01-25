/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:06:01 by tsomsa            #+#    #+#             */
/*   Updated: 2023/01/25 21:46:47 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_atoi(const char *nb)
{
	int	prefix;
	int	number;

	number = 0;
	if (*nb == '\0' || *nb == '\e')
		return (0);
	while (*nb <= 32)
		nb++;
	if (*nb == '-')
		prefix = -1;
	else
		prefix = 1;
	if (*nb == '-' || *nb == '+')
		nb++;
	while (ft_isdigit(*nb))
		number = (number * 10) + (*nb++ - '0');
	if (*nb)
	{
		printf("minirt: invalid character for value in ft_itoa.\n");
		exit (1);
	}
	return (prefix * number);
}
