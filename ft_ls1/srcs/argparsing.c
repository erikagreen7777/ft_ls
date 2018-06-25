#include "../ft_ls.h"

/*
** - flag parsing
*/
static void flag_parsing(char *str, t_lists *lists)
{
	int 	i;
	i = 1;
	while (str[i])
	{
		if (ft_strncmp(&str[i], "r", 1) == 0)
			lists->rflag++;
		else if (ft_strncmp(&str[i], "t", 1) == 0)
			lists->tflag++;
		else if (ft_strncmp(&str[i], "R", 1) == 0)
			lists->big_r_flag++;
		else if (ft_strncmp(&str[i], "l", 1) == 0)
			lists->lflag++;
		else if (ft_strncmp(&str[i], "a", 1) == 0)
			lists->aflag++;
		else
			ft_error(".");
		i++;
	}
}
/*
** - argument parsing for flag and arc
*/
void	arg_parsing(int argc, char **argv, t_lists *lists)
{
	lists->argcount = 0;
	lists->i = 0;
	while (lists->i < argc)
	{
		if (ft_strncmp(argv[lists->i], "-", 1) == 0)
		{
			// printf("argv[%d]: %s\n", lists->i, argv[lists->i]);
			flag_parsing(argv[lists->i], lists);
			lists->argcount++;
		}
		lists->i++;
	}
	lists->argcount++;
	printf("argcount: %d\nargc: %d\n", lists->argcount, argc);
	if (lists->argcount == argc)
	{
		lists->argcount++;
		argv[lists->argcount] = ".";
		argc++;
	}
	// printf("argv[%d]: %s\n", lists->argcount, argv[lists->argcount]);
	// printf("new argcount: %d\nnew argc: %d\n", lists->argcount, argc);

}