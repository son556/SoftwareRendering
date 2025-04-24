#pragma once

class Matrix4x4;
class Vector3;
class Quaternion;
class Vector4;

class MatrixUtils
{
public:
	static void	identity(Matrix4x4& m);
	static void	scaleMatrix(Matrix4x4& m, Vector3 const& scale);
	static void	rotateMatrix(Matrix4x4& m, Quaternion const& rotation);
	static void	translateMatrix(Matrix4x4& m, Vector3 const& translation);
	static void	viewMatrix(Matrix4x4& m, Vector3 const& pos, Vector3 const& dir);
	static void	perspectiveMatrix(
		Matrix4x4& m, float fov, float aspect, float c_near, float c_far);
	static void modelMatrix(Matrix4x4& m, 
		Vector3 const& translation, 
		Quaternion const& rotation, 
		Vector3 const& scale);

public: // test용 코드
	static void showMat(Matrix4x4 const& m);
	static void showVec3(Vector3 const& v);
	static void showVec4(Vector4 const& v);
private:
	MatrixUtils() = delete;
	MatrixUtils(MatrixUtils const&) = delete;
	MatrixUtils& operator=(const MatrixUtils&) = delete;
	~MatrixUtils() = delete;
};

