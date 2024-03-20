#include "Skin.h"
#include "GLTF.h"
#include "File.h"
#include "meshData.h"
#include "ShaderLayout.h"
#include "meshDataConverter.h"

using namespace tinygltf;

namespace Azul
{
	void CreateSkin(const char* const inName, const char* const outName)
	{
        const char* inFileExt = ".glb";
        const char* outFileExt = ".skin.proto.azul";

        size_t inFileNameSize = strlen(inName) + strlen(inFileExt) + 1;
        size_t outFileNameSize = strlen(outName) + strlen(outFileExt) + 1;

        char* inFileName = new char[inFileNameSize]();
        strcat_s(inFileName, inFileNameSize, inName);
        strcat_s(inFileName, inFileNameSize, inFileExt);

        char* outFileName = new char[outFileNameSize]();
        strcat_s(outFileName, outFileNameSize, outName);
        strcat_s(outFileName, outFileNameSize, outFileExt);

        char* buff = nullptr;
        unsigned int buffSize = 0;
        bool status;
        tinygltf::Model gltfModel;
        meshData runtimeModel;
        GLB_header glbHeader;
        char* json = nullptr;
        unsigned int jsonSize = 0;
        char* binBuff = nullptr;
        unsigned int binBuffSize = 0;

        status = GLTF::LoadBinary(gltfModel, inFileName);
        status = GLTF::GetGLBRawBuffer(buff, buffSize, inFileName);
        status = GLTF::GetGLBHeader(glbHeader, buff, buffSize);
        status = GLTF::GetRawJSON(json, jsonSize, buff, buffSize);
        status = GLTF::GetBinaryBuffPtr(binBuff, binBuffSize, buff, buffSize);

        SkinMesh skinMesh;

        tinygltf::Primitive prim = gltfModel.meshes[0].primitives[0];
        std::map<std::string, int> attribs = prim.attributes;

        size_t inverseMatrixAccessorIndex = gltfModel.skins[0].inverseBindMatrices;
        //assert(inverseMatrixAccessorIndex == 17);
        size_t weightAccessorIndex = attribs.at("WEIGHTS_0");
        //assert(weightAccessorIndex == 16);
        size_t jointAccessorIndex = attribs.at("JOINTS_0");
        //assert(jointAccessorIndex == 15);
        size_t indexAccessorIndex = prim.indices;
        //assert(indexAccessorIndex == 11);
        size_t posAccessorIndex = attribs.at("POSITION");
        //assert(posAccessorIndex == 12);
        size_t normsAccessorIndex = attribs.at("NORMAL");
        //assert(normsAccessorIndex == 13);
        size_t texCoordAccessorIndex = attribs.at("TEXCOORD_0");
        //assert(texCoordAccessorIndex == 14);

        unsigned char* dataBuff = (unsigned char*)&gltfModel.buffers[0].data[0];

        auto jointAccessor = gltfModel.accessors[jointAccessorIndex];
        auto jointBuffView = gltfModel.bufferViews[(size_t)jointAccessor.bufferView];
        unsigned char* jointBuff = dataBuff + jointBuffView.byteOffset;

        auto weightAccessor = gltfModel.accessors[weightAccessorIndex];
        auto weightBuffView = gltfModel.bufferViews[(size_t)weightAccessor.bufferView];
        unsigned char* weightBuff = dataBuff + weightBuffView.byteOffset;

        auto inverseAccessor = gltfModel.accessors[inverseMatrixAccessorIndex];
        auto inverseBuffView = gltfModel.bufferViews[(size_t)inverseAccessor.bufferView];
        unsigned char* inverseBuff = dataBuff + inverseBuffView.byteOffset;

        auto indexAccessor = gltfModel.accessors[indexAccessorIndex];
        auto indexBuffView = gltfModel.bufferViews[(size_t)indexAccessor.bufferView];
        unsigned char* indexBuff = dataBuff + indexBuffView.byteOffset;

        auto posAccessor = gltfModel.accessors[posAccessorIndex];
        auto posBuffView = gltfModel.bufferViews[(size_t)posAccessor.bufferView];
        unsigned char* posBuff = dataBuff + posBuffView.byteOffset;

        auto normsAccessor = gltfModel.accessors[normsAccessorIndex];
        auto normsBuffView = gltfModel.bufferViews[(size_t)normsAccessor.bufferView];
        unsigned char* normsBuff = dataBuff + normsBuffView.byteOffset;

        auto texCoordAccessor = gltfModel.accessors[texCoordAccessorIndex];
        auto texCoordBuffView = gltfModel.bufferViews[(size_t)texCoordAccessor.bufferView];
        unsigned char* texCoordBuff = dataBuff + texCoordBuffView.byteOffset;

        Mat4* mat4 = (Mat4*)inverseBuff;
        for (size_t i = 0; i < inverseAccessor.count; i++)
        {
            skinMesh.invBone.push_back(mat4[i]);
        }

        /*skinMesh.jointTable = gltfModel.skins[0].joints;
        Trace::out("\n");
        Trace::out("int JointTable_Size = %d; \n", skinMesh.jointTable.size());
        Trace::out("int JointTable[] = { \n");
        for (size_t i = 0; i < skinMesh.jointTable.size(); i++)
        {
            if (i != skinMesh.jointTable.size() - 1)
            {
                Trace::out("\t\t\t\t%d, \n", skinMesh.jointTable[i]);
            }
            else
            {
                Trace::out("\t\t\t\t%d }; \n", skinMesh.jointTable[i]);
            }
        }
        Trace::out("\n");*/

        isVect4* jointsV4 = (isVect4*)jointBuff;
        fVect4* weightsV4 = (fVect4*)weightBuff;
        fVect3* posV3 = (fVect3*)posBuff;
        fVect3* normsV3 = (fVect3*)normsBuff;
        fVect2* textCoordV2 = (fVect2*)texCoordBuff;

        for (size_t i = 0; i < posAccessor.count; i++)
        {
            skinMesh.joints.push_back(iuVect4((unsigned int)jointsV4[i].x, (unsigned int)jointsV4[i].y, (unsigned int)jointsV4[i].z, (unsigned int)jointsV4[i].w));
            skinMesh.weights.push_back(weightsV4[i]);
            skinMesh.pos.push_back(posV3[i]);
            skinMesh.norms.push_back(normsV3[i]);
            skinMesh.text_coord.push_back(textCoordV2[i]);
        }

        isVect3* indices = (isVect3*)indexBuff;

        for (size_t i = 0; i < indexAccessor.count / 3; i++)
        {
            skinMesh.index.push_back(iuVect3(indices[i].x, indices[i].y, indices[i].z));
        }

        skinMesh.skinName = gltfModel.meshes[0].name;
        skinMesh.vertCount = posAccessor.count;
        skinMesh.polyCount = indexAccessor.count / 3;

        memcpy_s(runtimeModel.pMeshName, meshData::FILE_NAME_SIZE, skinMesh.skinName.c_str(), skinMesh.skinName.size());
	
        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_VERT,
            "POSITION",
            runtimeModel.vbo_vert,
            (char*)&skinMesh.pos[0],
            skinMesh.pos.size() * sizeof(fVect3),
            skinMesh.pos.size(),
            vboData::VBO_COMPONENT::FLOAT,
            vboData::VBO_TYPE::VEC3,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_NORM,
            "NORMAL",
            runtimeModel.vbo_norm,
            (char*)&skinMesh.norms[0],
            skinMesh.norms.size() * sizeof(fVect3),
            skinMesh.norms.size(),
            vboData::VBO_COMPONENT::FLOAT,
            vboData::VBO_TYPE::VEC3,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_TEXT,
            "TEXCOORD_0",
            runtimeModel.vbo_uv,
            (char*)&skinMesh.text_coord[0],
            skinMesh.text_coord.size() * sizeof(fVect2),
            skinMesh.text_coord.size(),
            vboData::VBO_COMPONENT::FLOAT,
            vboData::VBO_TYPE::VEC2,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        GLTF::SetCustomVBO_index(
            ATTRIB_LOCATION_INDEX,
            "INDEX",
            runtimeModel.vbo_index,
            (char*)&skinMesh.index[0],
            skinMesh.index.size() * sizeof(iuVect3),
            skinMesh.index.size(),
            vboData::VBO_COMPONENT::UNSIGNED_INT,
            vboData::VBO_TYPE::SCALAR,
            vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);

        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_WEIGHT,
            "WEIGHTS_0",
            runtimeModel.vbo_weights,
            (char*)&skinMesh.weights[0],
            skinMesh.weights.size() * sizeof(fVect4),
            skinMesh.weights.size(),
            vboData::VBO_COMPONENT::FLOAT,
            vboData::VBO_TYPE::VEC4,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_JOINT,
            "JOINTS_0",
            runtimeModel.vbo_joints,
            (char*)&skinMesh.joints[0],
            skinMesh.joints.size() * sizeof(iuVect4),
            skinMesh.joints.size(),
            vboData::VBO_COMPONENT::UNSIGNED_INT,
            vboData::VBO_TYPE::VEC4,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        GLTF::SetCustomVBO(
            ATTRIB_LOCATION_INVERSE_BIND,
            "INVERSE_BIND_0",
            runtimeModel.vbo_invbind,
            (char*)&skinMesh.invBone[0],
            skinMesh.invBone.size() * sizeof(Mat4),
            skinMesh.invBone.size(),
            vboData::VBO_COMPONENT::FLOAT,
            vboData::VBO_TYPE::MAT4,
            vboData::VBO_TARGET::ARRAY_BUFFER);

        runtimeModel.triCount = runtimeModel.vbo_index.count / 3;
        runtimeModel.vertCount = runtimeModel.vbo_vert.count;

        runtimeModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);

        meshData_proto meshProto;
        runtimeModel.Serialize(meshProto);

        File::Handle handle;
        File::Error err;

        err = File::Open(handle, outFileName, File::Mode::WRITE);
        
        std::string strOut;
        meshProto.SerializeToString(&strOut);

        err = File::Write(handle, strOut.data(), strOut.length());
        err = File::Close(handle);

        delete[] inFileName;
        delete[] outFileName;
        delete[] buff;
        delete[] json;
       // delete[] binBuff;
       // delete[] dataBuff;
    }
}