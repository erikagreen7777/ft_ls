/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   argparsing.c                         			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 11:58:00 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
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
int/*void*/	arg_parsing(int argc, char **argv, t_lists *lists)
{
	lists->argcount = 0;
	lists->i = 0;
	while (lists->i < argc)
	{
		if (ft_strncmp(argv[lists->i], "-", 1) == 0)
		{
			flag_parsing(argv[lists->i], lists);
			lists->argcount++;
		}
		lists->i++;
	}
	lists->argcount++;
	lists->firstarg = lists->argcount;
	if (lists->argcount == argc)
	{
		argv[lists->argcount] = ".";
		argc++;
	}
	return (argc);
}