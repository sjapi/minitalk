/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:03:05 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/26 06:42:08 by azolotarev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h> // tmp for bzero
#include <stdio.h> // tmp for printf
#include "msg.h"

void	ft_putu(unsigned int n);
void	ft_putstr(char *str);

t_msg	g_msg;

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	char			bit;

	if (g_msg.pid != info->si_pid)
	{
		g_msg.pid = info->si_pid;
		g_msg.msg_len = 0;
		g_msg.bits_received = 0;
		if (g_msg.alloc)
			free(g_msg.msg);
		g_msg.alloc = 0;
	}
	bit = sig == SIGUSR2;
	if (g_msg.bits_received < (sizeof(unsigned int) * 8))
	{
		g_msg.msg_len = (g_msg.msg_len << 1) | bit;
	}
	if (g_msg.bits_received == (sizeof(unsigned int) * 8))
	{
		g_msg.msg = malloc(sizeof(char) * (g_msg.msg_len + 1));
		if (!g_msg.msg)
			exit(EXIT_FAILURE);
		bzero(g_msg.msg, g_msg.msg_len + 1);
	}
	if (g_msg.bits_received >= (sizeof(unsigned int) * 8))
	{
		// some fixes here§
		int	id = ((g_msg.bits_received - sizeof(unsigned int) * 8) / 8) - 1;
		g_msg.msg[id] = (g_msg.msg[id] << 1) | bit;
	}
	g_msg.bits_received++;
	if (g_msg.bits_received == g_msg.msg_len * 8 + (sizeof(unsigned int) * 8))
	{
		// ignores first letter
		write(1, g_msg.msg, g_msg.msg_len);
	} 
}

static int	listen(void)
{
	while (1)
		usleep(500000);
	return (0);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	printf("pid: %d\n", getpid());
	return (listen());
}
