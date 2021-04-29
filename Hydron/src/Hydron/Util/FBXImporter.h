#pragma once

#include <string>

#include <fbxsdk.h>

#include "Hydron/Geometry/ModelAsset.h"

namespace Hydron
{


	class FBXImporter
	{

	public:
		FBXImporter(const std::string& filePath);

	private:
		static void LoadVertex(ModelAsset& model_asset, FbxMesh& mesh);
		static void LoadIndices(ModelAsset& model_asset, FbxMesh& mesh);
	};

}