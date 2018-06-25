#include "../ft_ls.h"
/*
** - print lists backwards (for -r flags)
*/
void				print_lists_back(t_lists *lists)
{
	lists->i = lists->filecount;
	while (--lists->i > -1)
		ft_printf("%s\n", lists->dest[lists->i]);
}
/*
** ls -Rr helper
*/
int					Rr_helper(const char *str, int flag, t_lists *lists)
{
	DIR				*dip;
	char			arg[WORD_MAX];

	lists->i = 0;
	ft_strcpy(arg, str);
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	dip = opendir(str);
	if (dip == NULL)
		null_check(str);
	rl_helper_helper(dip, lists, arg, flag);
	if (closedir(dip) == -1)
		ft_error("closedir");
	lex_sort(lists);
	free_some_stuff(lists);
	return (0);
}
void free_some_stuff(t_lists *lists)
{
	int i;
	i = 0;
	while (i < lists->filecount)
	{
		if (lists->timearrayflag > 0)
			free(lists->timearray[i]);
		free(lists->dest[i]);
		i++;
	}
	free(lists->timearray);
	free(lists->dest);
}
/*
** ls -Rt helper
*/
int				Rt_helper(const char *str, int flag, t_lists *lists)
{
	DIR			*dip;
	char		arg[WORD_MAX];
	
	lists->i = 0;
	ft_strcpy(arg, str);
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	dip = opendir(str);
	if (dip == NULL)
		null_check(str);
	rt_helper_helper(dip, lists, arg, flag);
	if (closedir(dip) == -1)
		ft_error("closedir");
	ft_switch_time(lists);
	print_lists(lists);
	free_some_stuff(lists);
	return (0);
}
/*
** ls -R helper
*/
int					R_helper(const char *str, int flag)
{
	DIR				*dip;
	struct dirent	*dit;
	
	dip = opendir(str);
	if (dip == NULL)
		null_check(str);
	while ((dit = readdir(dip)) != NULL)
	{
		if (flag == 0)
		{
			if (dit->d_name[0] != '.')
				ft_printf("%s\n", dit->d_name);
		}
		else if (flag == 1)
			ft_printf("%s\n", dit->d_name);
	}
	if (closedir(dip) == -1)
		ft_error("closedir");
	return (0);
}
/*
** ls -Rl helper
*/
int					Rl_helper(const char *str, int flag, t_lists *lists)
{
	DIR				*dip;
	char			arg[WORD_MAX];

	lists->i = 0;
	lists->size = 0;
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	dip = opendir(str);
	if (dip == NULL)
		null_check(str);
	rl_helper_helper(dip, lists, arg, flag);
	if (closedir(dip) == -1)
		ft_error("closedir");
	recursive_ls_stat_helper(lists);
	free_some_stuff(lists);
	return (0);
}

