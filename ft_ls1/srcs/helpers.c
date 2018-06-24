#include "../ft_ls.h"

void				read_helper_guts_a(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag)
{
	if (lists->i > 0)
		ft_strcpy(arg, temp);
	ft_strcat(arg, dit->d_name);
	lists->dest[lists->i] = ft_strdup(arg);
	ft_bzero(arg, ft_strlen(arg));
	if (flag == 1)
		lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
	lists->i++;
}

void				read_helper_guts(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag)
{
	if (dit->d_name[0] != '.')
	{
		if (lists->i > 0)
			ft_strcpy(arg, temp);
		ft_strcat(arg, dit->d_name);
		lists->dest[lists->i] = ft_strdup(arg);
		ft_bzero(arg, ft_strlen(arg));
		if (flag == 1)
			lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
		lists->i++;
	}
}

// void	free_helper_stuff()
// {

// }

void				read_helper(t_lists *lists, int flag, char *arg, DIR *dip)
{
	char			temp[WORD_MAX];
	struct dirent	*dit;
	
	lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
	if (flag == 1)
		lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
	if (dip == NULL)
	{
		ft_error(": No file or directory");
	}
	ft_strcpy(temp, arg);
	while ((dit = readdir(dip)) != NULL)
	{
		read_helper_guts(lists, arg, dit, temp, flag);
	}
}
/*
** -read helper for -a
*/
void				read_helper_a(t_lists *lists, int flag, char *arg, DIR *dip)
{
	char			temp[WORD_MAX];
	struct dirent	*dit;
	
	lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
	if (flag == 1)
		lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
	if (dip == NULL)
	{
		ft_error(": No file or directory");
	}
	ft_strcpy(temp, arg);
	while ((dit = readdir(dip)) != NULL)
	{
		read_helper_guts_a(lists, arg, dit, temp, flag);
	}
}
/*
** - print lists
*/
void				print_lists(t_lists *lists)
{
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ft_printf("%s\n", lists->dest[lists->i]);
	lists->i = -1;
	while (++lists->i < lists->filecount)
		free(lists->dest[lists->i]);
}
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
    // struct dirent   *dit;
    // struct stat     fileStat;
    // char            **array;
	char			arg[WORD_MAX];
    // char            temp[WORD_MAX];
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
	return (0);
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
    // struct dirent   *dit;
	char			arg[WORD_MAX];
    // char            temp[WORD_MAX];
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
	return (0);
}
/*
** - Rrt helper
*/
int				rbigrt_helper(const char *str, int flag, t_lists *lists)
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
	print_lists_back(lists);
	return (0);
}
/*
** - used for -Rrlta
*/
int				everything_helper(const char *str, int flag, t_lists *lists)
{
	DIR			*dip;
	char		arg[WORD_MAX];
	lists->size = 0;
	lists->i = 0;
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	dip = opendir(str);
	if (dip == NULL)
		null_check(str);
	rt_helper_helper(dip, lists, arg, flag);
	ft_switch_time(lists);
	if (closedir(dip) == -1)
		ft_error("closedir");
	r_recursive_ls_stat_helper(lists);
	return (0);
}
