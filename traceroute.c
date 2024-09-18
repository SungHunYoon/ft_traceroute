#include "traceroute.h"

int	main(int argc, char **args)
{
	int		ret;
	t_info	info;

	if (getuid() != 0)
		return (root_error());
	ft_bzero(&info, sizeof(info));
	ret = parse_args(argc, args, &info);
	if (ret == PARSE_HELP)
		return (FT_SUCCESS);
	else if (ret > PARSE_HELP)
		return (FT_ERROR);
	info.pid = getpid();
	return (FT_SUCCESS);
}
