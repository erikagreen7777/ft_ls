#include "../ft_ls.h"

static void list_dir(const char *dir_name)
{
    DIR *d;
    d = opendir (dir_name);

    if (!d)
    {
        printf("Cannot open directory '%s': %s\n", dir_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
    while (1) 
    {
        struct dirent *entry;
        const char *d_name;
        entry = readdir(d);

        if (!entry)
        {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        if (d_name[0] != '.')
	       printf("d_name: %s\n", d_name);
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
                printf("final newpath: %s\n", newpath);
                if (newpath_length >= PATH_MAX)
                {
                    ft_printf ("Path length too long.\n");
                    exit(EXIT_FAILURE);
                }
                    /* Recursively call "list_dir" with the new path. */
                list_dir (newpath);
            }
    	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: <directory>");
        return (1);
    }
    list_dir (argv[1]);
    return 0;
}
