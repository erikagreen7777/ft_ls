/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_dir2.c                           			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 15:07:40 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"
/*
** ls 
*/
void	list_dir(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	int				j;
	j = 0;
	if (argc == 1)
	{
		argv[j + 1] = ".";
		argc = 2;
	}
	while (++j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
			null_check(argv[j]);
		while ((dit = readdir(dip)) != NULL)
		{
			if (dit->d_name[0] != '.')
				ft_printf("%s\n", dit->d_name);
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
	}
}
/*
** ls -a
*/
void	list_dira(int argc, char **argv, t_lists *lists)
{
	DIR				*dip;
	struct dirent	*dit;
	lists->j = 1;

	if (argc == 2)
	{
		argv[2] = ".";
		argc = 3;
	}
	while (++lists->j < argc)
	{
		if (lists->j > 2 && lists->j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[lists->j]);
		if (dip == NULL)
			null_check(argv[lists->j]);
		while ((dit = readdir(dip)) != NULL)
			ft_printf("%s\n", dit->d_name);
		if (closedir(dip) == -1)
			ft_error("closedir");
	}
}

/*
** - ls -l helper
*/
static void ls_l_helper(struct stat fileStat, char *arg, char *str, t_lists *lists)
{
	DIR				*dip;
	dip = NULL;

	if (S_ISDIR(fileStat.st_mode) == 1)
	{
		dip = opendir(str);
		ft_strcpy(arg, str);
		if (ft_strcmp(arg, "/dev") == 0)
			lists->flag = 1;
		if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
			ft_strcat(arg, "/");
		if (closedir(dip) == -1)
			ft_error("closedir");
		lists->filecount = directory_count(dip, str, 0);
		dip = opendir(str);
		read_helper(lists, 0, arg, dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
		ls_stat_helper(lists);
	}
}
/*
** ls -l
*/
void	list_dirl(int argc, char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;
	char			arg[WORD_MAX];

	j = 1;
	lists->flag = 0;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
	while (++j < argc)
	{
		if (j > 2 && j < argc)
		{
			write(1, "\n", 1);
			init_struct(&lists);
		}
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		ls_l_helper(fileStat, arg, argv[j], lists);
		free_struct(lists);
	}
}