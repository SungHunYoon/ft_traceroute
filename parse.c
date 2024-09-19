/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:15 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/19 21:26:37 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	parse_host(int argc, char **args, t_info *info)
{
	int		i;
	char	*target;

	i = 1;
	while (i < argc)
	{
		if (!(ft_strlen(args[i]) && args[i][0] == '-'))
			target = args[i];
		i++;
	}
	if (domain_to_fqdn(target, info->target_dns) || \
		domain_to_ip(info->target_dns, info->target_ip))
		error_handling("unknown host");
}

static void	long_options(char *str)
{
	if (ft_strlen(str) == 2 && ft_strncmp(str, "--", 2) == 0)
		return ;
	else if (ft_strncmp(str, "--help", 6) == 0)
		help_message();
	else
		unrecognize_error(str);
}

static void	short_options(char *str)
{
	while (*str)
	{
		if (*str == '?')
			help_message();
		else
			invalid_option(*str);
		str++;
	}
}

static void	parse_options(int argc, char **args)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(args[i]) && args[i][0] == '-')
		{
			if (args[i][0] == '-' && args[i][1] == '-')
				long_options(args[i]);
			else
				short_options(args[i] + 1);
		}
		i++;
	}
}

void	parse_args(int argc, char **args, t_info *info)
{
	if (argc == 1)
		help_message();
	parse_options(argc, args);
	parse_host(argc, args, info);
}
