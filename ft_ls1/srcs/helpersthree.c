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