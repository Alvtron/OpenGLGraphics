#include "mat2.h"

mat2::mat2() {
	for (int i = 0; i < 4; i++)
		matrix[i] = 0.0f;
}

std::ostream& operator<<(std::ostream& stream, const mat2& m) {
	stream << "mat2: \n" <<
		m.matrix[0] << "\t" << m.matrix[1] << "\n" <<
		m.matrix[2] << "\t" << m.matrix[3];
	return stream;
}