#pragma once

#include "VertexArray.h"
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "glm/glm.hpp"

namespace renderdata
{
	struct Data
	{
		float* vertices_array;
		int vertices_num;

		int* indices_array;
		int indices_num;

		int* attr_array;

		char* vert_shader_name;
		char* frag_shader_name;
	};

	bool ParseJsonFile(const char* file_path, renderdata::Data* data_struct);
};