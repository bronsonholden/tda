#ifndef TDA_MATH_FMAT4_H
#define TDA_MATH_FMAT4_H

#include <tda/math/fvec3.h>

struct fmat4
{
	float a[4];
	float b[4];
	float c[4];
	float d[4];
};

#define fmat4_id(ptr) \
	do { \
		(ptr)->a[0] = 1.0f; \
		(ptr)->a[1] = 0.0f; \
		(ptr)->a[2] = 0.0f; \
		(ptr)->a[3] = 0.0f; \
		(ptr)->b[0] = 0.0f; \
		(ptr)->b[1] = 1.0f; \
		(ptr)->b[2] = 0.0f; \
		(ptr)->b[3] = 0.0f; \
		(ptr)->c[0] = 0.0f; \
		(ptr)->c[1] = 0.0f; \
		(ptr)->c[2] = 1.0f; \
		(ptr)->c[3] = 0.0f; \
		(ptr)->d[0] = 0.0f; \
		(ptr)->d[1] = 0.0f; \
		(ptr)->d[2] = 0.0f; \
		(ptr)->d[3] = 1.0f; \
	} while (0);

void fmat4_ortho(
	struct fmat4 *m,
	const struct fvec3 *bl,
	const struct fvec3 *tr
	);

void fmat4_persp(
	struct fmat4 *m,
	float fov,
	float ratio,
	float near,
	float far
	);

void mat4_lookat(
	struct fmat4 *m,
	const struct fvec3 *pos,
	const struct fvec3 *tar,
	const struct fvec3 *up
	);

void fmat4_mul(
	struct fmat4 *m,
	const struct fmat4 *lv,
	const struct fmat4 *rv
	);

#endif /* TDA_MATH_FMAT4_H */
