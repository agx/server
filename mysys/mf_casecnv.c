/* Copyright (C) 2000 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
  Functions to convert to lover_case and to upper_case.
*/

#include "mysys_priv.h"
#include <m_ctype.h>
#ifndef SCO
#include <m_string.h>
#endif



int my_sortcmp(CHARSET_INFO *cs, const char *s, const char *t, uint len)
{
#ifdef USE_STRCOLL
  if (use_strnxfrm(cs))
    return my_strnncoll(cs,(uchar *)s, len, (uchar *)t, len);
  else
#endif
  {
    register uchar *map=cs->sort_order;
    while (len--)
    {
      if (map[(uchar) *s++] != map[(uchar) *t++])
        return ((int) map[(uchar) s[-1]] - (int) map[(uchar) t[-1]]);
    }
    return 0;
  }
}

int my_sortncmp(CHARSET_INFO *cs,
                const char *s, uint s_len, 
                const char *t, uint t_len)
{
#ifdef USE_STRCOLL
  if (use_strnxfrm(cs))
    return my_strnncoll(cs, (uchar *)s, s_len, (uchar *)t, t_len);
  else
#endif
  {
    uint len= min(s_len,t_len);
    register uchar *map=cs->sort_order;
    
    while (len--)
    {
      if (map[(uchar) *s++] != map[(uchar) *t++])
        return ((int) map[(uchar) s[-1]] - (int) map[(uchar) t[-1]]);
    }
    return (int) (s_len - t_len);
  }
}
