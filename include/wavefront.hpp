#ifndef banana_wavefront_hpp
#define banana_wavefront_hpp

#include "geometry.hpp"

#include <regex>
#include <string>
#include <fstream>

struct Wavefront
{
public:
	Wavefront(std::string _filename)
	{
		const std::regex rx_commentLine( "#" );
		const std::regex rx_materialFile( "mtllib ([^ ]+)" );
		const std::regex rx_vertex3( "v ([^ ]+) ([^ ]+) ([^ ]+)" );
		const std::regex rx_vertex4( "v ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)" );
		const std::regex rx_vertexNormal( "vn ([^ ]+) ([^ ]+) ([^ ]+)" );
		const std::regex rx_textureCoords2( "vt ([^ ]+) ([^ ]+)" );
		const std::regex rx_textureCoords3( "vt ([^ ]+) ([^ ]+) ([^ ]+)" );
		const std::regex rx_materialGroup( "usemtl ([^ ]+)" );
		const std::regex rx_objectName( "o ([^ ]+)" );
		const std::regex rx_groupName( "g ([^ ]+)" );
		const std::regex rx_face_vertex( "f ([^ ]+) ([^ ]+) ([^ ]+)" );
		const std::regex rx_face_vertexTexture( "f ([^/]+)/([^ ]+) ([^/]+)/([^ ]+) ([^/]+)/([^ ]+)" );
		const std::regex rx_face_vertexTextureNormal( "f ([^/]+)/([^/]+)/([^/]+) ([^/]+)/([^/]+)/([^ ]+) ([^/]+)/([^/]+)/([^ ]+)" );
		const std::regex rx_face_vertexNormal( "f ([^/]+)//([^ ]+) ([^/]+)//([^ ]+) ([^/]+)//([^ ]+)" );

		std::ifstream file(_filename);
		std::string line;
		std::smatch res;

		assert(file);

		std::vector<Mathematics::vec<float,3>> positions;
		std::vector<Mathematics::vec<float,3>> normals;
		std::vector<Mathematics::vec<float,2>> coords;

		while(file)
		{
			std::getline(file, line);

			if(std::regex_search(line, res, rx_commentLine))
				continue;
			if(std::regex_match(line, res, rx_vertex3))
			{
				positions.push_back({{std::stof(res.str(1)), std::stof(res.str(2)), std::stof(res.str(3))}});
				continue;
			}
			if(std::regex_match(line, res, rx_vertexNormal))
			{
				normals.push_back({{std::stof(res.str(1)), std::stof(res.str(2)), std::stof(res.str(3))}});
				continue;
			}

			if(std::regex_match(line, res, rx_face_vertexNormal))
			{
				vertices.resize(positions.size());
				vertex v1{}, v2{}, v3{};
				v1.pos = positions[std::stoul(res.str(1))-1];
				v2.pos = positions[std::stoul(res.str(3))-1];
				v3.pos = positions[std::stoul(res.str(5))-1];
				v1.norm = normals[std::stoul(res.str(2))-1];
				v2.norm = normals[std::stoul(res.str(4))-1];
				v3.norm = normals[std::stoul(res.str(6))-1];

				vertices[std::stoul(res.str(1))-1] = v1;
				vertices[std::stoul(res.str(3))-1] = v2;
				vertices[std::stoul(res.str(5))-1] = v3;
				indices.push_back({{{static_cast<unsigned int>(std::stoul(res.str(1))-1), static_cast<unsigned int>(std::stoul(res.str(3))-1), static_cast<unsigned int>(std::stoul(res.str(5))-1)}}});
				continue;
			}
		}
	}
	std::vector<vertex> vertices;
	std::vector<face> indices;
};

#endif