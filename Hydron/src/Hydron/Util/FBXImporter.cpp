#include "pch.h"
#include "FBXImporter.h"

namespace Hydron
{

    Mesh* FBXImporter::Load(const std::string& filePath)
    {

        FbxManager* manager = FbxManager::Create();

        if (manager == NULL) {
            HYDRON_CORE_ERROR("FBX Manager initialization failed!");
            return nullptr;
        }

        FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT); // 入出力設定を作成する
        manager->SetIOSettings(ios);    // マネージャーに入出力設定をセットする

        FbxImporter* importer = FbxImporter::Create(manager, "");   // FBXインポータを初期化する

        // FBXファイルの読み込みを実行する
        if (!importer->Initialize(filePath.c_str(), -1, manager->GetIOSettings())) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX load error!");
            return nullptr;
        }
        
        FbxScene* scene = FbxScene::Create(manager, "");    // FBXシーン(3D空間を構成するオブジェクト情報)を初期化する

        // シーンのインポートを実行する
        if (!importer->Import(scene)) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX scene import error!");
            return nullptr;
        }
        
        importer->Destroy();    // シーンの読み込みが完了すればインポータは不要なので破棄する

        // 三角ポリゴンへの変換を行う
        FbxGeometryConverter geometryConverter(manager);
        geometryConverter.Triangulate(scene, true);

        // ここで3Dデータへの処理を行う

        FbxMesh* mesh = scene->GetSrcObject<FbxMesh>();
        if (!mesh) {
            scene->Destroy();
            manager->Destroy();
            HYDRON_CORE_ERROR("Failed to load model");
            return nullptr;
        }

        auto m = LoadInternal(*mesh);

        scene->Destroy();
        manager->Destroy();

        return m;
    }

    

    Mesh* FBXImporter::LoadInternal(FbxMesh& mesh)
    {

        Mesh* hMesh = new Mesh();

        {
            // 頂点配列
            int indexCount = mesh.GetPolygonVertexCount();

            // TIPS:FBXは保持している頂点座標数と法線数とUV数が一致しないので
            //      頂点配列から展開してTriMeshに格納している(T^T)
            int* index = mesh.GetPolygonVertices();
            for (int i = 0; i < indexCount; ++i)
            {
                auto controlPoint = mesh.GetControlPointAt(index[i]);
                hMesh->PushPosition(glm::vec3(controlPoint[0], controlPoint[1], controlPoint[2]));
            }

            for (int i = 0; i < indexCount; i += 3)
            {
                hMesh->PushTriangle(i, i + 1, i + 2);
            }
        }

        {
            // 頂点法線
            FbxArray<FbxVector4> normals;
            mesh.GetPolygonVertexNormals(normals);

            for (int i = 0; i < normals.Size(); ++i)
            {
                const FbxVector4& n = normals[i];
                hMesh->PushNormal(glm::vec3(n[0], n[1], n[2]));
            }
        }

        {
            // UV
            FbxStringList uvsetName;
            mesh.GetUVSetNames(uvsetName);

            if (uvsetName.GetCount() > 0)
            {

                FbxArray<FbxVector2> uvsets;
                mesh.GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

                for (int i = 0; i < uvsets.Size(); ++i)
                {
                    const FbxVector2& uv = uvsets[i];
                    hMesh->PushUv(glm::vec2(uv[0], uv[1]));
                }
            }
        }

        return hMesh;

    }


}