#ifndef TDA_MATH_FQUAT_H
#define TDA_MATH_FQUAT_H

#include <tda/math/fvec3.h>
#include <tda/math/fmat4.h>

struct fquat
{
	/* real component */
	float a;
	/* imaginary components */
	float b;
	float c;
	float d;
};

#define fquat_id(q) \
	do { \
		(q)->a = 1.0f; \
		(q)->b = 0.0f; \
		(q)->c = 0.0f; \
		(q)->d = 0.0f; \
	} while (0);

void fquat_to_mat4(const struct fquat *q, struct fmat4 *m);

float fquat_get_angle(const struct fquat *q);

void fquat_get_axis(const struct fquat *q, struct fvec3 *axis);

void fquat_set_axis_angle(
	struct fquat *q,
	const struct fvec3 *axis,
	float angle
	);

void fquat_mul(
	struct fquat *q,
	const struct fquat *lv,
	const struct fquat *rv
	);

void fquat_inv(struct fquat *dest, const struct fquat *src);

void fquat_nrm(struct fquat *q, const struct fquat *src);

float fquat_len(const struct fquat *q);

float fquat_len2(const struct fquat *q);

#endif /* TDA_MATH_FQUAT_H */
