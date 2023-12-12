#ifndef LEAKDETECT_H
# define LEAKDETECT_H
# include <stdlib.h>
// # include "minishell.h"

// #define malloc(s) leak_detelc_malloc(s, __FILE__, __LINE__)
#define ft_calloc(i, num) leak_detelc_ft_calloc(i, num, __FILE__, __LINE__)
#define ft_strdup(str) leak_detelc_strdup(str, __FILE__, __LINE__)

void	*leak_detelc_malloc(size_t size,  const char *file, unsigned int line);
void	*leak_detelc_ft_calloc(size_t i, size_t num, const char *file, unsigned int line);
char	*leak_detelc_strdup(const char *str, const char *file, unsigned int line);

#endif
