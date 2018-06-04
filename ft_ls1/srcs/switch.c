#include "../ft_ls.h"
		
static void get_lengths(t_lists *lists)
{
	lists->timeleni = ft_strlen(lists->timearray[lists->i]);
	lists->timelenj = ft_strlen(lists->timearray[lists->j]);

	lists->destleni = ft_strlen(lists->dest[lists->i]);
	lists->destlenj = ft_strlen(lists->dest[lists->j]);
	
	lists->temp = (char *)malloc(lists->timeleni + 1);
	lists->tempdest = (char *)malloc(lists->destleni + 1);


}
		
void	ft_switch_time(t_lists *lists)
{
	lists->i = -1;
	while (++lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			/*
			** find the oldest time
			*/
			if (ft_atoi(lists->timearray[lists->i]) < ft_atoi(lists->timearray[lists->j]))
			{
				/*
				** get length of four things to malloc
				*/
				get_lengths(lists);
				// printf("before: lists->timearray[i]: %s: %s lists->timearray[j]: %s: %s\n", lists->timearray[lists->i], lists->dest[lists->i], lists->timearray[lists->j], lists->dest[lists->j]);
				lists->temp = ft_strdup(lists->timearray[lists->i]);
				lists->tempdest = ft_strdup(lists->dest[lists->i]);

				ft_bzero(lists->timearray[lists->i], lists->timeleni);
				ft_bzero(lists->dest[lists->i], lists->destleni);

				lists->timearray[lists->i] = ft_strdup(lists->timearray[lists->j]);
				lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);

				ft_bzero(lists->timearray[lists->j], lists->timelenj);
				ft_bzero(lists->dest[lists->j], lists->destlenj);

				lists->timearray[lists->j] = ft_strdup(lists->temp);
				lists->dest[lists->j] = ft_strdup(lists->tempdest);

				free(lists->temp);
				free(lists->tempdest);

				// printf("after: lists->timearray[i]: %s: %s lists->timearray[j]: %s: %s\n", lists->timearray[lists->i], lists->dest[lists->i], lists->timearray[lists->j], lists->dest[lists->j]);
				// ft_swap(lists->dest[i], lists->dest[j]);
			}
			lists->j++;
		}
	}
	/*
	** print off new array
	*/
	lists->i = -1;
	while (++lists->i < lists->filecount)
	printf("after: timearray[%d]: %s    %s\n", lists->i, lists->timearray[lists->i], lists->dest[lists->i]);

}
