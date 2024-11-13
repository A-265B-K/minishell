
#include "../../include/minishell.h"

/**
 * @brief Allocate memory with malloc and set it to zero.
 * @exception EXIT with ERR_MALLOC on failure.
 * @param count 
 * @param size 
 * @return void* 
 */
void	*mem_add(size_t count, size_t size)
{
	char	*ptr;
	int		n;

	n = size * count;
	ptr = malloc(n + 1);
	if (!ptr)
		exit(error(ERR_MALLOC));
	while (n >= 0)
		ptr[n--] = '\0';
	return ((void *) ptr);
}

/**
 * @brief Join two strings and optionaly free them.
 * 
 * @param s1 String 1.
 * @param s2 String 2.
 * @param free_s1 boolian to free string 1.
 * @param free_s2 boolian to free string 2.
 * @return char*
 */
char	*free_join(char *s1, char *s2, bool free_s1, bool free_s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (free_s2 == true)
		free(s2);
	if (free_s1 == true)
		free(s1);
	return (tmp);
}

/**
 * @brief Reallocate memory with malloc and set it to zero.
 * 
 * @param ptr 
 * @param size 
 * @return void* 
 */
void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
