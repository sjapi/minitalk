/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:58:56 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/26 06:10:28 by azolotarev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static	void	send_msg(pid_t pid, char *msg)
{
	int		i;
	int		j;
	char	c;
	int 	len;

	// send size
	len = 0;
	while (msg[len])
		len++;
	i = sizeof(int) * 8 - 1;
	while (i >= 0)
	{
		c = ((len >> i) & 0b1) + '0';
		write(1, &c, 1);
		if (c == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(50000);
	}
	
	// send msg
	write(1, "\n", 1);
	i = 0;
	while (msg[i])
	{
		j = 8 - 1;
		while (j >= 0)
		{
			c = ((msg[i] >> j) & 0b1) + '0';
			write(1, &c, 1);
			if (c == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(50000);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		send_msg(atoi(argv[1]), argv[2]);
	return (0);
}
