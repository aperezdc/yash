/* Yash: yet another shell */
/* plist.h: modifiable list of pointers */
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


#ifndef PLIST_H
#define PLIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct plist_t {
	void **contents;
	size_t length, maxlength;
} plist_t;

extern size_t plcount(void *const *list)
	__attribute__((nonnull));
extern void recfree(void **ary, void freer(void *elem));

extern plist_t *pl_init(plist_t *list)
	__attribute__((nonnull));
extern void pl_destroy(plist_t *list)
	__attribute__((nonnull));
extern void **pl_toary(plist_t *list)
	__attribute__((nonnull));
extern plist_t *pl_setmax(plist_t *list, size_t newmax)
	__attribute__((nonnull));
extern plist_t *pl_ensuremax(plist_t *list, size_t max)
	__attribute__((nonnull));
extern plist_t *pl_clear(plist_t *list)
	__attribute__((nonnull));
extern plist_t *pl_replace(
		plist_t *restrict list, size_t i, size_t ln,
		void *const *restrict a, size_t an)
	__attribute__((nonnull));
static inline plist_t *pl_ninsert(
		plist_t *restrict list, size_t i, void *const *restrict a, size_t n)
	__attribute__((nonnull));
static inline plist_t *pl_insert(
		plist_t *restrict list, size_t i, void *const *restrict a)
	__attribute__((nonnull));
static inline plist_t *pl_ncat(
		plist_t *restrict list, void *const *restrict a, size_t n)
	__attribute__((nonnull));
static inline plist_t *pl_cat(
		plist_t *restrict list, void *const *restrict a)
	__attribute__((nonnull));
static inline plist_t *pl_remove(plist_t *list, size_t i, size_t n)
	__attribute__((nonnull));
extern plist_t *pl_add(plist_t *list, void *p)
	__attribute__((nonnull(1)));


/* ポインタの配列 a の最初の n 要素をポインタリストの i 要素目の手前に挿入する。
 * a の要素に NULL があってもそれは特別扱いしない。
 * list->length <= i ならばリストの末尾に追加する。
 * a は list->contents の一部であってはならない。 */
static inline plist_t *pl_ninsert(
		plist_t *restrict list, size_t i, void *const *restrict a, size_t n)
{
	return pl_replace(list, i, 0, a, n);
}

/* ポインタの配列 a の要素をポインタリストの i 要素目の手前に挿入する。
 * 挿入するのは、a 内の NULL の手前までの要素である。
 * list->length <= i ならばリストの末尾に追加する。
 * a は list->contents の一部であってはならない。 */
static inline plist_t *pl_insert(
		plist_t *restrict list, size_t i, void *const *restrict a)
{
	return pl_replace(list, i, 0, a, plcount(a));
}

/* ポインタの配列 a の最初の n 要素をポインタリストの末尾に追加する。
 * a の要素に NULL があってもそれは特別扱いしない。
 * a は list->contents の一部であってはならない。 */
static inline plist_t *pl_ncat(
		plist_t *restrict list, void *const *restrict a, size_t n)
{
	return pl_replace(list, SIZE_MAX, 0, a, n);
}

/* ポインタの配列 a の要素をポインタリストの末尾に追加する。
 * 挿入するのは、a 内の NULL の手前までの要素である。
 * a は list->contents の一部であってはならない。 */
static inline plist_t *pl_cat(
		plist_t *restrict list, void *const *restrict a)
{
	return pl_replace(list, SIZE_MAX, 0, a, plcount(a));
}

/* リストの i 要素目から n 個の要素を削除する。
 * 消される要素は勝手には解放されないので注意。 */
static inline plist_t *pl_remove(plist_t *list, size_t i, size_t n)
{
	return pl_replace(list, i, n, (void *[]) { NULL, }, 0);
}


#endif /* PLIST_H */
