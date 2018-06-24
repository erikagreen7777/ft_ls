#include "../ft_ls.h"

/*
** - recursive path cat/cpy. Because of Norm
*/
void	recursive_cat(char *path, const char *name, struct dirent *entry)
{
    ft_strcpy(path, name);
    ft_strcat(path, "/");
    ft_strcat(path, entry->d_name);
    ft_printf("\n%s: \n", path);
}

void 	la_helper(char *str, t_lists *lists)
{
	DIR				*dip;
	char			arg[WORD_MAX];

	dip = opendir(str);
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	if (closedir(dip) == -1)
		ft_error("closedir");
	lists->filecount = directory_count(dip, str, 1);
	dip = opendir(str);
	read_helper_a(lists, 0, arg, dip);
	if (closedir(dip) == -1)
		ft_error("closedir");
}

