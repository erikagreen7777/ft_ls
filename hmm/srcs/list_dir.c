/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_dir.c                            			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 13:21:09 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"


/*
** - ra helper
*/
static void list_dirr_helper_a(struct stat fileStat, char *arg, char *str, t_lists *lists)
{
	DIR				*dip;

	dip = NULL;
	if (S_ISDIR(fileStat.st_mode) == 1)
	{
		ft_strcpy(arg, str);
		if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
			ft_strcat(arg, "/");
		lists->filecount = directory_count(dip, str, 1);
		dip = opendir(str);
		read_helper_a(lists, 0, arg, dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
	}
}
/*
** - ls -r helper
*/
static void list_dirr_helper(struct stat fileStat, char *arg, char *str, t_lists *lists)
{
	DIR				*dip;

	dip = NULL;
	if (S_ISDIR(fileStat.st_mode) == 1)
	{
		ft_strcpy(arg, str);
		if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
			ft_strcat(arg, "/");
		lists->filecount = directory_count(dip, str, 0);
		dip = opendir(str);
		read_helper(lists, 0, arg, dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
	}
}

/*
** ls -r
*/
void	list_dirr(int argc, char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	j = 1;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
	while (++j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		list_dirr_helper(fileStat, arg, argv[j], lists);
		lex_sort(lists);
	}
}
/*
** - ls -ra
*/
void	ls_ra(/*int argc, */char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;
	char			arg[WORD_MAX];

	j = lists->argcount;
	while (j < lists->newargc)
	{
		if (j > lists->argcount && j < lists->newargc)
		{
			init_struct(&lists);
			write(1, "\n", 1);
		}
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		list_dirr_helper_a(fileStat, arg, argv[j], lists);
		lex_sort(lists);
		free_struct(lists);
		j++;
	}
}