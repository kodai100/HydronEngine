#pragma once

#include <string>

#include <fbxsdk.h>

#include "Hydron/Geometry/Mesh.h"

namespace Hydron
{


	class FBXImporter
	{

	public:
		FBXImporter() {}

		static Mesh* Load(const std::string& filePath);

	private:
		static Mesh* LoadInternal(FbxMesh& mesh);
	};

}