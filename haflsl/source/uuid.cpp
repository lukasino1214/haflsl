#include <haflsl/uuid.hpp>

#include <random>

#include <unordered_map>

namespace HAFLSL {
	static std::random_device random_device;
	static std::mt19937_64 engine(random_device());
	static std::uniform_int_distribution<u64> uniform_int_distribution;

	UUID::UUID() : uuid(uniform_int_distribution(engine)) {}
	UUID::UUID(u64 uuid) : uuid(uuid) {}
}