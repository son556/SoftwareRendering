#include "pch.h"
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(const Matrix4x4& ref) {
	*this = ref;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& ref) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = ref.m[i][j];
	return (*this);
}

float& Matrix4x4::operator[](int idx) {
	return (this->m[idx / 4][idx % 4]);
}

Matrix4x4	Matrix4x4::operator*(Matrix4x4 const& m) {
	Matrix4x4	ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				ret.m[i][j] += this->m[i][k] * m.m[k][j];
			}
		}
	}
	return (ret);
}

Vector4	Matrix4x4::operator*(Vector4 const& v) {
	Vector4	ret;

	ret.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3] * v.w;
	ret.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3] * v.w;
	ret.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3] * v.w;
	ret.w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3] * v.w;
	return (ret);
}

Matrix4x4 Matrix4x4::Trnaspose()
{
	Matrix4x4 res;

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
			res.m[j][i] = this->m[i][j];
	}
	return res;
}

Matrix4x4 Matrix4x4::inverse()
{
    float inv[4][4];
    Matrix4x4 invOut;

    inv[0][0] = this->m[1][1] * this->m[2][2] * this->m[3][3]
        - this->m[1][1] * this->m[2][3] * this->m[3][2]
        - this->m[2][1] * this->m[1][2] * this->m[3][3]
        + this->m[2][1] * this->m[1][3] * this->m[3][2]
        + this->m[3][1] * this->m[1][2] * this->m[2][3]
        - this->m[3][1] * this->m[1][3] * this->m[2][2];

    inv[1][0] = -this->m[1][0] * this->m[2][2] * this->m[3][3]
        + this->m[1][0] * this->m[2][3] * this->m[3][2]
        + this->m[2][0] * this->m[1][2] * this->m[3][3]
        - this->m[2][0] * this->m[1][3] * this->m[3][2]
        - this->m[3][0] * this->m[1][2] * this->m[2][3]
        + this->m[3][0] * this->m[1][3] * this->m[2][2];

    inv[2][0] = this->m[1][0] * this->m[2][1] * this->m[3][3]
        - this->m[1][0] * this->m[2][3] * this->m[3][1]
        - this->m[2][0] * this->m[1][1] * this->m[3][3]
        + this->m[2][0] * this->m[1][3] * this->m[3][1]
        + this->m[3][0] * this->m[1][1] * this->m[2][3]
        - this->m[3][0] * this->m[1][3] * this->m[2][1];

    inv[3][0] = -this->m[1][0] * this->m[2][1] * this->m[3][2]
        + this->m[1][0] * this->m[2][2] * this->m[3][1]
        + this->m[2][0] * this->m[1][1] * this->m[3][2]
        - this->m[2][0] * this->m[1][2] * this->m[3][1]
        - this->m[3][0] * this->m[1][1] * this->m[2][2]
        + this->m[3][0] * this->m[1][2] * this->m[2][1];


    inv[0][1] = -this->m[0][1] * this->m[2][2] * this->m[3][3]
        + this->m[0][1] * this->m[2][3] * this->m[3][2]
        + this->m[2][1] * this->m[0][2] * this->m[3][3]
        - this->m[2][1] * this->m[0][3] * this->m[3][2]
        - this->m[3][1] * this->m[0][2] * this->m[2][3]
        + this->m[3][1] * this->m[0][3] * this->m[2][2];

    inv[1][1] = this->m[0][0] * this->m[2][2] * this->m[3][3]
        - this->m[0][0] * this->m[2][3] * this->m[3][2]
        - this->m[2][0] * this->m[0][2] * this->m[3][3]
        + this->m[2][0] * this->m[0][3] * this->m[3][2]
        + this->m[3][0] * this->m[0][2] * this->m[2][3]
        - this->m[3][0] * this->m[0][3] * this->m[2][2];

    inv[2][1] = -this->m[0][0] * this->m[2][1] * this->m[3][3]
        + this->m[0][0] * this->m[2][3] * this->m[3][1]
        + this->m[2][0] * this->m[0][1] * this->m[3][3]
        - this->m[2][0] * this->m[0][3] * this->m[3][1]
        - this->m[3][0] * this->m[0][1] * this->m[2][3]
        + this->m[3][0] * this->m[0][3] * this->m[2][1];

    inv[3][1] = this->m[0][0] * this->m[2][1] * this->m[3][2]
        - this->m[0][0] * this->m[2][2] * this->m[3][1]
        - this->m[2][0] * this->m[0][1] * this->m[3][2]
        + this->m[2][0] * this->m[0][2] * this->m[3][1]
        + this->m[3][0] * this->m[0][1] * this->m[2][2]
        - this->m[3][0] * this->m[0][2] * this->m[2][1];


    inv[0][2] = this->m[0][1] * this->m[1][2] * this->m[3][3]
        - this->m[0][1] * this->m[1][3] * this->m[3][2]
        - this->m[1][1] * this->m[0][2] * this->m[3][3]
        + this->m[1][1] * this->m[0][3] * this->m[3][2]
        + this->m[3][1] * this->m[0][2] * this->m[1][3]
        - this->m[3][1] * this->m[0][3] * this->m[1][2];

    inv[1][2] = -this->m[0][0] * this->m[1][2] * this->m[3][3]
        + this->m[0][0] * this->m[1][3] * this->m[3][2]
        + this->m[1][0] * this->m[0][2] * this->m[3][3]
        - this->m[1][0] * this->m[0][3] * this->m[3][2]
        - this->m[3][0] * this->m[0][2] * this->m[1][3]
        + this->m[3][0] * this->m[0][3] * this->m[1][2];

    inv[2][2] = this->m[0][0] * this->m[1][1] * this->m[3][3]
        - this->m[0][0] * this->m[1][3] * this->m[3][1]
        - this->m[1][0] * this->m[0][1] * this->m[3][3]
        + this->m[1][0] * this->m[0][3] * this->m[3][1]
        + this->m[3][0] * this->m[0][1] * this->m[1][3]
        - this->m[3][0] * this->m[0][3] * this->m[1][1];

    inv[3][2] = -this->m[0][0] * this->m[1][1] * this->m[3][2]
        + this->m[0][0] * this->m[1][2] * this->m[3][1]
        + this->m[1][0] * this->m[0][1] * this->m[3][2]
        - this->m[1][0] * this->m[0][2] * this->m[3][1]
        - this->m[3][0] * this->m[0][1] * this->m[1][2]
        + this->m[3][0] * this->m[0][2] * this->m[1][1];


    inv[0][3] = -this->m[0][1] * this->m[1][2] * this->m[2][3]
        + this->m[0][1] * this->m[1][3] * this->m[2][2]
        + this->m[1][1] * this->m[0][2] * this->m[2][3]
        - this->m[1][1] * this->m[0][3] * this->m[2][2]
        - this->m[2][1] * this->m[0][2] * this->m[1][3]
        + this->m[2][1] * this->m[0][3] * this->m[1][2];

    inv[1][3] = this->m[0][0] * this->m[1][2] * this->m[2][3]
        - this->m[0][0] * this->m[1][3] * this->m[2][2]
        - this->m[1][0] * this->m[0][2] * this->m[2][3]
        + this->m[1][0] * this->m[0][3] * this->m[2][2]
        + this->m[2][0] * this->m[0][2] * this->m[1][3]
        - this->m[2][0] * this->m[0][3] * this->m[1][2];

    inv[2][3] = -this->m[0][0] * this->m[1][1] * this->m[2][3]
        + this->m[0][0] * this->m[1][3] * this->m[2][1]
        + this->m[1][0] * this->m[0][1] * this->m[2][3]
        - this->m[1][0] * this->m[0][3] * this->m[2][1]
        - this->m[2][0] * this->m[0][1] * this->m[1][3]
        + this->m[2][0] * this->m[0][3] * this->m[1][1];

    inv[3][3] = this->m[0][0] * this->m[1][1] * this->m[2][2]
        - this->m[0][0] * this->m[1][2] * this->m[2][1]
        - this->m[1][0] * this->m[0][1] * this->m[2][2]
        + this->m[1][0] * this->m[0][2] * this->m[2][1]
        + this->m[2][0] * this->m[0][1] * this->m[1][2]
        - this->m[2][0] * this->m[0][2] * this->m[1][1];

    // 행렬식 계산 (첫 행과 여인수 전개)
    float det = this->m[0][0] * inv[0][0]
        + this->m[0][1] * inv[1][0]
        + this->m[0][2] * inv[2][0]
        + this->m[0][3] * inv[3][0];


    det = 1.0 / det;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            invOut.m[i][j] = inv[i][j] * det;
    }

    return invOut;
}
