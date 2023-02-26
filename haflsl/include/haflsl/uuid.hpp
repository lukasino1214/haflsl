#pragma once

#include "types.hpp"

namespace HAFLSL {
	struct UUID {
	public:
		UUID();
		UUID(u64 uuid);
		UUID(const UUID&) = default;

		operator u64() const { return uuid; }
	private:
		u64 uuid = 0;
	};

}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<HAFLSL::UUID> {
		std::size_t operator()(const HAFLSL::UUID& uuid) const {
			return static_cast<HAFLSL::Types::u64>(uuid);
		}
	};

}