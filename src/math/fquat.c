#include <string.h>
#include <math.h>
#include <tda/math/fquat.h>

#define sq(a) ((a) * (a))
#define abs(a) ((a) < 0 ? -(a) : (a))
#define feq(a, b) (abs((a) - (b)) < 0.00001f)

void fquat_to_mat4(const struct fquat *q, struct fmat4 *mat)
{
	mat->a[0] = 1.0f - (2 * sq(q->c)) - (2 * sq(q->d));
	mat->a[1] = (2 * q->b * q->c) + (2 * q->d * q->a);
	mat->a[2] = (2 * q->b * q->d) - (2 * q->c * q->a);
	mat->a[3] = 0.0f;

	mat->b[0] = (2 * q->b * q->c) - (2 * q->d * q->a);
	mat->b[1] = 1.0f - (2 * sq(q->b)) - (2 * sq(q->d));
	mat->b[2] = (2 * q->c * q->d) + (2 * q->a * q->b);
	mat->b[3] = 0.0f;

	mat->c[0] = (2 * q->b * q->d) + (2 * q->c * q->a);
	mat->c[1] = (2 * q->c * q->d) - (2 * q->b * q->a);
	mat->c[2] = 1.0f - (2 * sq(q->b)) - (2 * sq(q->c));
	mat->c[3] = 0.0f;

	mat->d[0] = 0.0f;
	mat->d[1] = 0.0f;
	mat->d[2] = 0.0f;
	mat->d[3] = 1.0f;
}

float fquat_get_angle(const struct fquat *q)
{
	return acosf(q->a) * 2.0f;
}

void fquat_get_axis(const struct fquat *q, struct fvec3 *axis)
{
	float inv;

	if (feq(q->a, 1.0f))
		inv = 1.0f;
	else
		inv = 1.0f / sqrtf(1.0f - (q->a * q->a));

	axis->x = q->b * inv;
	axis->y = q->c * inv;
	axis->z = q->d * inv;
}

void fquat_set_axis_angle(
	struct fquat *q,
	const struct fvec3 *axis,
	float angle
	)
{
	float tmp;

	tmp = sinf(angle * 0.5f);

	q->a = cosf(angle * 0.5f);

	q->b = axis->x * tmp;
	q->c = axis->y * tmp;
	q->d = axis->z * tmp;
}

void fquat_mul(
	struct fquat *q,
	const struct fquat *lv,
	const struct fquat *rv
	)
{
	q->a =   (lv->a * rv->a) - (lv->b * rv->b)
	       + (lv->c * rv->c) + (lv->d * rv->d);

	q->b =   (lv->b * rv->a) + (rv->b * lv->a)
	       + (lv->c * rv->d) - (lv->d * rv->c);

	q->c =   (lv->c * rv->a) + (rv->c * lv->a)
	       + (lv->d * rv->b) - (rv->d * lv->b);

	q->d =   (lv->d * rv->a) + (rv->d * lv->a)
	       + (lv->b * rv->c) - (lv->c * rv->b);
}

void fquat_inv(struct fquat *dest, const struct fquat *src)
{
	dest->a = -src->a;
	dest->b = -src->b;
	dest->c = -src->c;
	dest->d = -src->d;
	
	fquat_nrm(dest, dest);
}

void fquat_nrm(
	struct fquat *dest,
	const struct fquat *src
	)
{
	float len;

	len = fquat_len(src);

	if (fabsf(len) < 0.00001f)
		len = 1.0f;
	else
		len = 1.0f / len;

	dest->a = src->a * len;
	dest->b = src->b * len;
	dest->c = src->c * len;
	dest->d = src->d * len;
}

float fquat_len(const struct fquat *q)
{
	return sqrtf(fquat_len2(q));
}

float fquat_len2(const struct fquat *q)
{
	return sq(q->a) + sq(q->b) + sq(q->c) + sq(q->d);
}
