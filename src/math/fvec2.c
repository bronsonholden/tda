#include <math.h>
#include <tda/math/fvec2.h>

#define abs(a) ((a) < 0 ? -(a) : (a))
#define feq(a, b) (abs((a) - (b)) < 0.000001f)

void fvec2_cpy(
	struct fvec2 *dest,
	const struct fvec2 *src
	)
{
	dest->x = src->x;
	dest->y = src->y;
}

float fvec2_len(const struct fvec2 *v)
{
	return sqrtf(v->x * v->x + v->y * v->y);
}

float fvec2_crs(
	const struct fvec2 *lv,
	const struct fvec2 *rv
	)
{
	return lv->x * rv->y - lv->y * rv->x;
}

float fvec2_dot(
	const struct fvec2 *lv,
	const struct fvec2 *rv
	)
{
	return lv->x * rv->x + lv->y * rv->y;
}

void fvec2_nrm(struct fvec2 *v)
{
	float len = fvec2_len(v);

	if (feq(len, 0.0f))
		return;
	else
		len = 1.0f / len;

	v->x *= len;
	v->y *= len;
}

void fvec2_add(
	struct fvec2 *dv,
	const struct fvec2 *lv,
	const struct fvec2 *rv
	)
{
	dv->x = lv->x + rv->x;
	dv->y = lv->y + rv->y;
}

void fvec2_sub(
	struct fvec2 *dv,
	const struct fvec2 *lv,
	const struct fvec2 *rv
	)
{
	dv->x = lv->x - rv->x;
	dv->y = lv->x - rv->y;
}


void fvec2_mul(struct fvec2 *v, float val)
{
	v->x *= val;
	v->y *= val;
}

void fvec2_div(struct fvec2 *v, float val)
{
	if (feq(val, 0.0f))
		return;
	else
		val = 1.0f / val;

	v->x *= val;
	v->y *= val;
}
