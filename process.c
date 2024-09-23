/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:50:06 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/21 19:09:08 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	set_next_packet_info(t_info *info, int inc_flag)
{
	socklen_t	optlen;

	if (inc_flag)
	{
		info->ttl++;
		info->port_num++;
	}
	optlen = sizeof(info->ttl);
	if (setsockopt(info->udp_sock, IPPROTO_IP, IP_TTL, &info->ttl, optlen) < 0)
		error_handling("setsockopt", errno);
	info->dst_addr.sin_port = htons(info->port_num);
	info->prev = 0;
}

static void	send_udp_packet(t_info *info)
{
	const char	msg[] = "SUPERMAN";

	if (sendto(info->udp_sock, msg, sizeof(msg), 0, \
		(struct sockaddr *)&info->dst_addr, sizeof(info->dst_addr)) < 0)
		error_handling("sendto", errno);
	if (gettimeofday(&info->time, NULL) < 0)
		error_handling("gettimeofday", errno);
}

static int	recv_process(t_info *info)
{
	fd_set			reads;
	struct timeval	timeout;
	double			diff_time;
	size_t			tmp;
	int				ret;

	diff_time = diff_timeval(info->time);
	while (diff_time <= TIMEOUT_MS)
	{
		FD_ZERO(&reads);
		FD_SET(info->raw_sock, &reads);
		tmp = ((TIMEOUT_MS * TIME_MS) - (size_t)(diff_time * TIME_MS));
		timeout.tv_sec = tmp / TIME_US;
		timeout.tv_usec = tmp % TIME_US;
		ret = select(info->raw_sock + 1, &reads, NULL, NULL, &timeout);
		if (ret < 0)
			error_handling("select", errno);
		if (ret > 0 && FD_ISSET(info->raw_sock, &reads) && \
			recv_icmp_packet(info) == FT_SUCCESS)
			return (FT_SUCCESS);
		diff_time = diff_timeval(info->time);
	}
	return (FT_FAIL);
}

void	initialize(t_info *info)
{
	struct in_addr	ip_addr;

	info->udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (info->udp_sock < 0)
		error_handling("socket", errno);
	info->bind_addr.sin_family = AF_INET;
	info->bind_addr.sin_addr.s_addr = INADDR_ANY;
	info->bind_addr.sin_port = htons(BIND_PORT);
	while (info->bind_addr.sin_port < MAX_PORT && \
		bind(info->udp_sock, (struct sockaddr *)&info->bind_addr, \
			sizeof(info->bind_addr)) < 0)
		info->bind_addr.sin_port = htons(ntohs(info->bind_addr.sin_port) + 1);
	if (ntohs(info->bind_addr.sin_port) == 0)
		error_handling("bind", errno);
	info->raw_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (info->raw_sock < 0)
		error_handling("socket", errno);
	if (inet_pton(AF_INET, info->target_ip, &ip_addr) < 1)
		error_handling("inet_pton", errno);
	info->dst_addr.sin_family = AF_INET;
	info->dst_addr.sin_addr = ip_addr;
	info->ttl = 1;
	info->port_num = PORT_NUM;
	set_next_packet_info(info, FT_FALSE);
	info->max_ttl = MAX_TTL;
}

int	process(t_info *info)
{
	int	cnt;

	cnt = 0;
	printf(" %2d  ", info->ttl);
	while (cnt < ROUTE_CNT)
	{
		send_udp_packet(info);
		if (recv_process(info) == FT_SUCCESS)
		{
			if (info->prev != info->src_addr.sin_addr.s_addr)
				printf(" %s ", inet_ntoa(info->src_addr.sin_addr));
			printf(" %.3fms ", diff_timeval(info->time));
			if (info->error)
				printf("!%c ", info->error);
			info->prev = info->src_addr.sin_addr.s_addr;
		}
		else
			printf(" * ");
		fflush(stdout);
		cnt++;
	}
	printf("\n");
	set_next_packet_info(info, FT_TRUE);
	return (info->isend);
}
