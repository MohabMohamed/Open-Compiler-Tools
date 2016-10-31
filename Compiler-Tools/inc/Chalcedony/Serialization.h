#pragma once

#include "Chalcedony/Defines.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/binary.hpp>
#include <vector>
#include <memory>
#include <ostream>
#include <istream>

namespace CT
{

	class Serialization
	{
	public:

		template<typename datatype>
		static void save(datatype& object, std::ostream& stream)
		{
			cereal::JSONOutputArchive archive(stream);
			object.save(archive);
		}

		template<typename datatype>
		static void load(datatype& object, std::istream& stream)
		{
			cereal::JSONInputArchive archive(stream);
			object.load(archive);
		}
	};
}