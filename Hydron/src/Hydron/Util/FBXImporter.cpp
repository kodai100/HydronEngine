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

        FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT); // ���o�͐ݒ���쐬����
        manager->SetIOSettings(ios);    // �}�l�[�W���[�ɓ��o�͐ݒ���Z�b�g����

        FbxImporter* importer = FbxImporter::Create(manager, "");   // FBX�C���|�[�^������������

        // FBX�t�@�C���̓ǂݍ��݂����s����
        if (!importer->Initialize(filePath.c_str(), -1, manager->GetIOSettings())) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX load error!");
            return nullptr;
        }
        
        FbxScene* scene = FbxScene::Create(manager, "");    // FBX�V�[��(3D��Ԃ��\������I�u�W�F�N�g���)������������

        // �V�[���̃C���|�[�g�����s����
        if (!importer->Import(scene)) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX scene import error!");
            return nullptr;
        }
        
        importer->Destroy();    // �V�[���̓ǂݍ��݂���������΃C���|�[�^�͕s�v�Ȃ̂Ŕj������

        // �O�p�|���S���ւ̕ϊ����s��
        FbxGeometryConverter geometryConverter(manager);
        geometryConverter.Triangulate(scene, true);

        // ������3D�f�[�^�ւ̏������s��

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
            // ���_�z��
            int indexCount = mesh.GetPolygonVertexCount();

            // TIPS:FBX�͕ێ����Ă��钸�_���W���Ɩ@������UV������v���Ȃ��̂�
            //      ���_�z�񂩂�W�J����TriMesh�Ɋi�[���Ă���(T^T)
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
            // ���_�@��
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