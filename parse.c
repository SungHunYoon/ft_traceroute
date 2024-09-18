/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:15 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:39:56 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	parse_host(int argc, char **args, t_info *info)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(args[i]) && args[i][0] == '-')
			continue ;
		if (ft_strlen(info->target_ip) != 0)
			usage_error(args[i], i, PARSE_EXTRA);
		if (domain_to_fqdn(args[i], info->target_dns) || \
			domain_to_ip(info->target_dns, info->target_ip))
			usage_error(args[i], i, PARSE_HOST);
		i++;
	}
}

static void	parse_option(int argc, char **args)
{
	int		i;
	char	*c;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(args[i]) && args[i][0] == '-')
		{
			c = args[i] + 1;
			if (*c == '-')
			{
				if (ft_strncmp(c, "-help", 5) == 0)
					help_message();
				else
					invalid_option(c, i, 0);
			}
			while (*c)
			{
				invalid_option(c, i, 1);
				c++;
			}
		}
		i++;
	}
}

void	parse_args(int argc, char **args, t_info *info)
{
	if (argc == 1)
		help_message();
	parse_option(argc, args);
	parse_host(argc, args, info);
}
