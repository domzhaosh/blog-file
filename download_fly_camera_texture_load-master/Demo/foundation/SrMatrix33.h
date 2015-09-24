/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/22
****************************************************************************/
#ifndef SR_FOUNDATION_SRMATRIX33T_H_
#define SR_FOUNDATION_SRMATRIX33T_H_
/** \addtogroup foundation
  @{
*/

#include "SrVector3.h"
#include "SrQuaternion.h"
class Mat33DataType
{
public:
	struct S
	{

		float        _11, _12, _13;
		float        _21, _22, _23;
		float        _31, _32, _33;
	};
	union 
	{
		S s;
		float m[3][3];
	};
};

/**
\brief Identifies a special matrix. Can be passed to the #SrMatrix33 constructor.
*/
enum SrMatrixType
	{
	/**
	\brief Matrix of all zeros.
	*/
	SR_ZERO_MATRIX,

	/**
	\brief Identity matrix.
	*/
	SR_IDENTITY_MATRIX
	};


/**
\brief 3x3 Matrix Class.

 The idea of the matrix/vector classes is to partition them into two parts:
 One is the data structure which may have different formatting (3x3, 3x4, 4x4),
 row or column major.  The other is a template class which has all the operators
 but is storage format independent.

 This way it should be easier to change formats depending on what is faster/slower
 on a particular platform.

 Design issue: We use nameless struct/unions here.
 Design issue: this used to be implemented with a template.  This had no benefit
 but it added syntactic complexity.  Currently we just use a typedef and a preprocessor switch 
 to change between different memory layouts.

 The matrix math in this class is storage format (row/col major) independent as far
 as the user is concerned.
 When the user wants to get/set raw data, he needs to specify what order the data is
 coming in.  
 
*/
class SrMatrix33
	{
	public:
	SR_INLINE SrMatrix33();

	/**
	\param type Special matrix type to initialize with.

	@see SrMatrixType
	*/
	SR_INLINE SrMatrix33(SrMatrixType type);
	SR_INLINE SrMatrix33(const SrVector3 &row0, const SrVector3 &row1, const SrVector3 &row2);

	SR_INLINE SrMatrix33(const SrMatrix33&m);
	SR_INLINE SrMatrix33(const SrQuaternion &m);
	SR_INLINE ~SrMatrix33();
	SR_INLINE const SrMatrix33& operator=(const SrMatrix33 &src);

	// Access elements

	//low level data access, single or double precision, with eventual translation:
	//for dense 9 element data
	SR_INLINE void setRowMajor(const SrF32 *);
	SR_INLINE void setRowMajor(const SrF32 d[][3]);
	SR_INLINE void setColumnMajor(const SrF32 *);
	SR_INLINE void setColumnMajor(const SrF32 d[][3]);
	SR_INLINE void getRowMajor(SrF32 *) const;
	SR_INLINE void getRowMajor(SrF32 d[][3]) const;
	SR_INLINE void getColumnMajor(SrF32 *) const;
	SR_INLINE void getColumnMajor(SrF32 d[][3]) const;

	SR_INLINE void setRowMajor(const SrF64 *);
	SR_INLINE void setRowMajor(const SrF64 d[][3]);
	SR_INLINE void setColumnMajor(const SrF64 *);
	SR_INLINE void setColumnMajor(const SrF64 d[][3]);
	SR_INLINE void getRowMajor(SrF64 *) const;
	SR_INLINE void getRowMajor(SrF64 d[][3]) const;
	SR_INLINE void getColumnMajor(SrF64 *) const;
	SR_INLINE void getColumnMajor(SrF64 d[][3]) const;


	//for loose 4-padded data.
	SR_INLINE void setRowMajorStride4(const SrF32 *);
	SR_INLINE void setRowMajorStride4(const SrF32 d[][4]);
	SR_INLINE void setColumnMajorStride4(const SrF32 *);
	SR_INLINE void setColumnMajorStride4(const SrF32 d[][4]);
	SR_INLINE void getRowMajorStride4(SrF32 *) const;
	SR_INLINE void getRowMajorStride4(SrF32 d[][4]) const;
	SR_INLINE void getColumnMajorStride4(SrF32 *) const;
	SR_INLINE void getColumnMajorStride4(SrF32 d[][4]) const;

	SR_INLINE void setRowMajorStride4(const SrF64 *);
	SR_INLINE void setRowMajorStride4(const SrF64 d[][4]);
	SR_INLINE void setColumnMajorStride4(const SrF64 *);
	SR_INLINE void setColumnMajorStride4(const SrF64 d[][4]);
	SR_INLINE void getRowMajorStride4(SrF64 *) const;
	SR_INLINE void getRowMajorStride4(SrF64 d[][4]) const;
	SR_INLINE void getColumnMajorStride4(SrF64 *) const;
	SR_INLINE void getColumnMajorStride4(SrF64 d[][4]) const;


	SR_INLINE void setRow(int row, const SrVector3 &);
	SR_INLINE void setColumn(int col, const SrVector3 &);
	SR_INLINE void getRow(int row, SrVector3 &) const;
	SR_INLINE void getColumn(int col, SrVector3 &) const;

	SR_INLINE SrVector3 getRow(int row) const;
	SR_INLINE SrVector3 getColumn(int col) const;


	//element access:
    SR_INLINE float & operator()(int row, int col);
    SR_INLINE const float & operator() (int row, int col) const;

	/**
	\brief returns true for identity matrix
	*/
	SR_INLINE bool isIdentity() const;

	/**
	\brief returns true for zero matrix
	*/
	SR_INLINE bool isZero() const;

	/**
	\brief returns true if all elems are finite (not NAN or INF, etc.)
	*/
	SR_INLINE bool isFinite() const;

	//create special matrices:

	/**
	\brief sets this matrix to the zero matrix.
	*/
	SR_INLINE void zero();

	/**
	\brief sets this matrix to the identity matrix.
	*/
	SR_INLINE void id();

	/**
	\brief this = -this
	*/
	SR_INLINE void setNegative();

	/**
	\brief sets this matrix to the diagonal matrix.
	*/
	SR_INLINE void diagonal(const SrVector3 &vec);

	/**
	\brief Sets this matrix to the Star(Skew Symetric) matrix.

	So that star(v) * x = v.cross(x) .
	*/
	SR_INLINE void star(const SrVector3 &vec);


	SR_INLINE void fromQuat(const SrQuaternion &);
	SR_INLINE void toQuat(SrQuaternion &) const;

	//modifications:

	SR_INLINE const SrMatrix33 &operator +=(const SrMatrix33 &s);
	SR_INLINE const SrMatrix33 &operator -=(const SrMatrix33 &s);
	SR_INLINE const SrMatrix33 &operator *=(float s);
	SR_INLINE const SrMatrix33 &operator /=(float s);

	/*
	Gram-Schmidt orthogonalization to correct numerical drift, plus column normalization
	Caution: I believe the current implementation does not work right!
	*/
//	void orthonormalize();


	/**
	\brief returns determinant
	*/
	SR_INLINE float determinant() const;

	/**
	\brief assigns inverse to dest.
	
	Returns false if singular (i.e. if no inverse exists), setting dest to identity.
	*/
	SR_INLINE bool getInverse(SrMatrix33& dest) const;

	/**
	\brief this = transpose(other)

	this == other is OK.
	*/
	SR_INLINE void setTransposed(const SrMatrix33& other);

	/**
	\brief this = transpose(this)
	*/
	SR_INLINE void setTransposed();

	/**
	\brief this = this * [ d.x 0 0; 0 d.y 0; 0 0 d.z];
	*/
	SR_INLINE void multiplyDiagonal(const SrVector3 &d);

	/**
	\brief this = transpose(this) * [ d.x 0 0; 0 d.y 0; 0 0 d.z];
	*/
	SR_INLINE void multiplyDiagonalTranspose(const SrVector3 &d);

	/**
	\brief dst = this * [ d.x 0 0; 0 d.y 0; 0 0 d.z];
	*/
	SR_INLINE void multiplyDiagonal(const SrVector3 &d, SrMatrix33 &dst) const;

	/**
	\brief dst = transpose(this) * [ d.x 0 0; 0 d.y 0; 0 0 d.z];
	*/
	SR_INLINE void multiplyDiagonalTranspose(const SrVector3 &d, SrMatrix33 &dst) const;

	/**
	\brief dst = this * src
	*/
	SR_INLINE void multiply(const SrVector3 &src, SrVector3 &dst) const;
	/**
	\brief dst = transpose(this) * src
	*/
	SR_INLINE void multiplyByTranspose(const SrVector3 &src, SrVector3 &dst) const;

	/**
	\brief this = a + b
	*/
	SR_INLINE void  add(const SrMatrix33 & a, const SrMatrix33 & b);
	/***
	\brief this = a - b
	*/
	SR_INLINE void  subtract(const SrMatrix33 &a, const SrMatrix33 &b);
	/**
	\brief this = s * a;
	*/
	SR_INLINE void  multiply(float s,  const SrMatrix33 & a);
	/**
	\brief this = left * right
	*/
	SR_INLINE void multiply(const SrMatrix33& left, const SrMatrix33& right);
	/**
	\brief this = transpose(left) * right

	\note #multiplyByTranspose() is faster.
	*/
	SR_INLINE void multiplyTransposeLeft(const SrMatrix33& left, const SrMatrix33& right);
	/**
	\brief this = left * transpose(right)
	
	\note faster than #multiplyByTranspose().
	*/
	SR_INLINE void multiplyTransposeRight(const SrMatrix33& left, const SrMatrix33& right);

	/**
	\brief this = left * transpose(right)
	*/
	SR_INLINE void multiplyTransposeRight(const SrVector3 &left, const SrVector3 &right);

	/**
	\brief this = rotation matrix around X axis

	<b>Unit:</b> Radians
	*/
	SR_INLINE void rotX(float angle);

	/**
	\brief this = rotation matrix around Y axis

	<b>Unit:</b> Radians
	*/
	SR_INLINE void rotY(float angle);

	/**
	\brief this = rotation matrix around Z axis

	<b>Unit:</b> Radians
	*/
	SR_INLINE void rotZ(float angle);


	//overloaded multiply, and transposed-multiply ops:

	/**
	\brief returns transpose(this)*src
	*/
	SR_INLINE SrVector3 operator%  (const SrVector3 & src) const;
	/**
	\brief matrix vector product
	*/
	SR_INLINE SrVector3 operator*  (const SrVector3 & src) const;
	/**
	\brief matrix product
	*/
	SR_INLINE SrMatrix33&	operator*= (const SrMatrix33& mat);
	/**
	\brief matrix difference
	*/
	SR_INLINE SrMatrix33	operator-  (const SrMatrix33& mat)	const;
	/**
	\brief matrix addition
	*/
	SR_INLINE SrMatrix33	operator+  (const SrMatrix33& mat)	const;
	/**
	\brief matrix product
	*/
	SR_INLINE SrMatrix33	operator*  (const SrMatrix33& mat)	const;
	/**
	\brief matrix scalar product
	*/
	SR_INLINE SrMatrix33	operator*  (float s)				const;

	private:
	Mat33DataType data;
	};


SR_INLINE SrMatrix33::SrMatrix33()
	{
	}


SR_INLINE SrMatrix33::SrMatrix33(SrMatrixType type)
	{
		switch(type)
		{
			case SR_ZERO_MATRIX:		zero();	break;
			case SR_IDENTITY_MATRIX:	id();	break;
		}
	}


SR_INLINE SrMatrix33::SrMatrix33(const SrMatrix33& a)
	{
	data = a.data;
	}


SR_INLINE SrMatrix33::SrMatrix33(const SrQuaternion &q)
	{
	fromQuat(q);
	}

SR_INLINE SrMatrix33::SrMatrix33(const SrVector3 &row0, const SrVector3 &row1, const SrVector3 &row2)
{
	data.s._11 = row0.x;  data.s._12 = row0.y;  data.s._13 = row0.z;
	data.s._21 = row1.x;  data.s._22 = row1.y;  data.s._23 = row1.z;
	data.s._31 = row2.x;  data.s._32 = row2.y;  data.s._33 = row2.z;
}


SR_INLINE SrMatrix33::~SrMatrix33()
	{
	//nothing
	}


SR_INLINE const SrMatrix33& SrMatrix33::operator=(const SrMatrix33 &a)
	{
	data = a.data;
	return *this;
	}


SR_INLINE void SrMatrix33::setRowMajor(const SrF32* d)
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[1];
	data.s._13 = (float)d[2];

	data.s._21 = (float)d[3];
	data.s._22 = (float)d[4];
	data.s._23 = (float)d[5];

	data.s._31 = (float)d[6];
	data.s._32 = (float)d[7];
	data.s._33 = (float)d[8];
	}


SR_INLINE void SrMatrix33::setRowMajor(const SrF32 d[][3])
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[0][1];
	data.s._13 = (float)d[0][2];

	data.s._21 = (float)d[1][0];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[1][2];

	data.s._31 = (float)d[2][0];
	data.s._32 = (float)d[2][1];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::setColumnMajor(const SrF32* d)
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[3];
	data.s._13 = (float)d[6];

	data.s._21 = (float)d[1];
	data.s._22 = (float)d[4];
	data.s._23 = (float)d[7];

	data.s._31 = (float)d[2];
	data.s._32 = (float)d[5];
	data.s._33 = (float)d[8];
	}


SR_INLINE void SrMatrix33::setColumnMajor(const SrF32 d[][3])
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[1][0];
	data.s._13 = (float)d[2][0];

	data.s._21 = (float)d[0][1];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[2][1];

	data.s._31 = (float)d[0][2];
	data.s._32 = (float)d[1][2];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::getRowMajor(SrF32* d) const
	{
	//we are also row major, so this is a direct copy
	d[0] = (SrF32)data.s._11;
	d[1] = (SrF32)data.s._12;
	d[2] = (SrF32)data.s._13;

	d[3] = (SrF32)data.s._21;
	d[4] = (SrF32)data.s._22;
	d[5] = (SrF32)data.s._23;

	d[6] = (SrF32)data.s._31;
	d[7] = (SrF32)data.s._32;
	d[8] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getRowMajor(SrF32 d[][3]) const
	{
	//we are also row major, so this is a direct copy
	d[0][0] = (SrF32)data.s._11;
	d[0][1] = (SrF32)data.s._12;
	d[0][2] = (SrF32)data.s._13;

	d[1][0] = (SrF32)data.s._21;
	d[1][1] = (SrF32)data.s._22;
	d[1][2] = (SrF32)data.s._23;

	d[2][0] = (SrF32)data.s._31;
	d[2][1] = (SrF32)data.s._32;
	d[2][2] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajor(SrF32* d) const
	{
	//we are column major, so copy transposed.
	d[0] = (SrF32)data.s._11;
	d[3] = (SrF32)data.s._12;
	d[6] = (SrF32)data.s._13;

	d[1] = (SrF32)data.s._21;
	d[4] = (SrF32)data.s._22;
	d[7] = (SrF32)data.s._23;

	d[2] = (SrF32)data.s._31;
	d[5] = (SrF32)data.s._32;
	d[8] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajor(SrF32 d[][3]) const
	{
	//we are column major, so copy transposed.
	d[0][0] = (SrF32)data.s._11;
	d[1][0] = (SrF32)data.s._12;
	d[2][0] = (SrF32)data.s._13;

	d[0][1] = (SrF32)data.s._21;
	d[1][1] = (SrF32)data.s._22;
	d[2][1] = (SrF32)data.s._23;

	d[0][2] = (SrF32)data.s._31;
	d[1][2] = (SrF32)data.s._32;
	d[2][2] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::setRowMajorStride4(const SrF32* d)
	{
	//we are also row major, so this is a direct copy
	//however we've got to skip every 4th element.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[1];
	data.s._13 = (float)d[2];

	data.s._21 = (float)d[4];
	data.s._22 = (float)d[5];
	data.s._23 = (float)d[6];

	data.s._31 = (float)d[8];
	data.s._32 = (float)d[9];
	data.s._33 = (float)d[10];
	}


SR_INLINE void SrMatrix33::setRowMajorStride4(const SrF32 d[][4])
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[0][1];
	data.s._13 = (float)d[0][2];

	data.s._21 = (float)d[1][0];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[1][2];

	data.s._31 = (float)d[2][0];
	data.s._32 = (float)d[2][1];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::setColumnMajorStride4(const SrF32* d)
	{
	//we are column major, so copy transposed.
	//however we've got to skip every 4th element.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[4];
	data.s._13 = (float)d[8];

	data.s._21 = (float)d[1];
	data.s._22 = (float)d[5];
	data.s._23 = (float)d[9];

	data.s._31 = (float)d[2];
	data.s._32 = (float)d[6];
	data.s._33 = (float)d[10];
	}


SR_INLINE void SrMatrix33::setColumnMajorStride4(const SrF32 d[][4])
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[1][0];
	data.s._13 = (float)d[2][0];

	data.s._21 = (float)d[0][1];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[2][1];

	data.s._31 = (float)d[0][2];
	data.s._32 = (float)d[1][2];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::getRowMajorStride4(SrF32* d) const
	{
	//we are also row major, so this is a direct copy
	//however we've got to skip every 4th element.
	d[0] = (SrF32)data.s._11;
	d[1] = (SrF32)data.s._12;
	d[2] = (SrF32)data.s._13;

	d[4] = (SrF32)data.s._21;
	d[5] = (SrF32)data.s._22;
	d[6] = (SrF32)data.s._23;

	d[8] = (SrF32)data.s._31;
	d[9] = (SrF32)data.s._32;
	d[10]= (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getRowMajorStride4(SrF32 d[][4]) const
	{
	//we are also row major, so this is a direct copy
	d[0][0] = (SrF32)data.s._11;
	d[0][1] = (SrF32)data.s._12;
	d[0][2] = (SrF32)data.s._13;

	d[1][0] = (SrF32)data.s._21;
	d[1][1] = (SrF32)data.s._22;
	d[1][2] = (SrF32)data.s._23;

	d[2][0] = (SrF32)data.s._31;
	d[2][1] = (SrF32)data.s._32;
	d[2][2] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajorStride4(SrF32* d) const
	{
	//we are column major, so copy transposed.
	//however we've got to skip every 4th element.
	d[0] = (SrF32)data.s._11;
	d[4] = (SrF32)data.s._12;
	d[8] = (SrF32)data.s._13;

	d[1] = (SrF32)data.s._21;
	d[5] = (SrF32)data.s._22;
	d[9] = (SrF32)data.s._23;

	d[2] = (SrF32)data.s._31;
	d[6] = (SrF32)data.s._32;
	d[10]= (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajorStride4(SrF32 d[][4]) const
	{
	//we are column major, so copy transposed.
	d[0][0] = (SrF32)data.s._11;
	d[1][0] = (SrF32)data.s._12;
	d[2][0] = (SrF32)data.s._13;

	d[0][1] = (SrF32)data.s._21;
	d[1][1] = (SrF32)data.s._22;
	d[2][1] = (SrF32)data.s._23;

	d[0][2] = (SrF32)data.s._31;
	d[1][2] = (SrF32)data.s._32;
	d[2][2] = (SrF32)data.s._33;
	}


SR_INLINE void SrMatrix33::setRowMajor(const SrF64*d)
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[1];
	data.s._13 = (float)d[2];

	data.s._21 = (float)d[3];
	data.s._22 = (float)d[4];
	data.s._23 = (float)d[5];

	data.s._31 = (float)d[6];
	data.s._32 = (float)d[7];
	data.s._33 = (float)d[8];
	}


SR_INLINE void SrMatrix33::setRowMajor(const SrF64 d[][3])
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[0][1];
	data.s._13 = (float)d[0][2];

	data.s._21 = (float)d[1][0];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[1][2];

	data.s._31 = (float)d[2][0];
	data.s._32 = (float)d[2][1];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::setColumnMajor(const SrF64*d)
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[3];
	data.s._13 = (float)d[6];

	data.s._21 = (float)d[1];
	data.s._22 = (float)d[4];
	data.s._23 = (float)d[7];

	data.s._31 = (float)d[2];
	data.s._32 = (float)d[5];
	data.s._33 = (float)d[8];
	}


SR_INLINE void SrMatrix33::setColumnMajor(const SrF64 d[][3])
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[1][0];
	data.s._13 = (float)d[2][0];

	data.s._21 = (float)d[0][1];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[2][1];

	data.s._31 = (float)d[0][2];
	data.s._32 = (float)d[1][2];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::getRowMajor(SrF64*d) const
	{
	//we are also row major, so this is a direct copy
	d[0] = (SrF64)data.s._11;
	d[1] = (SrF64)data.s._12;
	d[2] = (SrF64)data.s._13;

	d[3] = (SrF64)data.s._21;
	d[4] = (SrF64)data.s._22;
	d[5] = (SrF64)data.s._23;

	d[6] = (SrF64)data.s._31;
	d[7] = (SrF64)data.s._32;
	d[8] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getRowMajor(SrF64 d[][3]) const
	{
	//we are also row major, so this is a direct copy
	d[0][0] = (SrF64)data.s._11;
	d[0][1] = (SrF64)data.s._12;
	d[0][2] = (SrF64)data.s._13;

	d[1][0] = (SrF64)data.s._21;
	d[1][1] = (SrF64)data.s._22;
	d[1][2] = (SrF64)data.s._23;

	d[2][0] = (SrF64)data.s._31;
	d[2][1] = (SrF64)data.s._32;
	d[2][2] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajor(SrF64*d) const
	{
	//we are column major, so copy transposed.
	d[0] = (SrF64)data.s._11;
	d[3] = (SrF64)data.s._12;
	d[6] = (SrF64)data.s._13;

	d[1] = (SrF64)data.s._21;
	d[4] = (SrF64)data.s._22;
	d[7] = (SrF64)data.s._23;

	d[2] = (SrF64)data.s._31;
	d[5] = (SrF64)data.s._32;
	d[8] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajor(SrF64 d[][3]) const
	{
	//we are column major, so copy transposed.
	d[0][0] = (SrF64)data.s._11;
	d[1][0] = (SrF64)data.s._12;
	d[2][0] = (SrF64)data.s._13;

	d[0][1] = (SrF64)data.s._21;
	d[1][1] = (SrF64)data.s._22;
	d[2][1] = (SrF64)data.s._23;

	d[0][2] = (SrF64)data.s._31;
	d[1][2] = (SrF64)data.s._32;
	d[2][2] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::setRowMajorStride4(const SrF64*d)
	{
	//we are also row major, so this is a direct copy
	//however we've got to skip every 4th element.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[1];
	data.s._13 = (float)d[2];

	data.s._21 = (float)d[4];
	data.s._22 = (float)d[5];
	data.s._23 = (float)d[6];

	data.s._31 = (float)d[8];
	data.s._32 = (float)d[9];
	data.s._33 = (float)d[10];
	}


SR_INLINE void SrMatrix33::setRowMajorStride4(const SrF64 d[][4])
	{
	//we are also row major, so this is a direct copy
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[0][1];
	data.s._13 = (float)d[0][2];

	data.s._21 = (float)d[1][0];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[1][2];

	data.s._31 = (float)d[2][0];
	data.s._32 = (float)d[2][1];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::setColumnMajorStride4(const SrF64*d)
	{
	//we are column major, so copy transposed.
	//however we've got to skip every 4th element.
	data.s._11 = (float)d[0];
	data.s._12 = (float)d[4];
	data.s._13 = (float)d[8];

	data.s._21 = (float)d[1];
	data.s._22 = (float)d[5];
	data.s._23 = (float)d[9];

	data.s._31 = (float)d[2];
	data.s._32 = (float)d[6];
	data.s._33 = (float)d[10];
	}


SR_INLINE void SrMatrix33::setColumnMajorStride4(const SrF64 d[][4])
	{
	//we are column major, so copy transposed.
	data.s._11 = (float)d[0][0];
	data.s._12 = (float)d[1][0];
	data.s._13 = (float)d[2][0];

	data.s._21 = (float)d[0][1];
	data.s._22 = (float)d[1][1];
	data.s._23 = (float)d[2][1];

	data.s._31 = (float)d[0][2];
	data.s._32 = (float)d[1][2];
	data.s._33 = (float)d[2][2];
	}


SR_INLINE void SrMatrix33::getRowMajorStride4(SrF64*d) const
	{
	//we are also row major, so this is a direct copy
	//however we've got to skip every 4th element.
	d[0] = (SrF64)data.s._11;
	d[1] = (SrF64)data.s._12;
	d[2] = (SrF64)data.s._13;

	d[4] = (SrF64)data.s._21;
	d[5] = (SrF64)data.s._22;
	d[6] = (SrF64)data.s._23;

	d[8] = (SrF64)data.s._31;
	d[9] = (SrF64)data.s._32;
	d[10]= (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getRowMajorStride4(SrF64 d[][4]) const
	{
	//we are also row major, so this is a direct copy
	d[0][0] = (SrF64)data.s._11;
	d[0][1] = (SrF64)data.s._12;
	d[0][2] = (SrF64)data.s._13;

	d[1][0] = (SrF64)data.s._21;
	d[1][1] = (SrF64)data.s._22;
	d[1][2] = (SrF64)data.s._23;

	d[2][0] = (SrF64)data.s._31;
	d[2][1] = (SrF64)data.s._32;
	d[2][2] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajorStride4(SrF64*d) const

	{
	//we are column major, so copy transposed.
	//however we've got to skip every 4th element.
	d[0] = (SrF64)data.s._11;
	d[4] = (SrF64)data.s._12;
	d[8] = (SrF64)data.s._13;

	d[1] = (SrF64)data.s._21;
	d[5] = (SrF64)data.s._22;
	d[9] = (SrF64)data.s._23;

	d[2] = (SrF64)data.s._31;
	d[6] = (SrF64)data.s._32;
	d[10]= (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::getColumnMajorStride4(SrF64 d[][4]) const
	{
	//we are column major, so copy transposed.
	d[0][0] = (SrF64)data.s._11;
	d[1][0] = (SrF64)data.s._12;
	d[2][0] = (SrF64)data.s._13;

	d[0][1] = (SrF64)data.s._21;
	d[1][1] = (SrF64)data.s._22;
	d[2][1] = (SrF64)data.s._23;

	d[0][2] = (SrF64)data.s._31;
	d[1][2] = (SrF64)data.s._32;
	d[2][2] = (SrF64)data.s._33;
	}


SR_INLINE void SrMatrix33::setRow(int row, const SrVector3 & v)
	{
#ifndef TRANSPOSED_MAT33
	data.m[row][0] = v.x;
	data.m[row][1] = v.y;
	data.m[row][2] = v.z;
#else
	data.m[0][row] = v.x;
	data.m[1][row] = v.y;
	data.m[2][row] = v.z;
#endif
	}


SR_INLINE void SrMatrix33::setColumn(int col, const SrVector3 & v)
	{
#ifndef TRANSPOSED_MAT33
	data.m[0][col] = v.x;
	data.m[1][col] = v.y;
	data.m[2][col] = v.z;
#else
	data.m[col][0] = v.x;
	data.m[col][1] = v.y;
	data.m[col][2] = v.z;
#endif
	}


SR_INLINE void SrMatrix33::getRow(int row, SrVector3 & v) const
	{
#ifndef TRANSPOSED_MAT33
	v.x = data.m[row][0];
	v.y = data.m[row][1];
	v.z = data.m[row][2];
#else
	v.x = data.m[0][row];
	v.y = data.m[1][row];
	v.z = data.m[2][row];
#endif
	}


SR_INLINE void SrMatrix33::getColumn(int col, SrVector3 & v) const
	{
#ifndef TRANSPOSED_MAT33
	v.x = data.m[0][col];
	v.y = data.m[1][col];
	v.z = data.m[2][col];
#else
	v.x = data.m[col][0];
	v.y = data.m[col][1];
	v.z = data.m[col][2];
#endif
	}


SR_INLINE SrVector3 SrMatrix33::getRow(int row) const
{
#ifndef TRANSPOSED_MAT33
	return SrVector3(data.m[row][0],data.m[row][1],data.m[row][2]);
#else
	return SrVector3(data.m[0][row],data.m[1][row],data.m[2][row]);
#endif
}

SR_INLINE SrVector3 SrMatrix33::getColumn(int col) const
{
#ifndef TRANSPOSED_MAT33
	return SrVector3(data.m[0][col],data.m[1][col],data.m[2][col]);
#else
	return SrVector3(data.m[col][0],data.m[col][1],data.m[col][2]);
#endif
}

SR_INLINE float & SrMatrix33::operator()(int row, int col)
	{
#ifndef TRANSPOSED_MAT33
	return data.m[row][col];
#else
	return data.m[col][row];
#endif
	}


SR_INLINE const float & SrMatrix33::operator() (int row, int col) const
	{
#ifndef TRANSPOSED_MAT33
	return data.m[row][col];
#else
	return data.m[col][row];
#endif
	}

//const methods


SR_INLINE bool SrMatrix33::isIdentity() const
	{
	if(data.s._11 != 1.0f)		return false;
	if(data.s._12 != 0.0f)		return false;
	if(data.s._13 != 0.0f)		return false;

	if(data.s._21 != 0.0f)		return false;
	if(data.s._22 != 1.0f)		return false;
	if(data.s._23 != 0.0f)		return false;

	if(data.s._31 != 0.0f)		return false;
	if(data.s._32 != 0.0f)		return false;
	if(data.s._33 != 1.0f)		return false;

	return true;
	}


SR_INLINE bool SrMatrix33::isZero() const
	{
	if(data.s._11 != 0.0f)		return false;
	if(data.s._12 != 0.0f)		return false;
	if(data.s._13 != 0.0f)		return false;

	if(data.s._21 != 0.0f)		return false;
	if(data.s._22 != 0.0f)		return false;
	if(data.s._23 != 0.0f)		return false;

	if(data.s._31 != 0.0f)		return false;
	if(data.s._32 != 0.0f)		return false;
	if(data.s._33 != 0.0f)		return false;

	return true;
	}


SR_INLINE bool SrMatrix33::isFinite() const
	{
	return SrMath::isFinite(data.s._11)
	&& SrMath::isFinite(data.s._12)
	&& SrMath::isFinite(data.s._13)

	&& SrMath::isFinite(data.s._21)
	&& SrMath::isFinite(data.s._22)
	&& SrMath::isFinite(data.s._23)

	&& SrMath::isFinite(data.s._31)
	&& SrMath::isFinite(data.s._32)
	&& SrMath::isFinite(data.s._33);
	}



SR_INLINE void SrMatrix33::zero()
	{
	data.s._11 = float(0.0);
	data.s._12 = float(0.0);
	data.s._13 = float(0.0);

	data.s._21 = float(0.0);
	data.s._22 = float(0.0);
	data.s._23 = float(0.0);

	data.s._31 = float(0.0);
	data.s._32 = float(0.0);
	data.s._33 = float(0.0);
	}


SR_INLINE void SrMatrix33::id()
	{
	data.s._11 = float(1.0);
	data.s._12 = float(0.0);
	data.s._13 = float(0.0);

	data.s._21 = float(0.0);
	data.s._22 = float(1.0);
	data.s._23 = float(0.0);

	data.s._31 = float(0.0);
	data.s._32 = float(0.0);
	data.s._33 = float(1.0);
	}


SR_INLINE void SrMatrix33::setNegative()
	{
	data.s._11 = -data.s._11;
	data.s._12 = -data.s._12;
	data.s._13 = -data.s._13;

	data.s._21 = -data.s._21;
	data.s._22 = -data.s._22;
	data.s._23 = -data.s._23;

	data.s._31 = -data.s._31;
	data.s._32 = -data.s._32;
	data.s._33 = -data.s._33;
	}


SR_INLINE void SrMatrix33::diagonal(const SrVector3 &v)
	{
	data.s._11 = v.x;
	data.s._12 = float(0.0);
	data.s._13 = float(0.0);

	data.s._21 = float(0.0);
	data.s._22 = v.y;
	data.s._23 = float(0.0);

	data.s._31 = float(0.0);
	data.s._32 = float(0.0);
	data.s._33 = v.z;
	}


SR_INLINE void SrMatrix33::star(const SrVector3 &v)
	{
	data.s._11 = float(0.0);	data.s._12 =-v.z;	data.s._13 = v.y;
	data.s._21 = v.z;	data.s._22 = float(0.0);	data.s._23 =-v.x;
	data.s._31 =-v.y;	data.s._32 = v.x;	data.s._33 = float(0.0);
	}


SR_INLINE void SrMatrix33::fromQuat(const SrQuaternion & q)
	{
	const float w = q.w;
	const float x = q.x;
	const float y = q.y;
	const float z = q.z;

	data.s._11 = float(1.0) - y*y*float(2.0) - z*z*float(2.0);
	data.s._12 = x*y*float(2.0) - w*z*float(2.0);	
	data.s._13 = x*z*float(2.0) + w*y*float(2.0);	

	data.s._21 = x*y*float(2.0) + w*z*float(2.0);	
	data.s._22 = float(1.0) - x*x*float(2.0) - z*z*float(2.0);	
	data.s._23 = y*z*float(2.0) - w*x*float(2.0);	
	
	data.s._31 = x*z*float(2.0) - w*y*float(2.0);	
	data.s._32 = y*z*float(2.0) + w*x*float(2.0);	
	data.s._33 = float(1.0) - x*x*float(2.0) - y*y*float(2.0);	
	}


SR_INLINE void SrMatrix33::toQuat(SrQuaternion & q) const					// set the SrQuaternion from a rotation matrix
	{
    float tr, s;
    tr = data.s._11 + data.s._22 + data.s._33;
    if(tr >= 0)
		{
		s = (float)SrMath::sqrt(tr +1);
		q.w = float(0.5) * s;
		s = float(0.5) / s;
		q.x = ((*this)(2,1) - (*this)(1,2)) * s;
		q.y = ((*this)(0,2) - (*this)(2,0)) * s;
		q.z = ((*this)(1,0) - (*this)(0,1)) * s;
		}
    else
		{
		int i = 0; 
		if (data.s._22 > data.s._11)
			i = 1; 
		if(data.s._33 > (*this)(i,i))
			i=2; 
		switch (i)
			{
			case 0:
				s = (float)SrMath::sqrt((data.s._11 - (data.s._22 + data.s._33)) + 1);
				q.x = float(0.5) * s;
				s = float(0.5) / s;
				q.y = ((*this)(0,1) + (*this)(1,0)) * s; 
				q.z = ((*this)(2,0) + (*this)(0,2)) * s;
				q.w = ((*this)(2,1) - (*this)(1,2)) * s;
				break;
			case 1:
				s = (float)SrMath::sqrt((data.s._22 - (data.s._33 + data.s._11)) + 1);
				q.y = float(0.5) * s;
				s = float(0.5) / s;
				q.z = ((*this)(1,2) + (*this)(2,1)) * s;
				q.x = ((*this)(0,1) + (*this)(1,0)) * s;
				q.w = ((*this)(0,2) - (*this)(2,0)) * s;
				break;
			case 2:
				s = (float)SrMath::sqrt((data.s._33 - (data.s._11 + data.s._22)) + 1);
				q.z = float(0.5) * s;
				s = float(0.5) / s;
				q.x = ((*this)(2,0) + (*this)(0,2)) * s;
				q.y = ((*this)(1,2) + (*this)(2,1)) * s;
				q.w = ((*this)(1,0) - (*this)(0,1)) * s;
			}
		}
	}

SR_INLINE void SrMatrix33::setTransposed(const SrMatrix33& other)
	{
	//gotta special case in-place case
	if (this != &other)
		{
		data.s._11 = other.data.s._11;
		data.s._12 = other.data.s._21;
		data.s._13 = other.data.s._31;

		data.s._21 = other.data.s._12;
		data.s._22 = other.data.s._22;
		data.s._23 = other.data.s._32;

		data.s._31 = other.data.s._13;
		data.s._32 = other.data.s._23;
		data.s._33 = other.data.s._33;
		}
	else
		{
		float tx, ty, tz;
		tx = data.s._21;	data.s._21 = other.data.s._12;	data.s._12 = tx;
		ty = data.s._31;	data.s._31 = other.data.s._13;	data.s._13 = ty;
		tz = data.s._32;	data.s._32 = other.data.s._23;	data.s._23 = tz;
		}
	}


SR_INLINE void SrMatrix33::setTransposed()
	{
		float tempValue = data.s._21;data.s._21 = data.s._12; data.s._12 = tempValue;
		tempValue = data.s._23;data.s._23 = data.s._32; data.s._32 = tempValue;
		tempValue = data.s._13;data.s._13 = data.s._31; data.s._31 = tempValue;
	}


SR_INLINE void SrMatrix33::multiplyDiagonal(const SrVector3 &d)
	{
	data.s._11 *= d.x;
	data.s._12 *= d.y;
	data.s._13 *= d.z;

	data.s._21 *= d.x;
	data.s._22 *= d.y;
	data.s._23 *= d.z;

	data.s._31 *= d.x;
	data.s._32 *= d.y;
	data.s._33 *= d.z;
	}


SR_INLINE void SrMatrix33::multiplyDiagonalTranspose(const SrVector3 &d)
	{
		float temp;
		data.s._11 = data.s._11 * d.x;
		data.s._22 = data.s._22 * d.y;
		data.s._33 = data.s._33 * d.z;

		temp = data.s._21 * d.y;
		data.s._21 = data.s._12 * d.x;
		data.s._12 = temp;

		temp = data.s._31 * d.z;
		data.s._31 = data.s._13 * d.x;
		data.s._13 = temp;
		
		temp = data.s._32 * d.z;
		data.s._32 = data.s._23 * d.y;
		data.s._23 = temp;
	}


SR_INLINE void SrMatrix33::multiplyDiagonal(const SrVector3 &d, SrMatrix33& dst) const
	{
	dst.data.s._11 = data.s._11 * d.x;
	dst.data.s._12 = data.s._12 * d.y;
	dst.data.s._13 = data.s._13 * d.z;

	dst.data.s._21 = data.s._21 * d.x;
	dst.data.s._22 = data.s._22 * d.y;
	dst.data.s._23 = data.s._23 * d.z;

	dst.data.s._31 = data.s._31 * d.x;
	dst.data.s._32 = data.s._32 * d.y;
	dst.data.s._33 = data.s._33 * d.z;
	}


SR_INLINE void SrMatrix33::multiplyDiagonalTranspose(const SrVector3 &d, SrMatrix33& dst) const
	{
	dst.data.s._11 = data.s._11 * d.x;
	dst.data.s._12 = data.s._21 * d.y;
	dst.data.s._13 = data.s._31 * d.z;

	dst.data.s._21 = data.s._12 * d.x;
	dst.data.s._22 = data.s._22 * d.y;
	dst.data.s._23 = data.s._32 * d.z;

	dst.data.s._31 = data.s._13 * d.x;
	dst.data.s._32 = data.s._23 * d.y;
	dst.data.s._33 = data.s._33 * d.z;
	}


SR_INLINE void SrMatrix33::multiply(const SrVector3 &src, SrVector3 &dst) const
	{
	float x,y,z;	//so it works if src == dst
	x = data.s._11 * src.x + data.s._12 * src.y + data.s._13 * src.z;
	y = data.s._21 * src.x + data.s._22 * src.y + data.s._23 * src.z;
	z = data.s._31 * src.x + data.s._32 * src.y + data.s._33 * src.z;

	dst.x = x;
	dst.y = y;
	dst.z = z;	
	}


SR_INLINE void SrMatrix33::multiplyByTranspose(const SrVector3 &src, SrVector3 &dst) const
	{
	float x,y,z;	//so it works if src == dst
	x = data.s._11 * src.x + data.s._21 * src.y + data.s._31 * src.z;
	y = data.s._12 * src.x + data.s._22 * src.y + data.s._32 * src.z;
	z = data.s._13 * src.x + data.s._23 * src.y + data.s._33 * src.z;

	dst.x = x;
	dst.y = y;
	dst.z = z;	
	}


SR_INLINE void SrMatrix33::add(const SrMatrix33 & a, const SrMatrix33 & b)
	{
	data.s._11 = a.data.s._11 + b.data.s._11;
	data.s._12 = a.data.s._12 + b.data.s._12;
	data.s._13 = a.data.s._13 + b.data.s._13;

	data.s._21 = a.data.s._21 + b.data.s._21;
	data.s._22 = a.data.s._22 + b.data.s._22;
	data.s._23 = a.data.s._23 + b.data.s._23;

	data.s._31 = a.data.s._31 + b.data.s._31;
	data.s._32 = a.data.s._32 + b.data.s._32;
	data.s._33 = a.data.s._33 + b.data.s._33;
	}


SR_INLINE void SrMatrix33::subtract(const SrMatrix33 &a, const SrMatrix33 &b)
	{
	data.s._11 = a.data.s._11 - b.data.s._11;
	data.s._12 = a.data.s._12 - b.data.s._12;
	data.s._13 = a.data.s._13 - b.data.s._13;

	data.s._21 = a.data.s._21 - b.data.s._21;
	data.s._22 = a.data.s._22 - b.data.s._22;
	data.s._23 = a.data.s._23 - b.data.s._23;

	data.s._31 = a.data.s._31 - b.data.s._31;
	data.s._32 = a.data.s._32 - b.data.s._32;
	data.s._33 = a.data.s._33 - b.data.s._33;
	}


SR_INLINE void SrMatrix33::multiply(float d,  const SrMatrix33 & a)
	{
	data.s._11 = a.data.s._11 * d;
	data.s._12 = a.data.s._12 * d;
	data.s._13 = a.data.s._13 * d;

	data.s._21 = a.data.s._21 * d;
	data.s._22 = a.data.s._22 * d;
	data.s._23 = a.data.s._23 * d;

	data.s._31 = a.data.s._31 * d;
	data.s._32 = a.data.s._32 * d;
	data.s._33 = a.data.s._33 * d;
	}


SR_INLINE void SrMatrix33::multiply(const SrMatrix33& left, const SrMatrix33& right)
	{
	float a,b,c, d,e,f, g,h,i;
	//note: temps needed so that x.multiply(x,y) works OK.
	a =left.data.s._11 * right.data.s._11 +left.data.s._12 * right.data.s._21 +left.data.s._13 * right.data.s._31;
	b =left.data.s._11 * right.data.s._12 +left.data.s._12 * right.data.s._22 +left.data.s._13 * right.data.s._32;
	c =left.data.s._11 * right.data.s._13 +left.data.s._12 * right.data.s._23 +left.data.s._13 * right.data.s._33;

	d =left.data.s._21 * right.data.s._11 +left.data.s._22 * right.data.s._21 +left.data.s._23 * right.data.s._31;
	e =left.data.s._21 * right.data.s._12 +left.data.s._22 * right.data.s._22 +left.data.s._23 * right.data.s._32;
	f =left.data.s._21 * right.data.s._13 +left.data.s._22 * right.data.s._23 +left.data.s._23 * right.data.s._33;

	g =left.data.s._31 * right.data.s._11 +left.data.s._32 * right.data.s._21 +left.data.s._33 * right.data.s._31;
	h =left.data.s._31 * right.data.s._12 +left.data.s._32 * right.data.s._22 +left.data.s._33 * right.data.s._32;
	i =left.data.s._31 * right.data.s._13 +left.data.s._32 * right.data.s._23 +left.data.s._33 * right.data.s._33;


	data.s._11 = a;
	data.s._12 = b;
	data.s._13 = c;

	data.s._21 = d;
	data.s._22 = e;
	data.s._23 = f;

	data.s._31 = g;
	data.s._32 = h;
	data.s._33 = i;
	}


SR_INLINE void SrMatrix33::multiplyTransposeLeft(const SrMatrix33& left, const SrMatrix33& right)
	{
	float a,b,c, d,e,f, g,h,i;
	//note: temps needed so that x.multiply(x,y) works OK.
	a =left.data.s._11 * right.data.s._11 +left.data.s._21 * right.data.s._21 +left.data.s._31 * right.data.s._31;
	b =left.data.s._11 * right.data.s._12 +left.data.s._21 * right.data.s._22 +left.data.s._31 * right.data.s._32;
	c =left.data.s._11 * right.data.s._13 +left.data.s._21 * right.data.s._23 +left.data.s._31 * right.data.s._33;

	d =left.data.s._12 * right.data.s._11 +left.data.s._22 * right.data.s._21 +left.data.s._32 * right.data.s._31;
	e =left.data.s._12 * right.data.s._12 +left.data.s._22 * right.data.s._22 +left.data.s._32 * right.data.s._32;
	f =left.data.s._12 * right.data.s._13 +left.data.s._22 * right.data.s._23 +left.data.s._32 * right.data.s._33;

	g =left.data.s._13 * right.data.s._11 +left.data.s._23 * right.data.s._21 +left.data.s._33 * right.data.s._31;
	h =left.data.s._13 * right.data.s._12 +left.data.s._23 * right.data.s._22 +left.data.s._33 * right.data.s._32;
	i =left.data.s._13 * right.data.s._13 +left.data.s._23 * right.data.s._23 +left.data.s._33 * right.data.s._33;

	data.s._11 = a;
	data.s._12 = b;
	data.s._13 = c;

	data.s._21 = d;
	data.s._22 = e;
	data.s._23 = f;

	data.s._31 = g;
	data.s._32 = h;
	data.s._33 = i;
	}


SR_INLINE void SrMatrix33::multiplyTransposeRight(const SrMatrix33& left, const SrMatrix33& right)
	{
	float a,b,c, d,e,f, g,h,i;
	//note: temps needed so that x.multiply(x,y) works OK.
	a =left.data.s._11 * right.data.s._11 +left.data.s._12 * right.data.s._12 +left.data.s._13 * right.data.s._13;
	b =left.data.s._11 * right.data.s._21 +left.data.s._12 * right.data.s._22 +left.data.s._13 * right.data.s._23;
	c =left.data.s._11 * right.data.s._31 +left.data.s._12 * right.data.s._32 +left.data.s._13 * right.data.s._33;

	d =left.data.s._21 * right.data.s._11 +left.data.s._22 * right.data.s._12 +left.data.s._23 * right.data.s._13;
	e =left.data.s._21 * right.data.s._21 +left.data.s._22 * right.data.s._22 +left.data.s._23 * right.data.s._23;
	f =left.data.s._21 * right.data.s._31 +left.data.s._22 * right.data.s._32 +left.data.s._23 * right.data.s._33;

	g =left.data.s._31 * right.data.s._11 +left.data.s._32 * right.data.s._12 +left.data.s._33 * right.data.s._13;
	h =left.data.s._31 * right.data.s._21 +left.data.s._32 * right.data.s._22 +left.data.s._33 * right.data.s._23;
	i =left.data.s._31 * right.data.s._31 +left.data.s._32 * right.data.s._32 +left.data.s._33 * right.data.s._33;

	data.s._11 = a;
	data.s._12 = b;
	data.s._13 = c;

	data.s._21 = d;
	data.s._22 = e;
	data.s._23 = f;

	data.s._31 = g;
	data.s._32 = h;
	data.s._33 = i;
	}


SR_INLINE void SrMatrix33::multiplyTransposeRight(const SrVector3 &left, const SrVector3 &right)
	{
	data.s._11 = left.x * right.x;
	data.s._12 = left.x * right.y;
	data.s._13 = left.x * right.z;

	data.s._21 = left.y * right.x;
	data.s._22 = left.y * right.y;
	data.s._23 = left.y * right.z;

	data.s._31 = left.z * right.x;
	data.s._32 = left.z * right.y;
	data.s._33 = left.z * right.z;
	}

SR_INLINE void SrMatrix33::rotX(float angle)
	{
	float Cos = cosf(angle);
	float Sin = sinf(angle);
	id();
	data.m[1][1] = data.m[2][2] = Cos;
	data.m[1][2] = -Sin;
	data.m[2][1] = Sin;
	}

SR_INLINE void SrMatrix33::rotY(float angle)
	{
	float Cos = cosf(angle);
	float Sin = sinf(angle);
	id();
	data.m[0][0] = data.m[2][2] = Cos;
	data.m[0][2] = Sin;
	data.m[2][0] = -Sin;
	}

SR_INLINE void SrMatrix33::rotZ(float angle)
	{
	float Cos = cosf(angle);
	float Sin = sinf(angle);
	id();
	data.m[0][0] = data.m[1][1] = Cos;
	data.m[0][1] = -Sin;
	data.m[1][0] = Sin;
	}

SR_INLINE SrVector3  SrMatrix33::operator%(const SrVector3 & src) const
	{
	SrVector3 dest;
	this->multiplyByTranspose(src, dest);
	return dest;
	}


SR_INLINE SrVector3  SrMatrix33::operator*(const SrVector3 & src) const
	{
	SrVector3 dest;
	this->multiply(src, dest);
	return dest;
	}


SR_INLINE const SrMatrix33 &SrMatrix33::operator +=(const SrMatrix33 &d)
	{
	data.s._11 += d.data.s._11;
	data.s._12 += d.data.s._12;
	data.s._13 += d.data.s._13;

	data.s._21 += d.data.s._21;
	data.s._22 += d.data.s._22;
	data.s._23 += d.data.s._23;

	data.s._31 += d.data.s._31;
	data.s._32 += d.data.s._32;
	data.s._33 += d.data.s._33;
	return *this;
	}


SR_INLINE const SrMatrix33 &SrMatrix33::operator -=(const SrMatrix33 &d)
	{
	data.s._11 -= d.data.s._11;
	data.s._12 -= d.data.s._12;
	data.s._13 -= d.data.s._13;

	data.s._21 -= d.data.s._21;
	data.s._22 -= d.data.s._22;
	data.s._23 -= d.data.s._23;

	data.s._31 -= d.data.s._31;
	data.s._32 -= d.data.s._32;
	data.s._33 -= d.data.s._33;
	return *this;
	}


SR_INLINE const SrMatrix33 &SrMatrix33::operator *=(float f)
	{
	data.s._11 *= f;
	data.s._12 *= f;
	data.s._13 *= f;

	data.s._21 *= f;
	data.s._22 *= f;
	data.s._23 *= f;

	data.s._31 *= f;
	data.s._32 *= f;
	data.s._33 *= f;
	return *this;
	}


SR_INLINE const SrMatrix33 &SrMatrix33::operator /=(float x)
	{
	float f = float(1.0) / x;
	data.s._11 *= f;
	data.s._12 *= f;
	data.s._13 *= f;

	data.s._21 *= f;
	data.s._22 *= f;
	data.s._23 *= f;

	data.s._31 *= f;
	data.s._32 *= f;
	data.s._33 *= f;
	return *this;
	}


SR_INLINE float SrMatrix33::determinant() const
	{
	return  data.s._11*data.s._22*data.s._33 + data.s._12*data.s._23*data.s._31 + data.s._13*data.s._21*data.s._32 
		  - data.s._13*data.s._22*data.s._31 - data.s._12*data.s._21*data.s._33 - data.s._11*data.s._23*data.s._32;
	}


SR_INLINE bool SrMatrix33::getInverse(SrMatrix33& dest) const
	{
	float b00,b01,b02,b10,b11,b12,b20,b21,b22;

	b00 = data.s._22*data.s._33-data.s._23*data.s._32;	b01 = data.s._13*data.s._32-data.s._12*data.s._33;	b02 = data.s._12*data.s._23-data.s._13*data.s._22;
	b10 = data.s._23*data.s._31-data.s._21*data.s._33;	b11 = data.s._11*data.s._33-data.s._13*data.s._31;	b12 = data.s._13*data.s._21-data.s._11*data.s._23;
	b20 = data.s._21*data.s._32-data.s._22*data.s._31;	b21 = data.s._12*data.s._31-data.s._11*data.s._32;	b22 = data.s._11*data.s._22-data.s._12*data.s._21;
	


	/*
	compute determinant: 
	float d =   a00*a11*a22 + a01*a12*a20 + a02*a10*a21	- a02*a11*a20 - a01*a10*a22 - a00*a12*a21;
				0				1			2			3				4			5

	this is a subset of the multiplies done above:

	float d = b00*a00				+		b01*a10						 + b02 * a20;
	float d = (a11*a22-a12*a21)*a00 +		(a02*a21-a01*a22)*a10		 + (a01*a12-a02*a11) * a20;

	float d = a11*a22*a00-a12*a21*a00 +		a02*a21*a10-a01*a22*a10		 + a01*a12*a20-a02*a11*a20;
			0			5					2			4					1			3
	*/

	float d = b00*data.s._11		+		b01*data.s._21				 + b02 * data.s._31;
	
	if (d == float(0.0))		//singular?
		{
		dest.id();
		return false;
		}
	
	d = float(1.0)/d;

	//only do assignment at the end, in case dest == this:


	dest.data.s._11 = b00*d; dest.data.s._12 = b01*d; dest.data.s._13 = b02*d;
	dest.data.s._21 = b10*d; dest.data.s._22 = b11*d; dest.data.s._23 = b12*d;
	dest.data.s._31 = b20*d; dest.data.s._32 = b21*d; dest.data.s._33 = b22*d;

	return true;
	}


SR_INLINE SrMatrix33&	SrMatrix33::operator*= (const SrMatrix33& mat)
	{
	this->multiply(*this, mat);
	return *this;
	}


SR_INLINE SrMatrix33	SrMatrix33::operator-  (const SrMatrix33& mat)	const
	{
	SrMatrix33 temp;
	temp.subtract(*this, mat);
	return temp;
	}


SR_INLINE SrMatrix33	SrMatrix33::operator+  (const SrMatrix33& mat)	const
	{
	SrMatrix33 temp;
	temp.add(*this, mat);
	return temp;
	}


SR_INLINE SrMatrix33	SrMatrix33::operator*  (const SrMatrix33& mat)	const
	{
	SrMatrix33 temp;
	temp.multiply(*this, mat);
	return temp;
	}


SR_INLINE SrMatrix33	SrMatrix33::operator*  (float s)			const
	{
	SrMatrix33 temp;
	temp.multiply(s, *this);
	return temp;
	}

SR_INLINE SrQuaternion::SrQuaternion(const class SrMatrix33 &m)
{
	m.toQuat(*this);
}


/** @} */
#endif

