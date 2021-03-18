#include <algorithm>

inline int clamp(int MIN, int VAL, int MAX) {
	return (std::max(MIN, std::min(VAL, MAX)));
}