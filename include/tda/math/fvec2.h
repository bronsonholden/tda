#ifndef TDA_MATH_FVEC2_H
#define TDA_MATH_FVEC2_H

#define fvec2_set(v, a, b) \
	do { \
		(v)->x = a; \
		(v)->y = b; \
	} while (0);

#define fvec2_zero(v) fvec2_set(v, 0, 0)

struct fvec2
{
	float x;
	float y;
};

void fvec2_cpy(struct fvec2 *dest, const struct fvec2 *src);

float fvec2_len(const struct fvec2 *v);

float fvec2_crs(const struct fvec2 *lv, const struct fvec2 *rv);

float fvec2_dot(const struct fvec2 *lv, const struct fvec2 *rv);

void fvec2_nrm(struct fvec2 *v);

void fvec2_add(
	struct fvec2 *dv,
	const struct fvec2 *lv,
	const struct fvec2 *rv
	);

void fvec2_sub(
	struct fvec2 *dv,
	const struct fvec2 *lv,
	const struct fvec2 *rv
	);

void fvec2_mul(struct fvec2 *v, float val);

void fvec2_div(struct fvec2 *v, float val);

#endif /* TDA_MATH_FVEC2_H */
