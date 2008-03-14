/* Yash: yet another shell */
/* strbuf.h: modifiable string buffer */
/* © 2007-2008 magicant */

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


#ifndef STRBUF_H
#define STRBUF_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>


typedef struct xstrbuf_T {
	char *contents;
	size_t length, maxlength;
} xstrbuf_T;
typedef struct xwcsbuf_T {
	wchar_t *contents;
	size_t length, maxlength;
} xwcsbuf_T;

extern xstrbuf_T *sb_init(xstrbuf_T *buf)
	__attribute__((nonnull));
extern xstrbuf_T *sb_initwith(xstrbuf_T *restrict buf, char *restrict s)
	__attribute__((nonnull));
extern void sb_destroy(xstrbuf_T *buf)
	__attribute__((nonnull));
extern char *sb_tostr(xstrbuf_T *buf)
	__attribute__((nonnull));
extern xstrbuf_T *sb_setmax(xstrbuf_T *buf, size_t newmax)
	__attribute__((nonnull));
extern inline xstrbuf_T *sb_ensuremax(xstrbuf_T *buf, size_t max)
	__attribute__((nonnull));
extern xstrbuf_T *sb_clear(xstrbuf_T *buf)
	__attribute__((nonnull));
extern xstrbuf_T *sb_replace(
		xstrbuf_T *restrict buf, size_t i, size_t bn,
		const char *restrict s, size_t sn)
	__attribute__((nonnull));
static inline xstrbuf_T *sb_ninsert(
		xstrbuf_T *restrict buf, size_t i, const char *restrict s, size_t n)
	__attribute__((nonnull));
static inline xstrbuf_T *sb_insert(
		xstrbuf_T *restrict buf, size_t i, const char *restrict s)
	__attribute__((nonnull));
static inline xstrbuf_T *sb_ncat(
		xstrbuf_T *restrict buf, const char *restrict s, size_t n)
	__attribute__((nonnull));
static inline xstrbuf_T *sb_cat(
		xstrbuf_T *restrict buf, const char *restrict s)
	__attribute__((nonnull));
static inline xstrbuf_T *sb_remove(xstrbuf_T *buf, size_t i, size_t n)
	__attribute__((nonnull));
extern xstrbuf_T *sb_ccat(xstrbuf_T *buf, char c)
	__attribute__((nonnull));
extern wchar_t *sb_wcscat(
		xstrbuf_T *restrict buf,
		const wchar_t *restrict s, mbstate_t *restrict ps)
	__attribute__((nonnull(1)));
extern int sb_vprintf(
		xstrbuf_T *restrict buf, const char *restrict format, va_list ap)
	__attribute__((nonnull(1,2),format(printf,2,0)));
extern int sb_printf(
		xstrbuf_T *restrict buf, const char *restrict format, ...)
	__attribute__((nonnull(1,2),format(printf,2,3)));
extern size_t sb_strftime(
		xstrbuf_T *restrict buf,
		const char *restrict format, const struct tm *restrict tm)
	__attribute__((nonnull,format(strftime,2,0)));

extern xwcsbuf_T *wb_init(xwcsbuf_T *buf)
	__attribute__((nonnull));
extern xwcsbuf_T *wb_initwith(xwcsbuf_T *restrict buf, wchar_t *restrict s)
	__attribute__((nonnull));
extern void wb_destroy(xwcsbuf_T *buf)
	__attribute__((nonnull));
extern wchar_t *wb_towcs(xwcsbuf_T *buf)
	__attribute__((nonnull));
extern xwcsbuf_T *wb_setmax(xwcsbuf_T *buf, size_t newmax)
	__attribute__((nonnull));
extern xwcsbuf_T *wb_clear(xwcsbuf_T *buf)
	__attribute__((nonnull));
extern xwcsbuf_T *wb_replace(
		xwcsbuf_T *restrict buf, size_t i, size_t bn,
		const wchar_t *restrict s, size_t sn)
	__attribute__((nonnull));
static inline xwcsbuf_T *wb_ninsert(
		xwcsbuf_T *restrict buf, size_t i, const wchar_t *restrict s, size_t n)
	__attribute__((nonnull));
static inline xwcsbuf_T *wb_insert(
		xwcsbuf_T *restrict buf, size_t i, const wchar_t *restrict s)
	__attribute__((nonnull));
static inline xwcsbuf_T *wb_ncat(
		xwcsbuf_T *restrict buf, const wchar_t *restrict s, size_t n)
	__attribute__((nonnull));
static inline xwcsbuf_T *wb_cat(
		xwcsbuf_T *restrict buf, const wchar_t *restrict s)
	__attribute__((nonnull));
static inline xwcsbuf_T *wb_remove(xwcsbuf_T *buf, size_t i, size_t n)
	__attribute__((nonnull));
extern xwcsbuf_T *wb_wccat(xwcsbuf_T *buf, wchar_t c)
	__attribute__((nonnull));
extern char *wb_mbscat(xwcsbuf_T *restrict buf, const char *restrict s)
	__attribute__((nonnull));
extern int wb_vprintf(
		xwcsbuf_T *restrict buf, const wchar_t *restrict format, va_list ap)
	__attribute__((nonnull(1,2)));
extern int wb_printf(
		xwcsbuf_T *restrict buf, const wchar_t *restrict format, ...)
	__attribute__((nonnull(1,2)));


/* マルチバイト文字列 s の最初の n バイトを
 * バッファの i バイト目の手前に挿入する。
 * strlen(s) < n ならば s 全体を挿入する。
 * buf->length <= i ならば文字列の末尾に追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xstrbuf_T *sb_ninsert(
		xstrbuf_T *restrict buf, size_t i, const char *restrict s, size_t n)
{
	return sb_replace(buf, i, 0, s, n);
}

/* マルチバイト文字列 s をバッファの i バイト目の手前に挿入する。
 * buf->length <= i ならば文字列の末尾に追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xstrbuf_T *sb_insert(
		xstrbuf_T *restrict buf, size_t i, const char *restrict s)
{
	return sb_replace(buf, i, 0, s, SIZE_MAX);
}

/* マルチバイト文字列 s の最初の n バイトを文字列バッファに追加する。
 * strlen(s) < n ならば s 全体を追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xstrbuf_T *sb_ncat(
		xstrbuf_T *restrict buf, const char *restrict s, size_t n)
{
	return sb_replace(buf, SIZE_MAX, 0, s, n);
}

/* マルチバイト文字列 s を文字列バッファに追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xstrbuf_T *sb_cat(
		xstrbuf_T *restrict buf, const char *restrict s)
{
	return sb_replace(buf, SIZE_MAX, 0, s, SIZE_MAX);
}

/* マルチバイト文字列バッファの i バイト目から n バイトを削除する。
 * buf->length <= i ならば何もしない。
 * buf->length <= i + n ならば i バイト目以降全てを削除する。 */
static inline xstrbuf_T *sb_remove(xstrbuf_T *buf, size_t i, size_t n)
{
	return sb_replace(buf, i, n, "", 0);
}


/* ワイド文字列 s の最初の n 文字をバッファの i 文字目の手前に挿入する。
 * wcslen(s) < n ならば s 全体を挿入する。
 * buf->length <= i ならば文字列の末尾に追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xwcsbuf_T *wb_ninsert(
		xwcsbuf_T *restrict buf, size_t i, const wchar_t *restrict s, size_t n)
{
	return wb_replace(buf, i, 0, s, n);
}

/* ワイド文字列 s をバッファの i 文字目の手前に挿入する。
 * buf->length <= i ならば文字列の末尾に追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xwcsbuf_T *wb_insert(
		xwcsbuf_T *restrict buf, size_t i, const wchar_t *restrict s)
{
	return wb_replace(buf, i, 0, s, SIZE_MAX);
}

/* ワイド文字列 s の最初の n 文字を文字列バッファに追加する。
 * wcslen(s) < n ならば s 全体を追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xwcsbuf_T *wb_ncat(
		xwcsbuf_T *restrict buf, const wchar_t *restrict s, size_t n)
{
	return wb_replace(buf, SIZE_MAX, 0, s, n);
}

/* ワイド文字列 s を文字列バッファに追加する。
 * s は buf->contents の一部であってはならない。 */
static inline xwcsbuf_T *wb_cat(
		xwcsbuf_T *restrict buf, const wchar_t *restrict s)
{
	return wb_replace(buf, SIZE_MAX, 0, s, SIZE_MAX);
}

/* ワイド文字列バッファの i 文字目から n 文字を削除する。
 * buf->length <= i ならば何もしない。
 * buf->length <= i + n ならば i 文字目以降全てを削除する。 */
static inline xwcsbuf_T *wb_remove(xwcsbuf_T *buf, size_t i, size_t n)
{
	return wb_replace(buf, i, n, L"", 0);
}


#endif /* STRBUF_H */
