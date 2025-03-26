/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:36:04 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/26 05:38:09 by azolotarev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		str += write(1, str, 1);
}

void	ft_putu(unsigned int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putu(n / 10);
		ft_putu(n % 10);
	}
	else
	{
		c = '0' + n;
		write(1, &c, 1);
	}
}
