#include "pch.h"
#include "FBXImporter.h"

#include<iostream>
#include<fbxsdk.h>

namespace Hydron
{

    FBXImporter::FBXImporter(const std::string& filePath)
    {

        FbxManager* manager = FbxManager::Create();

        if (manager == NULL) {
            HYDRON_CORE_ERROR("FBX Manager initialization failed!");
            return;
        }

        FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT); // ���o�͐ݒ���쐬����
        manager->SetIOSettings(ios);    // �}�l�[�W���[�ɓ��o�͐ݒ���Z�b�g����

        FbxImporter* importer = FbxImporter::Create(manager, "");   // FBX�C���|�[�^������������

        // FBX�t�@�C���̓ǂݍ��݂����s����
        if (!importer->Initialize(filePath.c_str(), -1, manager->GetIOSettings())) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX load error!");
            return;
        }
        
        FbxScene* scene = FbxScene::Create(manager, "");    // FBX�V�[��(3D��Ԃ��\������I�u�W�F�N�g���)������������

        // �V�[���̃C���|�[�g�����s����
        if (!importer->Import(scene)) {
            manager->Destroy();
            HYDRON_CORE_ERROR("FBX scene import error!");
            return;
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
            return;
        }


        // Model Asset�쐬
        ModelAsset model_asset;

        LoadVertex(model_asset, *mesh);
        LoadIndices(model_asset, *mesh);

        HYDRON_CORE_INFO("Index : {0}", model_asset.indices_count);
        HYDRON_CORE_INFO("Vert : {0}", model_asset.vertices_count);

        scene->Destroy();
        manager->Destroy();
    }

    
    void FBXImporter::LoadIndices(ModelAsset& model_asset, FbxMesh& mesh)
    {
        int polygon_vertex_count = mesh.GetPolygonVertexCount();
        model_asset.indices_count = polygon_vertex_count;
        model_asset.indices = new uint32_t[polygon_vertex_count];

        for (int i = 0; i < polygon_vertex_count; i++) {
            model_asset.indices[i] = mesh.GetPolygonVertices()[i];
        }
    }

    void FBXImporter::LoadVertex(ModelAsset& model_asset, FbxMesh& mesh)
    {
        int control_points_count = mesh.GetControlPointsCount();
        model_asset.vertices_count = control_points_count;
        model_asset.vertices = new Vertex[control_points_count];

        for (int i = 0; i < control_points_count; i++) {
            FbxVector4 point = mesh.GetControlPointAt(i);
            Vertex vertex;
            vertex.position[0] = point[0];
            vertex.position[1] = point[1];
            vertex.position[2] = point[2];

            model_asset.vertices[i] = vertex;
        }
    }
}