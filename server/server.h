/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:48:58 by azolotar          #+#    #+#             */
/*   Updated: 2025/03/28 18:57:02 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>

# ifndef INT_BITS
#  define INT_BITS 32
# endif 

typedef struct s_msg
{
	pid_t			pid;
	unsigned int	bits_received;
	unsigned int	msg_len;
	char			alloc;
	char			*msg;
}	t_msg;

/* msg.c */
void	reset_msg(t_msg *msg, pid_t pid);

void	msg_str_alloc(t_msg *msg);

void	msg_str_add_bit(t_msg *msg, char bit);

void	msg_str_print_reset(t_msg *msg);

/* utils.c */
void	ft_bzero(void *s, size_t n);

void	ft_putstr(char *str);

void	ft_putu(unsigned int n);

#endif
