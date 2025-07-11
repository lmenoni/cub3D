/*
** mlx_int_str_to_wordtab.c for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Wed Sep 13 11:36:09 2000 Charlie Root
** Last update Fri Dec 14 11:02:09 2001 Charlie Root
*/


#include	"mlx_int.h"


int	mlx_int_str_str(char *str,char *find,int len)
{
  int	len_f;
  int	p_pos;
  char	*s;
  char	*f;

  len_f = strlen(find);
  if (len_f>len)
    return (-1);
  p_pos = 0;
  while (*(str+len_f-1))
    {
      s = str;
      f = find;
      while (*(f++) == *(s++))
        if (!*f)
          return (p_pos);
      str ++;
      p_pos ++;
    }
  return (-1);
}



int	mlx_int_str_str_cote(char *str,char *find,int len)
{
  int	len_f;
  int	p_pos;
  char	*s;
  char	*f;
  int	cote;

  len_f = strlen(find);
  if (len_f>len)
    return (-1);
  cote = 0;
  p_pos = 0;
  while (*(str+len_f-1))
    {
      if (*str=='"')
	cote = 1-cote;
      if (!cote)
	{
	  s = str;
	  f = find;
	  while (*(f++) == *(s++))
	    if (!*f)
	      return (p_pos);
	}
      str ++;
      p_pos ++;
    }
  return (-1);
}


char	**mlx_int_str_to_wordtab(char *str)
{
  char	**tab;
  int	p_pos;
  int	nb_word;
  int	len;

  len = strlen(str);
  nb_word = 0;
  p_pos = 0;
  while (p_pos<len)
  {
    while (*(str+p_pos)==' ' || *(str+p_pos)=='\t')
      p_pos ++;
    if (*(str+p_pos))
      nb_word ++;
    while (*(str+p_pos) && *(str+p_pos)!=' ' && *(str+p_pos)!='\t')
      p_pos ++;
  }
  if (!(tab = malloc((1+nb_word)*sizeof(*tab))))
    return ((char **)0);
  nb_word = 0;
  p_pos = 0;
  while (p_pos<len)
    {
      while (*(str+p_pos)==' ' || *(str+p_pos)=='\t')
	{
	  *(str+p_pos) = 0;
	  p_pos ++;
	}
      if (*(str+p_pos))
	{
	  tab[nb_word] = str+p_pos;
	  nb_word ++;
	}
      while (*(str+p_pos) && *(str+p_pos)!=' ' && *(str+p_pos)!='\t')
	p_pos ++;
    }
  tab[nb_word] = 0;
  return (tab);
}
