#include "minishell.h"

char *ft_strdup(char *s)
{
	char *dup;
	int i;

	i = 0;
	if (!s)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *s3;
	int	i;
	int j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char *ft_substr(char *str, int start, int ammount)
{
	int i;
	char *sub;

	i = 0;
	if (!str)
		return (NULL);
	sub = malloc(sizeof(char) * (ammount + 1));
	if (!sub)
		return (NULL);
	while (str[start] != '\0' && ammount > 0)
	{
		sub[i] = str[start];
		i++;
		start++;
		ammount--;
	}
	sub[i] = '\0';
	return (sub);
}

int ft_strchr(char c, char *s)
{
	int i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char *store_buffer(char *holder, char *buff)
{
	char *temp;

	if (holder)
	{
		temp = ft_strjoin(holder, buff);
		free(holder);
		holder = ft_strdup(temp);
		free(temp);
	}
	else
	{
		holder = ft_strdup(buff); // if holder == NULL it means we had a file with no nl ?
		if (holder == NULL)
			return (NULL);
	}
	return (holder);
}

char *store_line(char **line, char *holder, int ret)
{
	char	*temp;
	int		i;

	i = 0;
	if (!holder)
		return (NULL);
	while (holder[i] != '\0')
	{
		if (holder[i] == '\n')
			break ;
		i++;
	}

	if (i < ft_strlen(holder)) // If we got here cause there's a nl somewhere in holder
	{
		*line = ft_substr(holder, 0, i + 1);
		temp = ft_substr(holder, i + 1, ft_strlen(holder));
		free(holder);
		holder = ft_strdup(temp);
		if (temp)
			free(temp);
	}
	else if (ret == 0) // if we've read till EOF
	{
		if (holder[0] == '\0') //for the possibility of a file with no nl!!
			return (NULL);
		*line = holder;
		holder = NULL;
	}
	return (holder);
}

char *get_next_line(int fd)
{
	static char	*holder[1024];
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	if (fd < 0 || read(fd, holder[fd], 0) < 0)
		return (NULL);

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);

		buff[ret] = '\0';
		
		holder[fd] = store_buffer(holder[fd], buff);

		if (ft_strchr('\n', buff))
			break ;
	}

	if (ret == 0 && !holder[fd]) // Edge case: file with just EOF
	{
		line = ft_strdup("");
		return (line);
	}

	if (ret == 0 && ft_strlen(holder[fd]) == ft_strchr('\n', holder[fd])) // Edge case: read till end of file but:
	{
		if (ft_strlen(holder[fd]) == 0) // Either it was just an empty file
			return (NULL);

		// Or it was a file that ended in a nl
		line = ft_strdup(holder[fd]);
		free(holder[fd]);
		return (line);
	}

	holder[fd] = store_line(&line, holder[fd], ret);

	if (!holder[fd] && ret == 0 && !line)
		return (NULL);

	return (line);
}
