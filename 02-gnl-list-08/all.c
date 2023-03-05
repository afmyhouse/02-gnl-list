/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:12:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/03/05 18:19:45 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s || !*s)
		return (NULL);
	str = (char *)s;
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
} 

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len;
	char	*dst;
	char	*ret;

	if (!s1 || !*s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ret = dst;
	if (s1)
	{
		while (*s1)
			*dst++ = *s1++;
		free((void *)(s1 - (dst - ret)));
	}
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	return (ret);
}

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned long	i;

	if (!str)
		return (NULL);
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub)
	{

		while (i < len && str[start + i] != '\0')
		{
			sub[i] = str[start + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}

t_fd_lst	*check_fd(int fd, t_fd_lst **list)
{
	t_fd_lst	*ptr;
	t_fd_lst	*tmp;

	ptr = *list;
	tmp = *list;
	while (ptr != NULL)
	{
		if ((ptr->fd) == fd)
		{
			if (ptr != tmp)
			{
				tmp->next = ptr->next;
				ptr->next = *list;
				*list = ptr;
			}
			return (ptr->nl = NULL, ptr);
		}
		tmp = ptr;
		ptr = ptr->next;
	}
	ptr = (t_fd_lst *)malloc(sizeof(t_fd_lst));
	if (!ptr)
		return (NULL);
	*ptr = (t_fd_lst){fd, NULL, NULL, 1, *list};
	return (*list = ptr, ptr);
}

int	new_line(t_fd_lst *node)
{
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	buff[0] = '\0';
	while (node->ret != 0 && !ft_strchr(buff, '\n'))
	{
		node->ret = read(node->fd, buff, BUFFER_SIZE);
		if (node->ret < 0)
		{
			ft_free(&buff);
			node->ret = 0;
			return (0);
		}
		buff[node->ret] = '\0';
		if (node->ret)
			node->raw = ft_strjoin_free(node->raw, buff);
	}
	ft_free(&buff);
	return (1);
}

int	next_line(t_fd_lst *node)
{
	int		len;
	int		i;
	char	*tmp;
	
	i = 0;
	if (!ft_strchr(node->raw, '\n') && node->ret)
		new_line(node);
	if (node->raw && *node->raw)
	{
		len = ft_strlen(node->raw);
		tmp = node->raw;
		while (node->raw[i] && node->raw[i] != '\n')
			i++;
		if (node->raw[i] == '\n')
		{
			i++;
			node->nl = ft_strsub(node->raw, 0, i);
			node->raw = ft_strsub(node->raw, i, len - i);
			if (!*node->raw)
				ft_free(&node->raw);
			free(tmp);
			return (1);
		}
		node->nl = node->raw;
	}
	node->raw = NULL;
	node->ret = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fd_lst	*fd_lst;
	t_fd_lst		*node;
	char 			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = check_fd(fd, &fd_lst);
	if (node == NULL)
		return (NULL);
	//node->nl = NULL;
	next_line(node);
	line = node->nl;
	if ((node->ret == 0 || node->ret == -1) && (!node->nl || !*node->nl))
	{
		fd_lst = node->next;
		free(node);
	}
	return (node->nl);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		fd3, fd4, fd5, fd6;
	char	*line3, *line4, *line5, *line6;
	int 	i = 1;

	//fd1 = open("./files/multiple_nlx5", O_RDONLY);
	fd3 = open(FILE_3, O_RDONLY);
	fd4 = open(FILE_4, O_RDONLY);
	fd5 = open(FILE_5, O_RDONLY);
	fd6 = open(FILE_6, O_RDONLY);
	printf("BUFFER_SIZE = %i\n", BUFFER_SIZE);
	printf("file 3 : %s\n", FILE_3);
	printf("\n____________________line at a time____________________\n");
	printf("\n____________________line %i____________________\n",i);

	fd = 1;
	while (fd)
	{
		fd =0;
		if ((line = get_next_line(fd3)))
		{
			fd = 1;
			printf("--------- fd%d :", fd3);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd4)))
		{
			fd = 1;
			printf("--------- fd%d :", fd4);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd5)))
		{
			fd = 1;
			printf("--------- fd%d :", fd5);
			printf("%s", line);
			free(line);
		}
		if ((line = get_next_line(fd6)))
		{
			fd = 1;
			printf("--------- fd%d :", fd6);
			printf("%s", line);
			free(line);
		}
		++i;
		if (i == 10)
			printf("\n__________________BREAKPOINT____________________\n");
		if (fd)
			printf("\n____________________line %i____________________\n",i);
	}

	close(fd3);
	close(fd4);
	close(fd5);
	close(fd6);
	printf("\n_______________end of a line at a time________________\n");

	printf("\n____________________file at a time____________________\n");

	fd3 = open(FILE_3, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd3);
	line3 = get_next_line(fd3);
	i = 1;
	while(line3)
	{
		printf("%s", line3);
		free(line3);
		line3 = get_next_line(fd3);
		++i;
	}
	close(fd3);
	fd4 = open(FILE_4, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd4);
	line4 = get_next_line(fd4);
	i = 1;
	while(line4)
	{
		printf("%s", line4);
		free(line4);
		line4 = get_next_line(fd4);
		++i;
	}
	close(fd4);
	fd5 = open(FILE_5, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd5);
	line5 = get_next_line(fd5);
	i = 1;
	while(line5)
	{
		printf("%s", line5);
		free(line5);
		line5 = get_next_line(fd5);
		++i;
	}
	close(fd5);
	fd6 = open(FILE_6, O_RDONLY);
	printf("\n#_______________ fd%d _______________#\n", fd6);
	line6 = get_next_line(fd6);
	i = 1;
	while(line6)
	{
		printf("%s", line6);
		free(line6);
		line6 = get_next_line(fd6);
		++i;
	}
	close(fd6);
	printf("\n_______________end of a file at a time________________\n");
	
	return (0);
}
