#include "pch.h"
#include "MatrixUtils.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

void MatrixUtils::identity(Matrix4x4& mat)
{
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (r == c)
				mat.m[r][c] = 1;
			else
				mat.m[r][c] = 0;
		}
	}
}

void MatrixUtils::scaleMatrix(Matrix4x4& mat, Vector3 const& scale)
{
	for (int r = 0; r < 3; r++) {
		mat.m[r][0] *= scale.x;
		mat.m[r][1] *= scale.y;
		mat.m[r][2] *= scale.z;
	}
}

void MatrixUtils::rotateMatrix(Matrix4x4& m, Quaternion const& rotation)
{
	for (int c = 0; c < 3; c++) {
		Vector3 const	row = rotation * 
			Vector3(m.m[0][c], m.m[1][c], m.m[2][c]);

		m.m[0][c] = row.x;
		m.m[1][c] = row.y;
		m.m[2][c] = row.z;
	}
}

void MatrixUtils::translateMatrix(Matrix4x4& mat, Vector3 const& translation)
{
	mat.m[0][3] += translation.x;
	mat.m[1][3] += translation.y;
	mat.m[2][3] += translation.z;
}

// 왼손 좌표계
void MatrixUtils::viewMatrix(
	Matrix4x4& ref, 
	Vector3 const& pos, 
	Vector3 const& dir
)
{
	Vector3	forward = dir.normalized();
	Vector3	right = Vector3(0, 1, 0).cross(forward).normalized();
	Vector3 up = forward.cross(right).normalized();

	ref.m[0][0] = right.x;
	ref.m[0][1] = right.y;
	ref.m[0][2] = right.z;
	ref.m[0][3] = pos * right;
	ref.m[0][3] *= -1;
	
	ref.m[1][0] = up.x;
	ref.m[1][1] = up.y;
	ref.m[1][2] = up.z;
	ref.m[1][3] = pos * up;
	ref.m[1][3] *= -1;

	ref.m[2][0] = forward.x;
	ref.m[2][1] = forward.y;
	ref.m[2][2] = forward.z;
	ref.m[2][3] = pos * forward;
	ref.m[2][3] *= -1;

	ref.m[3][0] = 0;
	ref.m[3][1] = 0;
	ref.m[3][2] = 0;
	ref.m[3][3] = 1;
}

void MatrixUtils::perspectiveMatrix(
	Matrix4x4& ref, 
	float fov, 
	float aspect, 
	float near, 
	float far
)
{
	float const	t = 1 / std::tanf(fov / 360.f * M_PI);

	ref.m[0][0] = t / aspect;
	ref.m[0][1] = 0;
	ref.m[0][2] = 0;
	ref.m[0][3] = 0;

	ref.m[1][0] = 0;
	ref.m[1][1] = t;
	ref.m[1][2] = 0;
	ref.m[1][3] = 0;

	ref.m[2][0] = 0;
	ref.m[2][1] = 0;
	ref.m[2][2] = (near + far) / (far - near);
	ref.m[2][3] = 2 * near * far / (near - far);

	ref.m[3][0] = 0;
	ref.m[3][1] = 0;
	ref.m[3][2] = 1;
	ref.m[3][3] = 0;
}

void MatrixUtils::modelMatrix(
	Matrix4x4& m, 
	Vector3 const& translation, 
	Quaternion const& rotation, 
	Vector3 const& scale
) 
{
	MatrixUtils::identity(m);
	MatrixUtils::scaleMatrix(m, scale);
	MatrixUtils::rotateMatrix(m, rotation);
	MatrixUtils::translateMatrix(m, translation);
}

void MatrixUtils::showMat(Matrix4x4 const& m)
{
	cout << "Matrix4x4" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m.m[i][j] << ' ';
			if (j == 3)
				cout << endl;
		}
	}
	cout << endl;
}

void MatrixUtils::showVec3(Vector3 const& v)
{
	cout << "Vector3: ";
	cout << "{ x: " << v.x << ", y: " << v.y << ", z: " << v.z << " }" << endl;
}

void MatrixUtils::showVec4(Vector4 const& v)
{
	cout << "Vector4: ";
	cout << "{ x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " 
		<< v.w << " }" << endl;
}
