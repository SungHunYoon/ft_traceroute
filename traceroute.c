/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:06 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/21 19:08:50 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int	main(int argc, char **args)
{
	t_info	info;

	if (getuid() != 0)
		error_handling("please check root privilege", 0);
	ft_bzero(&info, sizeof(info));
	parse_args(argc, args, &info);
	printf("traceroute to %s (%s), ", info.target_dns, info.target_ip);
	printf("64 hops max\n");
	initialize(&info);
	while (info.ttl <= info.max_ttl)
	{
		if (process(&info))
			break ;
	}
	close(info.udp_sock);
	close(info.raw_sock);
	if (info.isend)
		exit(FT_SUCCESS);
	else
		exit(FT_FAIL);
}
