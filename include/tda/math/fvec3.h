#ifndef TDA_MATH_FVEC3_H
#define TDA_MATH_FVEC3_H

#define fvec3_set(v, a, b, c) \
	do { \
		(v)->x = a; \
		(v)->y = b; \
		(v)->z = c; \
	} while (0);

#define fvec3_cpy(dest, src) \
	do { \
		(dest)->x = (src)->x; \
		(dest)->y = (src)->y; \
		(dest)->z = (src)->z; \
	} while (0);

#define fvec3_zero(v) fvec3_set(v, 0, 0, 0)

struct fvec3
{
	float x;
	float y;
	float z;
};

float fvec3_dist(const struct fvec3 *a, const struct fvec3 *b);

float fvec3_len(const struct fvec3 *v);

void fvec3_nrm(struct fvec3 *dest, const struct fvec3 *src);

float fvec3_dot(const struct fvec3 *lv, const struct fvec3 *rv);

void fvec3_crs(
	struct fvec3 *dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	);

void fvec3_add(
	struct fvec3* dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	);

void fvec3_sub(
	struct fvec3* dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	);

void fvec3_mul(struct fvec3 *v, float val);

void fvec3_div(struct fvec3 *v, float val);

#endif /* TDA_MATH_FVEC3_H */
