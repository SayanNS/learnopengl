#include "ParseJson.h"
#include <iostream>

bool renderdata::ParseJsonFile(const char* file_path, renderdata::Data* data_struct)
{
	std::string file;

	std::ifstream my_file(file_path);

	if (my_file.is_open())
	{
		std::string line;

		while (my_file >> line)
		{
			file.append(line);
		}

		my_file.close();
	}
	else
	{
		return false;
	}

	rapidjson::Document document;
	document.Parse(file.c_str());

	{
		rapidjson::Value& vertices_value = document["vertices"];
		int vertices_num = vertices_value.Size();
	
		rapidjson::Value& indices_value = document["indices"];
		int indices_num = indices_value.Size();

		float* array = new float[indices_num * 6];

		for (int i = 0; i < indices_num / 3; i++)
		{
			float vertices[3][3];

			for (int j = 0; j < 3; j++)
			{
				int index = indices_value[i * 3 + j].GetInt();

				for (int k = 0; k < 3; k++)
				{
					vertices[j][k] = vertices_value[index * 3 + k].GetFloat();
				}
			}

			glm::vec3 a(vertices[1][0] - vertices[0][0], vertices[1][1] - vertices[0][1], vertices[1][2] - vertices[0][2]);
			glm::vec3 b(vertices[1][0] - vertices[2][0], vertices[1][1] - vertices[2][1], vertices[1][2] - vertices[2][2]);
			glm::vec3 c = glm::normalize(glm::cross(a, b));

			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					array[i * 18 + j * 6 + k] = vertices[j][k];
					array[i * 18 + j * 6 + k + 3] = c[k];
				}
			}
		}

		data_struct->vertices_array = array;
		data_struct->vertices_num = indices_num * 6;
	}

	{
		rapidjson::Value& value = document["attrArray"];
		int num = value.Size();
		int* array = new int[num + 1];
		int sum = 0;

		for (int i = 0; i < num; i++)
		{
			int val = value[i].GetInt();
			array[i + 1] = val;
			sum += val;
		}

		array[0] = sum;
		data_struct->attr_array = array;
	}

	{
		rapidjson::Value& value = document["vert_shader"];
		int num = value.GetStringLength();
		char* array = new char[num + 1];
		const char* str = value.GetString();

		for (int i = 0; i < num; i++)
		{
			array[i] = str[i];
		}

		array[num] = 0;
		data_struct->vert_shader_name = array;
	}

	{
		rapidjson::Value& value = document["frag_shader"];
		int num = value.GetStringLength();
		char* array = new char[num + 1];
		const char* str = value.GetString();

		for (int i = 0; i < num; i++)
		{
			array[i] = str[i];
		}

		array[num] = 0;
		data_struct->frag_shader_name = array;
	}

	return true;
}