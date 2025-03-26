/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:58:56 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/26 18:55:25 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void	handler(int sig)
{
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	send_msg_len(int len, pid_t pid)
{
	int		i;
	char	bit;

	i = sizeof(int) * 8 - 1;
	while (i >= 0)
	{
		bit = (len >> i) & 0b1;
// DEBUG
		char wbit = '0' + bit;
		write(1, &wbit, 1);
// DEBUG
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(500);
	}
	write(1, "\n", 1);
}

static	void	send_msg(char *msg, pid_t pid)
{
	int		i;
	int		j;
	char	bit;
	int 	len;

	len = ft_strlen(msg);
	if (len == 0)
		return ;
	send_msg_len(len, pid);
	i = 0;
	while (i < ft_strlen(msg))
	{
		j = 8 - 1;
		while (j >= 0)
		{
			bit = (msg[i] >> j) & 0b1;
// DEBUG
			char wbit = '0' + bit;
			write(1, &wbit, 1);
// DEBUG
			if (bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(500);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_msg(argv[2], atoi(argv[1]));
	return (0);
}
