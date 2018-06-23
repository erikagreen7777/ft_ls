#include "../ft_ls.h"

void null_check(const char *str)
{
    struct stat     fileStat;

    if(lstat(str, &fileStat) < 0) 
    {
        ft_printf("./ft_ls: %s: No such file or directory\n", str);
        exit (-1);
    } 
    printf("%s\n", str);
    exit (-1);
}