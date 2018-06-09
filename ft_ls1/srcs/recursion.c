#include "../ft_ls.h"

void list_dirbigr(int argc, const char *dir_name)
{
    DIR *d;
    d = opendir (dir_name);

    printf("argc: %d\n", argc);
    if (!d)
        ft_error(": No such file or directory");
    while (1) 
    {
        struct dirent *entry;
        const char *d_name;
        entry = readdir(d);

        if (!entry)
        {
            break;
        }
        d_name = entry->d_name;
        if (d_name[0] != '.')
	       ft_printf("%s\n", d_name);
        if (entry->d_type & DT_DIR) 
        {
            /* Check that the directory is not "d" or d's parent. */
            if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0) 
            {
                char newpath[PATH_MAX];
                int  newpath_length;
                newpath_length = ft_strlen(newpath);
                ft_strcpy(newpath, dir_name);
                ft_strcat(newpath, "/");
                ft_strcat(newpath, d_name);
                ft_printf("%s\n", newpath);
                if (newpath_length >= PATH_MAX)
                    ft_error("Path length too long");
                    /* Recursively call "list_dir" with the new path. */
                list_dirbigr(argc, newpath);
            }
    	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
            ft_error("closedir");
        exit (EXIT_FAILURE);
    }
}

