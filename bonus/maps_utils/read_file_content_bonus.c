/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:34:14 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/25 21:45:43 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

char	*get_file_contents(const char *filepath)
{
	int		fd;
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	fd = open(filepath, O_RDONLY);
	if (fd < 0 || !content)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		free(line);
		if (!content)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}
