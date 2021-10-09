#include "get_next_line.h"

static char	*ft_secure(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

char	*ft_return(char **save)
{
	char	*rtn;
	char	*tmp;

	rtn = ft_substr(*save, 0, (ft_lenchr(*save, '\n') + 1));
	if (!rtn)
		return (NULL);
	tmp = *save;
	*save = ft_substr(tmp, ft_lenchr(tmp, '\n') + 1,
			(ft_strlen(tmp) - ft_lenchr(tmp, '\n') + 1));
	free(tmp);
	return (rtn);
}

char	*ft_lst_return(char **save)
{
	char	*rtn;

	rtn = *save;
	*save = NULL;
	return (rtn);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	int			ret;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	ret = 1;
	while (ret > 0 && !ft_strchr(save, '\n'))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (ft_secure(save));
		buff[ret] = '\0';
		if (ret)
			save = ft_strjoin(save, buff);
		if (!save)
			return (NULL);
	}
	if (!save || save[0] == '\0')
		return (ft_secure(save));
	if (ft_strchr(save, '\n'))
		return (ft_return(&save));
	else
		return (ft_lst_return(&save));
}
