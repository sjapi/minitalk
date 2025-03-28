/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:56:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/03/26 17:56:00 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	reset_msg(t_msg *msg, pid_t pid)
{
	msg->pid = pid;
	msg->msg_len = 0;
	msg->bits_received = 0;
	if (msg->alloc)
		free(msg->msg);
	msg->alloc = 0;
}

void	msg_str_alloc(t_msg *msg)
{
	msg->msg = malloc(sizeof(char) * (msg->msg_len + 1));
	if (!msg->msg)
		exit(EXIT_FAILURE);
	msg->alloc = 1;
	ft_bzero(msg->msg, msg->msg_len + 1);
}

void	msg_str_add_bit(t_msg *msg, char bit)
{
	int	i;

	i = (msg->bits_received - INT_BITS) / 8;
	msg->msg[i] = (msg->msg[i] << 1) | bit;
}

void	msg_str_print_reset(t_msg *msg)
{
	ft_putstr(msg->msg);
	ft_putstr("\n");
	reset_msg(msg, 0);
}
