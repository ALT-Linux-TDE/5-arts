/* GSL - Generic Sound Layer
 * Copyright (C) 2001 Tim Janik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#include "gslconvert.h"
#include <string.h>



/* --- functions --- */
gchar*
gsl_convert_from_utf8 (const gchar *codeset,
		       const gchar *string)
{
  gchar *result;

  g_return_val_if_fail (codeset != NULL, NULL);
  if (!string)
    return NULL;

  result = g_convert (string, strlen (string), codeset, GSL_CODESET_UTF8, NULL, NULL, NULL);
  if (!result)
    result = g_strconcat ("??unknown-codeset:", codeset, "??", NULL);

  return result;
}

gchar*
gsl_convert_to_utf8 (const gchar *codeset,
		     const gchar *string)
{
  gchar *result;

  g_return_val_if_fail (codeset != NULL, NULL);
  if (!string)
    return NULL;

  result = g_convert (string, strlen (string), GSL_CODESET_UTF8, codeset, NULL, NULL, NULL);
  if (!result)
    result = g_strconcat ("??unknown-codeset:", codeset, "??", NULL);

  return result;
}