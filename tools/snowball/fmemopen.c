/**
 * THIS FILE IS FOR OSX and WINDOWS (NO CYGWIN) ONLY!
 * Other unix systems support it regardless
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__

//
// Copyright 2011-2014 NimbusKit
// Originally ported from https://github.com/ingenuitas/python-tesseract/blob/master/fmemopen.c
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <sys/mman.h>

struct fmem {
  size_t pos;
  size_t size;
  char *buffer;
};
typedef struct fmem fmem_t;

static int readfn(void *handler, char *buf, int size) {
  fmem_t *mem = handler;
  size_t available = mem->size - mem->pos;
  
  if (size > available) {
    size = available;
  }
  memcpy(buf, mem->buffer + mem->pos, sizeof(char) * size);
  mem->pos += size;
  
  return size;
}

static int writefn(void *handler, const char *buf, int size) {
  fmem_t *mem = handler;
  size_t available = mem->size - mem->pos;

  if (size > available) {
    size = available;
  }
  memcpy(mem->buffer + mem->pos, buf, sizeof(char) * size);
  mem->pos += size;

  return size;
}

static fpos_t seekfn(void *handler, fpos_t offset, int whence) {
  size_t pos;
  fmem_t *mem = handler;

  switch (whence) {
    case SEEK_SET: {
      if (offset >= 0) {
        pos = (size_t)offset;
      } else {
        pos = 0;
      }
      break;
    }
    case SEEK_CUR: {
      if (offset >= 0 || (size_t)(-offset) <= mem->pos) {
        pos = mem->pos + (size_t)offset;
      } else {
        pos = 0;
      }
      break;
    }
    case SEEK_END: pos = mem->size + (size_t)offset; break;
    default: return -1;
  }

  if (pos > mem->size) {
    return -1;
  }

  mem->pos = pos;
  return (fpos_t)pos;
}

static int closefn(void *handler) {
  free(handler);
  return 0;
}

FILE *fmemopen(void *buf, size_t size, const char *mode) {
  // This data is released on fclose.
  fmem_t* mem = (fmem_t *) malloc(sizeof(fmem_t));

  // Zero-out the structure.
  memset(mem, 0, sizeof(fmem_t));

  mem->size = size;
  mem->buffer = buf;

  // funopen's man page: https://developer.apple.com/library/mac/#documentation/Darwin/Reference/ManPages/man3/funopen.3.html
  return funopen(mem, readfn, writefn, seekfn, closefn);
}

#elif _WIN32


/* Copyright (C) 2007-2010 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author Pablo Rincon Crespo <pablo.rincon.crespo@gmail.com>
 *         Based on FMem.c of Alexandre Flori (2008/10/17 AF)
 */

#include "fmemopen.h"
#include <windows.h>
/**
 * \brief portable version of fmemopen for Windows works on top of real temp files
 * \param buffer that holds the file content
 * \param size of the file buffer
 * \param mode mode of the file to open
 * \retval pointer to the file; NULL if something is wrong
 */
FILE *fmemopen(void *buf, size_t size, const char *mode) {
    char temppath[MAX_PATH - 13];
    if (0 == GetTempPath(sizeof(temppath), temppath))
        return NULL;

    char filename[MAX_PATH + 1];
    if (0 == GetTempFileName(temppath, "SC", 0, filename))
        return NULL;

    FILE *f = fopen(filename, "wb");
    if (NULL == f)
        return NULL;

    fwrite(buf, size, 1, f);
    fclose(f);

    return fopen(filename, mode);
}

#endif
