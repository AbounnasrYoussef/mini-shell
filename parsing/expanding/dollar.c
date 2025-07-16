#include <../minishell.h>


char	*get_env_value(char *name, t_list_env *env, garbage **garb)
{
	while (env)
	{
		if (env->variable && ft_strcmp(env->variable, name) == 0)
			return (ft_strdup(env->valeur_vari, garb));
		env = env->next;
	}
	return (ft_strdup("", garb));
}

char	*expand_dollar(char *value, int *i, int exit_code,t_list_env *env, garbage **garb)
{
	char	*var_name;

	if (value[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(exit_code, garb));
	}
	(*i)++;
	int start = *i;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(value, start, *i - start, garb);
	return (get_env_value(var_name, env, garb));
}