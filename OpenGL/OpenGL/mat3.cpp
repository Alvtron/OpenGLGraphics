#include "mat3.h"

mat3::mat3() {
	for (int i = 0; i < 9; i++)
		matrix[i] = 0.0f;
}

std::ostream& operator<<(std::ostream& stream, const mat3& m) {
	stream << "mat3: \n" <<
		m.matrix[0] << "\t" << m.matrix[1] << "\t" << m.matrix[2] << "\n" <<
		m.matrix[3] << "\t" << m.matrix[4] << "\t" << m.matrix[5] << "\n" <<
		m.matrix[6] << "\t" << m.matrix[7] << "\t" << m.matrix[8];
	return stream;
}