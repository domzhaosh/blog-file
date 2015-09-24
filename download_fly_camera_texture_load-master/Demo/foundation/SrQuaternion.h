/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/22
****************************************************************************/
#ifndef SR_FOUNDATION_NSQUATERNION_H_
#define SR_FOUNDATION_NSQUATERNION_H_
#include "SrSimpleTypes.h"
#include "SrVector3.h"

/** \addtogroup foundation
  @{
*/

/**
\brief This is a quaternion class. For more information on quaternion mathematics
consult a mathematics source on complex numbers.
 
*/

class SrQuaternion
	{
	public:
	/**
	\brief Default constructor, does not do any initialization.
	*/
	SR_INLINE SrQuaternion();

	/**
	\brief Copy constructor.
	*/
	SR_INLINE SrQuaternion(const SrQuaternion&);

	/**
	\brief copies xyz elements from v, and scalar from w (defaults to 0).
	*/
	SR_INLINE SrQuaternion(const SrVector3& v, float w = 0);

	/**
	\brief creates from angle-axis representation.

	note that if Angle > 360 the resulting rotation is Angle mod 360.
	
	<b>Unit:</b> Degrees
	*/
	SR_INLINE SrQuaternion(const float angle, const SrVector3 & axis);

	/**
	\brief Creates from orientation matrix.

	\param[in] m Rotation matrix to extract quaternion from.
	*/
	SR_INLINE SrQuaternion(const class SrMatrix33 &m); /* defined in SrMatrix33.h */


	/**
	\brief Set the quaternion to the identity rotation.
	*/
	SR_INLINE void id();

	/**
	\brief Test if the quaternion is the identity rotation.
	*/
	SR_INLINE bool isIdentityRotation() const;

	//setting:

	/**
	\brief Set the members of the quaternion, in order WXYZ
	*/
	SR_INLINE void setWXYZ(float w, float x, float y, float z);

	/**
	\brief Set the members of the quaternion, in order XYZW
	*/
	SR_INLINE void setXYZW(float x, float y, float z, float w);

	/**
	\brief Set the members of the quaternion, in order WXYZ
	*/
	SR_INLINE void setWXYZ(const float *);

	/**
	\brief Set the members of the quaternion, in order XYZW
	*/
	SR_INLINE void setXYZW(const float *);

	SR_INLINE SrQuaternion& operator=  (const SrQuaternion&);

	/**
	\brief Implicitly extends vector by a 0 w element.
	*/
	SR_INLINE SrQuaternion& operator=  (const SrVector3&);

	SR_INLINE void setx(const float& d);
	SR_INLINE void sety(const float& d);
	SR_INLINE void setz(const float& d);
	SR_INLINE void setw(const float& d);

	SR_INLINE void getWXYZ(SrF32 *) const;
	SR_INLINE void getXYZW(SrF32 *) const;

	SR_INLINE void getWXYZ(SrF64 *) const;
	SR_INLINE void getXYZW(SrF64 *) const;

	/**
	\brief returns true if all elements are finite (not NAN or INF, etc.)
	*/
	SR_INLINE bool isFinite() const;

	/**
	\brief sets to the quat [0,0,0,1]
	*/
	SR_INLINE void zero();

	/**
	\brief creates a random unit quaternion.
	*/
	SR_INLINE void random();
	/**
	\brief creates from angle-axis representation.

	Note that if Angle > 360 the resulting rotation is Angle mod 360.
	
	<b>Unit:</b> Degrees
	*/
	SR_INLINE void fromAngleAxis(float angle, const SrVector3 & axis);

	/**
	\brief Creates from angle-axis representation.

	Axis must be normalized!
	
	<b>Unit:</b> Radians
	*/
	SR_INLINE void fromAngleAxisFast(float AngleRadians, const SrVector3 & axis);

	/**
	\brief Sets this to the opposite rotation of this.
	*/
	SR_INLINE void invert();

	/**
	\brief Fetches the Angle/axis given by the SrQuaternion.

	<b>Unit:</b> Degrees
	*/
	SR_INLINE void getAngleAxis(float& Angle, SrVector3 & axis) const;

	/**
	\brief Gets the angle between this quat and the identity quaternion.

	<b>Unit:</b> Degrees
	*/
	SR_INLINE float getAngle() const;

	/**
	\brief Gets the angle between this quat and the argument

	<b>Unit:</b> Degrees
	*/
	SR_INLINE float getAngle(const SrQuaternion &) const;

	/**
	\brief This is the squared 4D vector length, should be 1 for unit quaternions.
	*/
	SR_INLINE float magnitudeSquared() const;

	/**
	\brief returns the scalar product of this and other.
	*/
	SR_INLINE float dot(const SrQuaternion &other) const;

	//modifiers:
	/**
	\brief maps to the closest unit quaternion.
	*/
	SR_INLINE void normalize();

	/*
	\brief assigns its own conjugate to itself.

	\note for unit quaternions, this is the inverse.
	*/
	SR_INLINE void conjugate();

	/**
	this = a * b
	*/
	SR_INLINE void multiply(const SrQuaternion& a, const SrQuaternion& b);

	/**
	this = a * v
	v is interpreted as quat [xyz0]
	*/
	SR_INLINE void multiply(const SrQuaternion& a, const SrVector3& v);

	/**
	this = slerp(t, a, b)
	*/
	SR_INLINE void slerp(const float t, const SrQuaternion& a, const SrQuaternion& b);

	/**
	rotates passed vec by rot expressed by unit quaternion.  overwrites arg with the result.
	*/
	SR_INLINE void rotate(SrVector3 &) const;

	/**
	rotates passed vec by this (assumed unitary)
	*/
	SR_INLINE const SrVector3 rot(const SrVector3 &) const;

	/**
	inverse rotates passed vec by this (assumed unitary)
	*/
	SR_INLINE const SrVector3 invRot(const SrVector3 &) const;

	/**
	transform passed vec by this rotation (assumed unitary) and translation p
	*/
	SR_INLINE const SrVector3 transform(const SrVector3 &v, const SrVector3 &p) const;

	/**
	inverse rotates passed vec by this (assumed unitary)
	*/
	SR_INLINE const SrVector3 invTransform(const SrVector3 &v, const SrVector3 &p) const;


	/**
	rotates passed vec by opposite of rot expressed by unit quaternion.  overwrites arg with the result.
	*/
	SR_INLINE void inverseRotate(SrVector3 &) const;



	/**
	negates all the elements of the quat.  q and -q represent the same rotation.
	*/
	SR_INLINE void negate();
	SR_INLINE SrQuaternion operator -() const; 

	SR_INLINE SrQuaternion& operator*= (const SrQuaternion&);
	SR_INLINE SrQuaternion& operator+= (const SrQuaternion&);
	SR_INLINE SrQuaternion& operator-= (const SrQuaternion&);
	SR_INLINE SrQuaternion& operator*= (const float s);

	/** the quaternion elements */
    float x,y,z,w;

	/** quaternion multiplication */
	SR_INLINE SrQuaternion operator *(const SrQuaternion &) const; 

	/** quaternion addition */
	SR_INLINE SrQuaternion operator +(const SrQuaternion &) const; 

	/** quaternion subtraction */
	SR_INLINE SrQuaternion operator -(const SrQuaternion &) const; 

	/** quaternion conjugate */
	SR_INLINE SrQuaternion operator !() const; 

    /* 
	ops we decided not to implement:
	bool  operator== (const SrQuaternion&) const;
	SrVector3  operator^  (const SrQuaternion& r_h_s) const;//same as normal quat rot, but casts itself into a vector.  (doesn't compute w term)
	SrQuaternion  operator*  (const SrVector3& v) const;//implicitly extends vector by a 0 w element.
	SrQuaternion  operator*  (const float Scale) const;
	*/

	friend class SrMatrix33;
	private:
		SrQuaternion(float ix, float iy, float iz, float iw);
	};




SR_INLINE SrQuaternion::SrQuaternion()
	{
	//nothing
	}


SR_INLINE SrQuaternion::SrQuaternion(const SrQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w)
	{
	}


SR_INLINE SrQuaternion::SrQuaternion(const SrVector3& v, float s)						// copy constructor, assumes w=0 
	{
	x = v.x;
	y = v.y;
	z = v.z;
	w = s;
	}


SR_INLINE SrQuaternion::SrQuaternion(const float angle, const SrVector3 & axis)				// creates a SrQuaternion from an Angle axis -- note that if Angle > 360 the resulting rotation is Angle mod 360
	{
	fromAngleAxis(angle,axis);
	}


SR_INLINE void SrQuaternion::id()
	{
	x = float(0);
	y = float(0);
	z = float(0);
	w = float(1);
	}

SR_INLINE bool SrQuaternion::isIdentityRotation() const
{
	return x==0 && y==0 && z==0 && fabsf(w)==1;
}


SR_INLINE void SrQuaternion::setWXYZ(float sw, float sx, float sy, float sz)
	{
	x = sx;
	y = sy;
	z = sz;
	w = sw;
	}


SR_INLINE void SrQuaternion::setXYZW(float sx, float sy, float sz, float sw)
	{
	x = sx;
	y = sy;
	z = sz;
	w = sw;
	}


SR_INLINE void SrQuaternion::setWXYZ(const float * d)
	{
	x = d[1];
	y = d[2];
	z = d[3];
	w = d[0];
	}


SR_INLINE void SrQuaternion::setXYZW(const float * d)
	{
	x = d[0];
	y = d[1];
	z = d[2];
	w = d[3];
	}


SR_INLINE void SrQuaternion::getWXYZ(SrF32 *d) const
	{
	d[1] = (SrF32)x;
	d[2] = (SrF32)y;
	d[3] = (SrF32)z;
	d[0] = (SrF32)w;
	}


SR_INLINE void SrQuaternion::getXYZW(SrF32 *d) const
	{
	d[0] = (SrF32)x;
	d[1] = (SrF32)y;
	d[2] = (SrF32)z;
	d[3] = (SrF32)w;
	}


SR_INLINE void SrQuaternion::getWXYZ(SrF64 *d) const
	{
	d[1] = (SrF64)x;
	d[2] = (SrF64)y;
	d[3] = (SrF64)z;
	d[0] = (SrF64)w;
	}


SR_INLINE void SrQuaternion::getXYZW(SrF64 *d) const
	{
	d[0] = (SrF64)x;
	d[1] = (SrF64)y;
	d[2] = (SrF64)z;
	d[3] = (SrF64)w;
	}

//const methods
 
SR_INLINE bool SrQuaternion::isFinite() const
	{
	return SrMath::isFinite(x) 
		&& SrMath::isFinite(y) 
		&& SrMath::isFinite(z)
		&& SrMath::isFinite(w);
	}



SR_INLINE void SrQuaternion::zero()
	{
	x = float(0.0);
	y = float(0.0);
	z = float(0.0);
	w = float(1.0);
	}


SR_INLINE void SrQuaternion::negate()
	{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	}

SR_INLINE SrQuaternion SrQuaternion::operator-() const
	{
	return SrQuaternion(-x,-y,-z,-w);
	}


SR_INLINE void SrQuaternion::random()
	{
	x = SrMath::rand(float(0.0),float(1.0));
	y = SrMath::rand(float(0.0),float(1.0));
	z = SrMath::rand(float(0.0),float(1.0));
	w = SrMath::rand(float(0.0),float(1.0));
	normalize();
	}


SR_INLINE void SrQuaternion::fromAngleAxis(float Angle, const SrVector3 & axis)			// set the SrQuaternion by Angle-axis (see AA constructor)
	{
	x = axis.x;
	y = axis.y;
	z = axis.z;

	// required: Normalize the axis

	const float i_length =  float(1.0) / SrMath::sqrt( x*x + y*y + z*z );
	
	x = x * i_length;
	y = y * i_length;
	z = z * i_length;

	// now make a clQuaternionernion out of it
	float Half = SrMath::degToRad(Angle * float(0.5));

	w = SrMath::cos(Half);//this used to be w/o deg to rad.
	const float sin_theta_over_two = SrMath::sin(Half );
	x = x * sin_theta_over_two;
	y = y * sin_theta_over_two;
	z = z * sin_theta_over_two;
	}

SR_INLINE void SrQuaternion::fromAngleAxisFast(float AngleRadians, const SrVector3 & axis)
	{
	float s;
	SrMath::sinCos(AngleRadians * 0.5f, s, w);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	}

SR_INLINE void SrQuaternion::invert()
	{
	x = -x;
	y = -y;
	z = -z;
	}

SR_INLINE void SrQuaternion::setx(const float& d) 
	{ 
	x = d;
	}


SR_INLINE void SrQuaternion::sety(const float& d) 
	{ 
	y = d;
	}


SR_INLINE void SrQuaternion::setz(const float& d) 
	{ 
	z = d;
	}


SR_INLINE void SrQuaternion::setw(const float& d) 
	{ 
	w = d;
	}


SR_INLINE void SrQuaternion::getAngleAxis(float& angle, SrVector3 & axis) const
	{
	//return axis and angle of rotation of quaternion
    angle = SrMath::acos(w) * float(2.0);		//this is getAngle()
    float sa = SrMath::sqrt(float(1.0) - w*w);
	if (sa)
		{
		axis.set(x/sa,y/sa,z/sa);
		angle = SrMath::radToDeg(angle);
		}
	else
		axis.set(float(1.0),float(0.0),float(0.0));

	}



SR_INLINE float SrQuaternion::getAngle() const
	{
	return SrMath::acos(w) * float(2.0);
	}



SR_INLINE float SrQuaternion::getAngle(const SrQuaternion & q) const
	{
	return SrMath::acos(dot(q)) * float(2.0);
	}


SR_INLINE float SrQuaternion::magnitudeSquared() const

//modifiers:
	{
	return x*x + y*y + z*z + w*w;
	}


SR_INLINE float SrQuaternion::dot(const SrQuaternion &v) const
	{
	return x * v.x + y * v.y + z * v.z  + w * v.w;
	}


SR_INLINE void SrQuaternion::normalize()											// convert this SrQuaternion to a unit clQuaternionernion
	{
	const float mag = SrMath::sqrt(magnitudeSquared());
	if (mag)
		{
		const float imag = float(1.0) / mag;
		
		x *= imag;
		y *= imag;
		z *= imag;
		w *= imag;
		}
	}


SR_INLINE void SrQuaternion::conjugate()											// convert this SrQuaternion to a unit clQuaternionernion
	{
	x = -x;
	y = -y;
	z = -z;
	}


SR_INLINE void SrQuaternion::multiply(const SrQuaternion& left, const SrQuaternion& right)		// this = a * b
	{
	float a,b,c,d;

	a =left.w*right.w - left.x*right.x - left.y*right.y - left.z*right.z;
	b =left.w*right.x + right.w*left.x + left.y*right.z - right.y*left.z;
	c =left.w*right.y + right.w*left.y + left.z*right.x - right.z*left.x;
	d =left.w*right.z + right.w*left.z + left.x*right.y - right.x*left.y;

	w = a;
	x = b;
	y = c;
	z = d;
	}


SR_INLINE void SrQuaternion::multiply(const SrQuaternion& left, const SrVector3& right)		// this = a * b
	{
	float a,b,c,d;

	a = - left.x*right.x - left.y*right.y - left.z *right.z;
	b =   left.w*right.x + left.y*right.z - right.y*left.z;
	c =   left.w*right.y + left.z*right.x - right.z*left.x;
	d =   left.w*right.z + left.x*right.y - right.x*left.y;

	w = a;
	x = b;
	y = c;
	z = d;
	}

SR_INLINE void SrQuaternion::slerp(const float t, const SrQuaternion& left, const SrQuaternion& right) // this = slerp(t, a, b)
	{
	const float	quatEpsilon = (float(1.0e-8f));

	*this = left;

	float cosine = 
		x * right.x + 
		y * right.y + 
		z * right.z + 
		w * right.w;		//this is left.dot(right)

	float sign = float(1);
	if (cosine < 0)
		{
		cosine = - cosine;
		sign = float(-1);
		}

	float Sin = float(1) - cosine*cosine;

	if(Sin>=quatEpsilon*quatEpsilon)	
		{
		Sin = SrMath::sqrt(Sin);
		const float angle = SrMath::atan2(Sin, cosine);
		const float i_sin_angle = float(1) / Sin;



		float lower_weight = SrMath::sin(angle*(float(1)-t)) * i_sin_angle;
		float upper_weight = SrMath::sin(angle * t) * i_sin_angle * sign;

		w = (w * (lower_weight)) + (right.w * (upper_weight));
		x = (x * (lower_weight)) + (right.x * (upper_weight));
		y = (y * (lower_weight)) + (right.y * (upper_weight));
		z = (z * (lower_weight)) + (right.z * (upper_weight));
		}
	}


SR_INLINE void SrQuaternion::rotate(SrVector3 & v) const						//rotates passed vec by rot expressed by quaternion.  overwrites arg ith the result.
	{
	//float msq = float(1.0)/magnitudeSquared();	//assume unit quat!
	SrQuaternion myInverse;
	myInverse.x = -x;//*msq;
	myInverse.y = -y;//*msq;
	myInverse.z = -z;//*msq;
	myInverse.w =  w;//*msq;

	//v = ((*this) * v) ^ myInverse;

	SrQuaternion left;
	left.multiply(*this,v);
	v.x =left.w*myInverse.x + myInverse.w*left.x + left.y*myInverse.z - myInverse.y*left.z;
	v.y =left.w*myInverse.y + myInverse.w*left.y + left.z*myInverse.x - myInverse.z*left.x;
	v.z =left.w*myInverse.z + myInverse.w*left.z + left.x*myInverse.y - myInverse.x*left.y;
	}


SR_INLINE void SrQuaternion::inverseRotate(SrVector3 & v) const				//rotates passed vec by opposite of rot expressed by quaternion.  overwrites arg ith the result.
	{
	//float msq = float(1.0)/magnitudeSquared();	//assume unit quat!
	SrQuaternion myInverse;
	myInverse.x = -x;//*msq;
	myInverse.y = -y;//*msq;
	myInverse.z = -z;//*msq;
	myInverse.w =  w;//*msq;

	//v = (myInverse * v) ^ (*this);
	SrQuaternion left;
	left.multiply(myInverse,v);
	v.x =left.w*x + w*left.x + left.y*z - y*left.z;
	v.y =left.w*y + w*left.y + left.z*x - z*left.x;
	v.z =left.w*z + w*left.z + left.x*y - x*left.y;
	}


SR_INLINE SrQuaternion& SrQuaternion::operator=  (const SrQuaternion& q)
	{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
	}

#if 0
SrQuaternion& SrQuaternion::operator=  (const SrVector3& v)		//implicitly extends vector by a 0 w element.
	{
	x = v.x;
	y = v.y;
	z = v.z;
	w = float(1.0);
	return *this;
	}
#endif

SR_INLINE SrQuaternion& SrQuaternion::operator*= (const SrQuaternion& q)
	{
	float xx[4]; //working Quaternion
	xx[0] = w*q.w - q.x*x - y*q.y - q.z*z;
	xx[1] = w*q.x + q.w*x + y*q.z - q.y*z;
	xx[2] = w*q.y + q.w*y + z*q.x - q.z*x;
	z=w*q.z + q.w*z + x*q.y - q.x*y;

	w = xx[0];
	x = xx[1];
	y = xx[2];
	return *this;
	}


SR_INLINE SrQuaternion& SrQuaternion::operator+= (const SrQuaternion& q)
	{
	x+=q.x;
	y+=q.y;
	z+=q.z;
	w+=q.w;
	return *this;
	}


SR_INLINE SrQuaternion& SrQuaternion::operator-= (const SrQuaternion& q)
	{
	x-=q.x;
	y-=q.y;
	z-=q.z;
	w-=q.w;
	return *this;
	}


SR_INLINE SrQuaternion& SrQuaternion::operator*= (const float s)
	{
	x*=s;
	y*=s;
	z*=s;
	w*=s;
	return *this;
	}

SR_INLINE SrQuaternion::SrQuaternion(float ix, float iy, float iz, float iw)
{
	x = ix;
	y = iy;
	z = iz;
	w = iw;
}

SR_INLINE SrQuaternion SrQuaternion::operator*(const SrQuaternion &q) const
{
	return SrQuaternion(w*q.x + q.w*x + y*q.z - q.y*z,
				  w*q.y + q.w*y + z*q.x - q.z*x,
				  w*q.z + q.w*z + x*q.y - q.x*y,
				  w*q.w - x*q.x - y*q.y - z*q.z);
}

SR_INLINE SrQuaternion SrQuaternion::operator+(const SrQuaternion &q) const
{
	return SrQuaternion(x+q.x,y+q.y,z+q.z,w+q.w);
}

SR_INLINE SrQuaternion SrQuaternion::operator-(const SrQuaternion &q) const
{
	return SrQuaternion(x-q.x,y-q.y,z-q.z,w-q.w);
}

SR_INLINE SrQuaternion SrQuaternion::operator!() const
{
	return SrQuaternion(-x,-y,-z,w);
}



SR_INLINE const SrVector3 SrQuaternion::rot(const SrVector3 &v) const
    {
	SrVector3 qv(x,y,z);

	return (v*(w*w-0.5f) + (qv^v)*w + qv*(qv|v))*2;
    }

SR_INLINE const SrVector3 SrQuaternion::invRot(const SrVector3 &v) const
    {
	SrVector3 qv(x,y,z);

	return (v*(w*w-0.5f) - (qv^v)*w + qv*(qv|v))*2;
    }



SR_INLINE const SrVector3 SrQuaternion::transform(const SrVector3 &v, const SrVector3 &p) const
    {
	return rot(v)+p;
    }

SR_INLINE const SrVector3 SrQuaternion::invTransform(const SrVector3 &v, const SrVector3 &p) const
    {
	return invRot(v-p);
    }

/** @} */
#endif
