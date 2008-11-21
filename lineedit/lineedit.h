/* Yash: yet another shell */
/* lineedit.h: command line editing */
/* (C) 2007-2008 magicant */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


#ifndef YASH_LINEEDIT_H
#define YASH_LINEEDIT_H

#include <stddef.h>
#include "../strbuf.h"


extern _Bool yle_need_term_reset;

extern int yle_line, yle_column;
extern _Bool yle_counting;

extern xwcsbuf_T yle_main_buffer;
extern size_t yle_main_buffer_index;

extern _Bool yle_init(void);

extern wchar_t *yle_readline(const wchar_t *prompt)
    __attribute__((nonnull,malloc,warn_unused_result));

extern void yle_print_wc(wchar_t c);
extern void yle_print_ws(const wchar_t *s, size_t n)
    __attribute__((nonnull));

extern void yle_print_prompt(const wchar_t *prompt)
    __attribute__((nonnull));


#endif /* YASH_LINEEDIT_H */


/* vim: set ts=8 sts=4 sw=4 noet: */
