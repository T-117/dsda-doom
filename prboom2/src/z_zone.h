/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *      Zone Memory Allocation, perhaps NeXT ObjectiveC inspired.
 *      Remark: this was the only stuff that, according
 *       to John Carmack, might have been useful for
 *       Quake.
 *
 * Rewritten by Lee Killough, though, since it was not efficient enough.
 *
 *---------------------------------------------------------------------*/

#ifndef __Z_ZONE__
#define __Z_ZONE__

#ifndef __GNUC__
#define __attribute__(x)
#endif

// Include system definitions so that prototypes become
// active before macro replacements below are in effect.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ZONE MEMORY
// PU - purge tags.

enum {
  PU_STATIC,
  PU_LEVEL,
  /* Must always be last -- killough */
  PU_MAX
};

void Z_Free(void *ptr);
void *Z_Malloc(size_t size);
void *Z_Calloc(size_t n, size_t n2);
void *Z_Realloc(void *p, size_t n);
char *Z_Strdup(const char *s);

void Z_FreeTag(int tag);
void *Z_MallocTag(size_t size, int tag);
void *Z_CallocTag(size_t n, size_t n2, int tag);
void *Z_ReallocTag(void *p, size_t n, int tag);
char *Z_StrdupTag(const char *s, int tag);

/* cphipps 2001/11/18 -
 * If we're using memory mapped file access to WADs, we won't need to maintain
 * our own heap. So we *could* let "normal" malloc users use the libc malloc
 * directly, for efficiency. Except we do need a wrapper to handle out of memory
 * errors... damn, ok, we'll leave it for now.
 */

// Remove all definitions before including system definitions

#undef free
#undef malloc
#undef realloc
#undef calloc
#undef strdup

#define free(p)            Z_Free(p)
#define malloc(n)          Z_Malloc(n)
#define realloc(p,n)       Z_Realloc(p,n)
#define calloc(n1,n2)      Z_Calloc(n1,n2)
#define strdup(s)          Z_Strdup(s)

#endif
