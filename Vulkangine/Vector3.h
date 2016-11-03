#ifndef VECTOR3_H
#define VECTOR3_H

#include <sstream>

class Vector3 {
	public: 
		float x, y, z;
		Vector3(float x, float y, float z);
		Vector3(Vector3 * vec);
		Vector3();

		void add(Vector3 * vec);
		std::string toString();
		Vector3 operator+(const Vector3 & other);
		Vector3 operator*(const float & other);
};

#endif