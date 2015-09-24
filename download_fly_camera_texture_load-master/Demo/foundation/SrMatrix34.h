/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/22
****************************************************************************/
#ifndef SR_FOUNDATION_SRMATRIX34T_H_
#define SR_FOUNDATION_SRMATRIX34T_H_
/** \addtogroup foundation
  @{
*/

#include "SrMatrix33.h"

/**
\brief Combination of a 3x3 rotation matrix and a translation vector.

homogenous transform class composed of a matrix and a vector.
*/

class SrMatrix34
	{
	public:
	/**
	\brief [ M t ]
	*/
	SrMatrix33 M;
	SrVector3 t;

	/**
	\brief by default M is inited and t isn't.  Use this ctor to either init or not init in full.
	*/
	SR_INLINE explicit SrMatrix34(bool init = true);

	SR_INLINE SrMatrix34(const SrMatrix33& rot, const SrVector3& trans) : M(rot), t(trans)
		{
		}

	SR_INLINE void zero();

	SR_INLINE void id();

	/**
	\brief returns true for identity matrix
	*/
	SR_INLINE bool isIdentity() const;

	/**
	\brief returns true if all elems are finite (not NAN or INF, etc.)
	*/
	SR_INLINE bool isFinite() const;

	/**
	\brief assigns inverse to dest. 
	
	Returns false if singular (i.e. if no inverse exists), setting dest to identity.  dest may equal this.
	*/
	SR_INLINE bool getInverse(SrMatrix34& dest) const;

	/**
	\brief same as #getInverse(), but assumes that M is orthonormal
	*/
	SR_INLINE bool getInverseRT(SrMatrix34& dest) const;

	/**
	\brief dst = this * src
	*/
	SR_INLINE void multiply(const SrVector3 &src, SrVector3 &dst) const;

	/**
	\brief operator wrapper for multiply
	*/
	SR_INLINE SrVector3 operator*  (const SrVector3 & src) const { SrVector3 dest; multiply(src, dest); return dest; }
	/**
	\brief dst = inverse(this) * src	-- assumes M is rotation matrix!!!
	*/
	SR_INLINE void multiplyByInverseRT(const SrVector3 &src, SrVector3 &dst) const;

	/**
	\brief operator wrapper for multiplyByInverseRT
	*/
	SR_INLINE SrVector3 operator%  (const SrVector3 & src) const { SrVector3 dest; multiplyByInverseRT(src, dest); return dest; }

	/**
	\brief this = left * right	
	*/
	SR_INLINE void multiply(const SrMatrix34& left, const SrMatrix34& right);

	/**
	\brief this = inverse(left) * right	-- assumes M is rotation matrix!!!
	*/
	SR_INLINE void multiplyInverseRTLeft(const SrMatrix34& left, const SrMatrix34& right);

	/**
	\brief this = left * inverse(right)	-- assumes M is rotation matrix!!!
	*/
	SR_INLINE void multiplyInverseRTRight(const SrMatrix34& left, const SrMatrix34& right);

	/**
	\brief operator wrapper for multiply
	*/
	SR_INLINE SrMatrix34 operator*  (const SrMatrix34 & right) const { SrMatrix34 dest(false); dest.multiply(*this, right); return dest; }

	/**
	\brief convert from a matrix format appropriate for rendering
	*/
	SR_INLINE void setColumnMajor44(const SrF32 *);
	/**
	\brief convert from a matrix format appropriate for rendering
	*/
	SR_INLINE void setColumnMajor44(const SrF32 d[4][4]);
	/**
	\brief convert to a matrix format appropriate for rendering
	*/
	SR_INLINE void getColumnMajor44(SrF32 *) const;
	/**
	\brief convert to a matrix format appropriate for rendering
	*/
	SR_INLINE void getColumnMajor44(SrF32 d[4][4]) const;
	/**
	\brief set the matrix given a row major matrix.
	*/
	SR_INLINE void setRowMajor44(const SrF32 *);
	/**
	\brief set the matrix given a row major matrix.
	*/
	SR_INLINE void setRowMajor44(const SrF32 d[4][4]);
	/**
	\brief retrieve the matrix in a row major format.
	*/
	SR_INLINE void getRowMajor44(SrF32 *) const;
	/**
	\brief retrieve the matrix in a row major format.
	*/
	SR_INLINE void getRowMajor44(SrF32 d[4][4]) const;
	};


SR_INLINE SrMatrix34::SrMatrix34(bool init)
	{
	if (init)
	{
		t.zero();
		M.id();
	}
	}


SR_INLINE void SrMatrix34::zero()
	{
	M.zero();
	t.zero();
	}


SR_INLINE void SrMatrix34::id()
	{
	M.id();
	t.zero();
	}


SR_INLINE bool SrMatrix34::isIdentity() const
	{
	if(!M.isIdentity())	return false;
	if(!t.isZero())		return false;
	return true;
	}


SR_INLINE bool SrMatrix34::isFinite() const
	{
	if(!M.isFinite())	return false;
	if(!t.isFinite())	return false;
	return true;
	}


SR_INLINE bool SrMatrix34::getInverse(SrMatrix34& dest) const
	{
	// inv(this) = [ inv(M) , inv(M) * -t ]
	bool status = M.getInverse(dest.M);
	dest.M.multiply(t * -1.0f, dest.t); 
	return status;
	}


SR_INLINE bool SrMatrix34::getInverseRT(SrMatrix34& dest) const
	{
	// inv(this) = [ M' , M' * -t ]
	dest.M.setTransposed(M);
	dest.M.multiply(t * -1.0f, dest.t); 
	return true;
	}



SR_INLINE void SrMatrix34::multiply(const SrVector3 &src, SrVector3 &dst) const
	{
	dst = M * src + t;
	}


SR_INLINE void SrMatrix34::multiplyByInverseRT(const SrVector3 &src, SrVector3 &dst) const
	{
	//dst = M' * src - M' * t = M' * (src - t)
	M.multiplyByTranspose(src - t, dst);
	}


SR_INLINE void SrMatrix34::multiply(const SrMatrix34& left, const SrMatrix34& right)
	{
	//[aR at] * [bR bt] = [aR * bR		aR * bt + at]  NOTE: order of operations important so it works when this ?= left ?= right.
	t = left.M * right.t + left.t;
	M.multiply(left.M, right.M);
	}


SR_INLINE void SrMatrix34::multiplyInverseRTLeft(const SrMatrix34& left, const SrMatrix34& right)
	{
	//[aR' -aR'*at] * [bR bt] = [aR' * bR		aR' * bt  - aR'*at]	//aR' ( bt  - at )	NOTE: order of operations important so it works when this ?= left ?= right.
	t = left.M % (right.t - left.t);
	M.multiplyTransposeLeft(left.M, right.M);
	}


SR_INLINE void SrMatrix34::multiplyInverseRTRight(const SrMatrix34& left, const SrMatrix34& right)
	{
	//[aR at] * [bR' -bR'*bt] = [aR * bR'		-aR * bR' * bt + at]	NOTE: order of operations important so it works when this ?= left ?= right.
	M.multiplyTransposeRight(left.M, right.M);
	t = left.t - M * right.t;
	}

SR_INLINE void SrMatrix34::setColumnMajor44(const SrF32 * d) 
	{
	M.setColumnMajorStride4(d);
    t.x = d[12];
	t.y = d[13];
	t.z = d[14];
	}

SR_INLINE void SrMatrix34::setColumnMajor44(const SrF32 d[4][4]) 
	{
	M.setColumnMajorStride4(d);
    t.x = d[3][0];
	t.y = d[3][1];
	t.z = d[3][2];
	}

SR_INLINE void SrMatrix34::getColumnMajor44(SrF32 * d) const
	{
	M.getColumnMajorStride4(d);
    d[12] = t.x;
	d[13] = t.y;
	d[14] = t.z;
	d[3] = d[7] = d[11] = 0.0f;
	d[15] = 1.0f;
	}

SR_INLINE void SrMatrix34::getColumnMajor44(SrF32 d[4][4]) const
	{
	M.getColumnMajorStride4(d);
    d[3][0] = t.x;
	d[3][1] = t.y;
	d[3][2] = t.z;
	d[0][3] = d[1][3] = d[2][3] = 0.0f;
	d[3][3] = 1.0f;
	}

SR_INLINE void SrMatrix34::setRowMajor44(const SrF32 * d) 
	{
	M.setRowMajorStride4(d);
    t.x = d[3];
	t.y = d[7];
	t.z = d[11];
	}

SR_INLINE void SrMatrix34::setRowMajor44(const SrF32 d[4][4])
	{
	M.setRowMajorStride4(d);
    t.x = d[0][3];
	t.y = d[1][3];
	t.z = d[2][3];
	}

SR_INLINE void SrMatrix34::getRowMajor44(SrF32 * d) const
	{
	M.getRowMajorStride4(d);
    d[3] = t.x;
	d[7] = t.y;
	d[11] = t.z;
	d[12] = d[13] = d[14] = 0.0f;
	d[15] = 1.0f;
	}

SR_INLINE void SrMatrix34::getRowMajor44(SrF32 d[4][4]) const
	{
	M.getRowMajorStride4(d);
    d[0][3] = t.x;
	d[1][3] = t.y;
	d[2][3] = t.z;
	d[3][0] = d[3][1] = d[3][2] = 0.0f;
	d[3][3] = 1.0f;
	}
/** @} */
#endif
