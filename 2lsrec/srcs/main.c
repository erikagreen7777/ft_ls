#include "../ft_ls.h"

static void
list_dir (const char *dir_name)
{
    DIR *d;

    /* Open the directory specified by "dir_name". */
    d = opendir (dir_name);

    /* Check it was opened. */
    if (!d) {
        fprintf (stderr, "mehCannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) 
    {
        struct dirent *entry;
        const char *d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir(d);
        if (!entry)
        {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
        if (d_name[0] != '.')
	       printf("d_name: %s\n", d_name);
        if (entry->d_type & DT_DIR) 
        {
            /* Check that the directory is not "d" or d's parent. */
// STRJOIN INTO BUFFER AND PRINT BUFFER AT THE END
    //-strcat will append instead of allocate
            if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0) 
            {
                char newpath[PATH_MAX];
                int  newpath_length;

                newpath_length = ft_strlen(newpath);
                ft_strcpy(newpath, dir_name);
                ft_strcat(newpath, "/");
                ft_strcat(newpath, d_name);
                printf("final newpath: %s\n", newpath);

                // int path_length = 0;
                // char path[PATH_MAX];
                // printf("(dir_name: %s\t\td_name: %s)\n", dir_name, d_name);
                // path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);
//DOES SNPRINTF AUTOMATICALLY FREE THE BUFFER?
    //just allocate on the stack for char[PATH_NAME] to avoid allocating memory
                // printf ("snprintf: %s\n", path);
                // if (path_length >= PATH_MAX)
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
