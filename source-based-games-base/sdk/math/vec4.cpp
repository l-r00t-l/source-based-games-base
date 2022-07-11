#include "pch.h"
#include "vec4.h"


void VectorCopy(const vec4_t& src, vec4_t& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	dst.w = src.w;
}
void VectorLerp(const vec4_t& src1, const vec4_t& src2, vec_t t, vec4_t& dest)
{
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
	dest.w = src1.w + (src2.w - src1.w) * t;
}
float VectorLength(const vec4_t& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec_t NormalizeVector(vec4_t& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = v.z = v.w = 0.0f;
	}
	return l;
}

vec4_t::vec4_t(void)
{
	Invalidate();
}
vec4_t::vec4_t(vec_t X, vec_t Y, vec_t Z, vec_t W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}
vec4_t::vec4_t(vec_t* clr)
{
	x = clr[0];
	y = clr[1];
	z = clr[2];
	w = clr[3];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void vec4_t::Init(vec_t ix, vec_t iy, vec_t iz, vec_t iw)
{
	x = ix; y = iy; z = iz; w = iw;
}

void vec4_t::Random(vec_t minVal, vec_t maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
void vec4_t::Zero()
{
	x = y = z = w = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

vec4_t& vec4_t::operator=(const vec4_t& vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
	return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
vec_t& vec4_t::operator[](int i)
{
	return ((vec_t*)this)[i];
}

vec_t vec4_t::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
vec_t* vec4_t::Base()
{
	return (vec_t*)this;
}

vec_t const* vec4_t::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool vec4_t::IsValid() const
{
	return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

void vec4_t::Invalidate()
{
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	x = y = z = w = std::numeric_limits<float>::infinity();
	//#endif
	//#endif
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool vec4_t::operator==(const vec4_t& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

bool vec4_t::operator!=(const vec4_t& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------
void vec4_t::CopyToArray(float* rgfl) const
{
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
}

//-----------------------------------------------------------------------------
// standard Math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

void vec4_t::Negate()
{
	x = -x; y = -y; z = -z; w = -w;
}

// Get the component of this vector parallel to some other given vector
vec4_t vec4_t::ProjectOnto(const vec4_t& onto)
{
	return onto * (this->Dot(onto) / (onto.LengthSqr()));
}

// FIXME: Remove
// For backwards compatability
void vec4_t::MulAdd(const vec4_t& a, const vec4_t& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
	w = a.w + b.w * scalar;
}

vec4_t VectorLerp(const vec4_t& src1, const vec4_t& src2, vec_t t)
{
	vec4_t result;
	VectorLerp(src1, src2, t, result);
	return result;
}

vec_t vec4_t::Dot(const vec4_t& b) const
{
	return (x * b.x + y * b.y + z * b.z + w * b.w);
}
void VectorClear(vec4_t& a)
{
	a.x = a.y = a.z = a.w = 0.0f;
}

vec_t vec4_t::Length(void) const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

// check a point against a box
bool vec4_t::WithinAABox(vec4_t const& boxmin, vec4_t const& boxmax)
{
	return (
		(x >= boxmin.x) && (x <= boxmax.x) &&
		(y >= boxmin.y) && (y <= boxmax.y) &&
		(z >= boxmin.z) && (z <= boxmax.z) &&
		(w >= boxmin.w) && (w <= boxmax.w)
		);
}

//-----------------------------------------------------------------------------
// Get the distance from this vector to the other one 
//-----------------------------------------------------------------------------
vec_t vec4_t::DistTo(const vec4_t& vOther) const
{
	vec4_t delta;
	delta = *this - vOther;
	return delta.Length();
}

//-----------------------------------------------------------------------------
// Returns a vector with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
vec4_t vec4_t::Min(const vec4_t& vOther) const
{
	return vec4_t(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y,
		z < vOther.z ? z : vOther.z,
		w < vOther.w ? w : vOther.w);
}

vec4_t vec4_t::Max(const vec4_t& vOther) const
{
	return vec4_t(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y,
		z > vOther.z ? z : vOther.z,
		w > vOther.w ? w : vOther.w);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

vec4_t vec4_t::operator-(void) const
{
	return vec4_t(-x, -y, -z, -w);
}

vec4_t vec4_t::operator+(const vec4_t& v) const
{
	return vec4_t(x + v.x, y + v.y, z + v.z, w + v.w);
}

vec4_t vec4_t::operator-(const vec4_t& v) const
{
	return vec4_t(x - v.x, y - v.y, z - v.z, w - v.w);
}

vec4_t vec4_t::operator*(float fl) const
{
	return vec4_t(x * fl, y * fl, z * fl, w * fl);
}

vec4_t vec4_t::operator*(const vec4_t& v) const
{
	return vec4_t(x * v.x, y * v.y, z * v.z, w * v.w);
}

vec4_t vec4_t::operator/(float fl) const
{
	return vec4_t(x / fl, y / fl, z / fl, w / fl);
}

vec4_t vec4_t::operator/(const vec4_t& v) const
{
	return vec4_t(x / v.x, y / v.y, z / v.z, w / v.w);
}

vec4_t operator*(float fl, const vec4_t& v)
{
	return v * fl;
}