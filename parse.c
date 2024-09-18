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

static int	parse_host(int argc, char **args, t_info *info)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(args[i]) && args[i][0] == '-')
			continue ;
		if (ft_strlen(info->target_ip) != 0)
			return (usage_error(args[i], i, PARSE_EXTRA));
		if (domain_to_fqdn(args[i], info->target_dns) || \
			domain_to_ip(info->target_dns, info->target_ip))
			return (usage_error(args[i], i, PARSE_HOST));
		printf("Target DNS : %s\n", info->target_dns);
		printf("Target IP : %s\n", info->target_ip);
		i++;
	}
	return (PARSE_SUCCESS);
}

static int	parse_option(int argc, char **args)
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
					return (help_message());
				else
					return (invalid_option(c, i, 0));
			}
			while (*c)
			{
				return (invalid_option(c, i, 1));
				c++;
			}
		}
		i++;
	}
	return (PARSE_SUCCESS);
}

int	parse_args(int argc, char **args, t_info *info)
{
	t_parse	ret;

	if (argc == 1)
		return (help_message());
	ret = parse_option(argc, args);
	if (ret != PARSE_SUCCESS)
		return (ret);
	ret = parse_host(argc, args, info);
	if (ret != PARSE_SUCCESS)
		return (ret);
	return (ret);
}
