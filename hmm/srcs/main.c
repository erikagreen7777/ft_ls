/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                             			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 15:16:00 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

void		init_struct(t_lists **lists)
{
	*lists = (t_lists *)ft_memalloc(sizeof(t_lists));
	(*lists)->timearray = NULL;
	(*lists)->filecount = 0;
	(*lists)->dest = NULL;
	(*lists)->tflag = 0;
	(*lists)->big_r_flag = 0;
	(*lists)->rflag = 0;
	(*lists)->lflag = 0;
	(*lists)->aflag = 0;
	(*lists)->k = 0;
	(*lists)->i = 0;
	(*lists)->j = 0;
	(*lists)->newargc = 0;
	(*lists)->firstarg = 0;
	(*lists)->timearrayflag = 0;
	(*lists)->size = 0;
}

void	free_struct(t_lists *lists)
{
	int i;
	i = 0;
	while (i < lists->filecount)
	{
		free(lists->dest[i]);
		i++;
	}
	if (lists->timearrayflag > 0)
	{
		free(lists->timearray);
	}
	ft_memdel((void*)&lists->timearray);
	ft_memdel((void*)&lists->dest);
	free(lists->dest);
	free(lists);
}

int main(int argc, char **argv)
{
	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		t_lists *lists;
		lists = NULL;
		/*
		** ls with no args
		*/
		if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], ".") == 0))
		{
			list_dir(argc, argv);
		}
		else if (argc >= 2)
		{
			init_struct(&lists);
			lists->newargc = arg_parsing(argc, argv, lists);
			the_start(argc, argv, lists);
			list_dir(argc, argv);
			free_struct(lists);
		}
		else
			ft_error("main: ./ft_ls error");
	}
	return (0);
}

/*
** - ls -t helper
*/
static void		lsr_helper(struct stat fileStat, char *arg, char *str, t_lists *lists)
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
		read_helper(lists, 1, arg, dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
		ft_switch_time(lists);
		print_lists(lists);
	}
}
/*
** ls -t
*/
void	list_dirt(int argc, char **argv, t_lists *lists)
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
		lsr_helper(fileStat, arg, argv[j], lists);
		free_some_stuff(lists);
	}
}