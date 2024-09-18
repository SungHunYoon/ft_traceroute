/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:06 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:38:07 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int	main(int argc, char **args)
{
	t_info	info;

	if (getuid() != 0)
		error_handling("please check root privilege");
	ft_bzero(&info, sizeof(info));
	parse_args(argc, args, &info);
	process(&info);
	exit(FT_SUCCESS);
}
