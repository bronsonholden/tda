#include <math.h>
#include <tda/math/fvec3.h>

void fvec3_cpy(
	struct fvec3 *dest,
	const struct fvec3 *src
	)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

float fvec3_dist(const struct fvec3 *a, const struct fvec3 *b)
{
	float tmp, dist = 0;

	tmp = a->x - b->x;
	dist += tmp * tmp;

	tmp = a->y - b->y;
	dist += tmp * tmp;

	tmp = a->z - b->z;
	dist += tmp * tmp;

	return sqrtf(dist);
}

float fvec3_len(const struct fvec3 *v)
{
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

void fvec3_crs(
	struct fvec3 *dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	)
{
	struct fvec3 tmp;

	tmp.x = (lv->y * rv->z) - (rv->y * lv->z);
	tmp.y = (lv->z * rv->x) - (lv->x * rv->z);
	tmp.z = (lv->x * rv->y) - (lv->y * rv->x);

	fvec3_cpy(dv, &tmp);
}

float fvec3_dot(const struct fvec3 *lv, const struct fvec3 *rv)
{
	return lv->x * rv->x + lv->y * rv->y + lv->z * rv->z;
}

void fvec3_nrm(struct fvec3 *v)
{
	float len = fvec3_len(v);

	if (len < 0.00001f && len > -0.00001f)
		return;
	else
		len = 1.0f / len;

	v->x *= len;
	v->y *= len;
	v->z *= len;
}

void fvec3_add(
	struct fvec3 *dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	)
{
	dv->x = lv->x + rv->x;
	dv->y = lv->y + rv->y;
	dv->z = lv->z + rv->z;
}

void fvec3_sub(
	struct fvec3 *dv,
	const struct fvec3 *lv,
	const struct fvec3 *rv
	)
{
	dv->x = lv->x - rv->x;
	dv->y = lv->y - rv->y;
	dv->z = lv->z - rv->z;
}

void fvec3_mul(struct fvec3 *v, float val)
{
	v->x *= val;
	v->y *= val;
	v->z *= val;
}

void fvec3_div(struct fvec3 *v, float val)
{
	if (val == 0)
		return;
	else
		val = 1.0f / val;

	v->x *= val;
	v->y *= val;
	v->z *= val;
}
