/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_icmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:23:50 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/23 10:39:01 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static uint16_t	calculate_checksum(uint16_t *data, int len)
{
	uint32_t	sum;

	sum = 0;
	while (len > 1)
	{
		sum += *data++;
		len -= 2;
	}
	if (len == 1)
		sum += *(uint8_t *)data;
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	return ((uint16_t)(~sum));
}

static void	set_error_code(t_info *info, struct icmp *icmp_hdr)
{
	const char	error_list[] = "NHPPFS789abcXVC";

	if (icmp_hdr->icmp_type != ICMP_UNREACH || \
		icmp_hdr->icmp_code > ICMP_UNREACH_PRECEDENCE_CUTOFF)
		return ;
	info->error = error_list[icmp_hdr->icmp_code];
}

static int	set_router_info(t_info *info, struct icmp *icmp_hdr)
{
	int	ret;

	ret = FT_FAIL;
	if (icmp_hdr->icmp_type == ICMP_UNREACH)
	{
		info->isend = FT_TRUE;
		ret = FT_SUCCESS;
		if (icmp_hdr->icmp_code != ICMP_UNREACH_PORT)
			set_error_code(info, icmp_hdr);
	}
	else if (icmp_hdr->icmp_type == ICMP_TIMXCEED)
		ret = FT_SUCCESS;
	return (ret);
}

static int	parse_icmp_packet(t_info *info, char *buf)
{
	struct ip		ip_hdr;
	struct icmp		icmp_hdr;
	struct udphdr	udp_hdr;
	uint16_t		cksum;
	uint16_t		cal_cksum;

	ft_memcpy(&ip_hdr, buf, IP_SIZE);
	ft_memcpy(&icmp_hdr, &buf[IP_SIZE], ICMP_SIZE);
	ft_memcpy(&udp_hdr, &buf[IP_SIZE + ICMP_SIZE], UDP_SIZE);
	cksum = icmp_hdr.icmp_cksum;
	ft_bzero(&buf[IP_SIZE + 2], 2);
	cal_cksum = calculate_checksum((uint16_t *)&buf[IP_SIZE], \
									ntohs(ip_hdr.ip_len));
	if ((cksum != cal_cksum) || \
		(icmp_hdr.icmp_dun.id_ip.idi_ip.ip_p != IPPROTO_UDP) || \
		(icmp_hdr.icmp_dun.id_ip.idi_ip.ip_dst.s_addr != \
		info->dst_addr.sin_addr.s_addr) || \
		(info->bind_addr.sin_port != udp_hdr.uh_sport) || \
		(info->dst_addr.sin_port != udp_hdr.uh_dport))
		return (FT_FAIL);
	return (set_router_info(info, &icmp_hdr));
}

int	recv_icmp_packet(t_info *info)
{
	char		buf[1024];
	socklen_t	socksize;

	ft_bzero(buf, sizeof(buf));
	socksize = sizeof(info->src_addr);
	if (recvfrom(info->raw_sock, buf, sizeof(buf), 0, \
		(struct sockaddr *)&info->src_addr, &socksize) < 0)
		error_handling("recvfrom", errno);
	return (parse_icmp_packet(info, buf));
}
