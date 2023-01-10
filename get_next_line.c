/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphilip <mphilip@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:40:13 by mphilip           #+#    #+#             */
/*   Updated: 2023/01/10 16:44:26 by mphilip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*null_str(int size)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	while (i < size + 1)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
		char	*ptr;
		size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&ptr[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;
	size_t	i;

	dest_ptr = (char  *)dest;
	src_ptr = (char *)src;
	i = 0;
	if (dest_ptr == NULL && src_ptr == NULL)
		return (dest);
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (src_ptr == dest_ptr || n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			dest_ptr[n - 1] = src_ptr[n - 1];
			n--;
		}
			return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}

char	*ft_realloc_add(char *stash, char *line, int size_to_add)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	result = null_str(len + size_to_add);
	if (!result)
		return (NULL);
	while (line[i])
	{
		result[i] = line[i];
		i++;
	}
	i = 0;
	while (i < size_to_add)
	{
		result[len + i] = stash[i];
		i++;
	}
	free(line);
	return (result);
}

void	stash_clean(char *stash)
{
	char	*ptr;
	int		final_len;
	int		i;

	i = 0;
	ptr = ft_strchr(stash, '\n');
	final_len = ft_strlen(ptr) - 1;
	ft_memmove(stash, ptr + 1, final_len);
	while (i < BUFFER_SIZE - final_len)
	{
		stash[final_len + i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char		stash[BUFFER_SIZE+1];
	char			*line;
	char			*buf;
	static size_t	bytes_count=1;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	buf = malloc(BUFFER_SIZE+1);
	if (!buf)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE+1);
	while (bytes_count != 0)
	{
		if (stash[0] == 0)
		{
			bytes_count = read(fd, buf, BUFFER_SIZE);
			ft_memmove(stash, buf, bytes_count);
		}
		if (ft_strchr(stash, '\n'))
		{
			line = ft_realloc_add(stash, line, ft_strlen(stash)-ft_strlen(ft_strchr(stash, '\n'))+1);
			stash_clean(stash);
			free(buf);
			if (line[0] == '\0')
				return (free(line), NULL);
			return (line);
		}
		else
		{
			line = ft_realloc_add(stash, line, ft_strlen(stash));
			ft_bzero(stash, BUFFER_SIZE);
		}
	}
	free(buf);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
