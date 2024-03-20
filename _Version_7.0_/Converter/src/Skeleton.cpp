//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Skeleton.h"
#include "GLTF.h"

namespace Azul
{

	skeleton::skeleton()
		:nodeIndex(-1),
		nodeName(),
		parentIndex(-1),
		parentName("unknown")
	{

	};

	skelData* SKEL::CreateVectorChickenBot(Model &model)
	{
		// Create a skeleton and Fill it
		this->skeletonVector.reserve(model.skins[0].joints.size());
		for(size_t i = 0; i < model.skins[0].joints.size(); i++)
		{
			skeleton tmpSkeleton;
			this->skeletonVector.push_back(tmpSkeleton);
		}

		// Walk through the nodes starting on the node they state
		size_t StartNodeIndex = (size_t)model.skins[0].joints[0];
		for(size_t i = StartNodeIndex; i < StartNodeIndex + this->skeletonVector.size(); i++)
		{
			auto pNode = model.nodes[i];
			skeletonVector[i - StartNodeIndex].nodeIndex = (int)i;
			skeletonVector[i - StartNodeIndex].nodeName = pNode.name;
			//Trace::out("%d: %s \n", i, pNode.name.c_str());
			for(size_t j = 0; j < pNode.children.size(); j++)
			{
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].nodeIndex = pNode.children[j];
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].nodeName = model.nodes[(size_t)pNode.children[j]].name;
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].parentIndex = (int)i;
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].parentName = pNode.name;
				//Trace::out("\t child: (%d) %s \n", pNode.children[j], model.nodes[(size_t)pNode.children[j]].name.c_str());
			}
		}

		// Fill skeletonTable
		skeletonTable.reserve(skeletonVector.size());
		for(size_t i = 0; i < skeletonVector.size(); i++)
		{
			skeleton_table table;

			table.nodeIndex = skeletonVector[i].nodeIndex;
			table.parentIndex = skeletonVector[i].parentIndex;

			// Copy the string
			memset(table.nodeName, 0, skeleton_table::SKELETON_NAME_SIZE);
			strncpy_s(table.nodeName,
				skeleton_table::SKELETON_NAME_SIZE,
				skeletonVector[i].nodeName.c_str(),
				skeleton_table::SKELETON_NAME_SIZE - 1);

			skeletonTable.push_back(table);
		}

		unsigned int boneCount = skeletonTable.size();
		skelData* sData = new skelData();
		sData->boneCount = boneCount;
		sData->bones = new boneContainer[boneCount]();

		int tmpIndex = -1;
		int tmpParentIndex = -1;

		for (unsigned int i = 0; i < boneCount; i++)
		{

			tmpIndex = skeletonTable[i].nodeIndex;// -4;
			tmpParentIndex = skeletonTable[i].parentIndex;
			if (tmpParentIndex != -1)
				tmpParentIndex = tmpParentIndex;// -4;

			sData->bones[i].index = tmpIndex;
			sData->bones[i].parentIndex = tmpParentIndex;
			memcpy_s(sData->bones[i].nodeName,
				boneContainer::SKELETON_NAME_SIZE,
				&skeletonTable[i].nodeName[0],
				boneContainer::SKELETON_NAME_SIZE);
		}

		return sData;
	}

	skelData* SKEL::CreateVector(Model& model)
	{
		// Create a skeleton and Fill it
		this->skeletonVector.reserve(model.nodes.size());
		for (size_t i = 0; i < model.nodes.size(); i++)
		{
			skeleton tmpSkeleton;
			this->skeletonVector.push_back(tmpSkeleton);
		}

		// Walk through the nodes starting on the node they state
		size_t StartNodeIndex = 0;// (size_t)model.skins[0].joints[0];
		for (size_t i = StartNodeIndex; i < StartNodeIndex + this->skeletonVector.size(); i++)
		{
			auto pNode = model.nodes[i];
			skeletonVector[i - StartNodeIndex].nodeIndex = (int)i;
			skeletonVector[i - StartNodeIndex].nodeName = pNode.name;
			//Trace::out("%d: %s \n", i, pNode.name.c_str());
			for (size_t j = 0; j < pNode.children.size(); j++)
			{
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].nodeIndex = pNode.children[j];
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].nodeName = model.nodes[(size_t)pNode.children[j]].name;
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].parentIndex = (int)i;
				skeletonVector[(size_t)pNode.children[j] - StartNodeIndex].parentName = pNode.name;
				//Trace::out("\t child: (%d) %s \n", pNode.children[j], model.nodes[(size_t)pNode.children[j]].name.c_str());
			}
		}

		// Fill skeletonTable
		skeletonTable.reserve(skeletonVector.size());
		for (size_t i = 0; i < skeletonVector.size(); i++)
		{
			skeleton_table table;

			table.nodeIndex = skeletonVector[i].nodeIndex;
			table.parentIndex = skeletonVector[i].parentIndex;

			// Copy the string
			memset(table.nodeName, 0, skeleton_table::SKELETON_NAME_SIZE);
			strncpy_s(table.nodeName,
				skeleton_table::SKELETON_NAME_SIZE,
				skeletonVector[i].nodeName.c_str(),
				skeleton_table::SKELETON_NAME_SIZE - 1);

			skeletonTable.push_back(table);
		}

		unsigned int boneCount = skeletonTable.size();
		skelData* sData = new skelData();
		sData->boneCount = boneCount;
		sData->bones = new boneContainer[boneCount]();

		int tmpIndex = -1;
		int tmpParentIndex = -1;

		for (unsigned int i = 0; i < boneCount; i++)
		{

			tmpIndex = skeletonTable[i].nodeIndex;
			tmpParentIndex = skeletonTable[i].parentIndex;
			if (tmpParentIndex != -1)
				tmpParentIndex = tmpParentIndex;

			sData->bones[i].index = tmpIndex;
			sData->bones[i].parentIndex = tmpParentIndex;
			memcpy_s(sData->bones[i].nodeName,
				boneContainer::SKELETON_NAME_SIZE,
				&skeletonTable[i].nodeName[0],
				boneContainer::SKELETON_NAME_SIZE);
		}

		SkinMesh skinMesh;
		skinMesh.jointTable = model.skins[0].joints;
		sData->jointTableCount = skinMesh.jointTable.size();
		sData->jointTable = new unsigned int[sData->jointTableCount]();
		for (int i = 0; i < sData->jointTableCount; i++)
		{
			sData->jointTable[i] = skinMesh.jointTable.at(i);
		}

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
		Trace::out("\n");

		return sData;
	}

	hierarchyData* SKEL::Hierarchy(Model& model)
	{
		this->skeletonVector.reserve(model.nodes.size());
		for (size_t i = 0; i < model.nodes.size(); i++)
		{
			skeleton tmpSkel;
			this->skeletonVector.push_back(tmpSkel);
		}

		size_t startNodeIndex = 0;

		for (size_t i = startNodeIndex; i < startNodeIndex + this->skeletonVector.size(); i++)
		{
			auto node = model.nodes[i];
			this->skeletonVector[i - startNodeIndex].nodeIndex = (int)i;
			this->skeletonVector[i - startNodeIndex].nodeName = node.name;
			for (size_t j = 0; j < node.children.size(); j++)
			{
				skeletonVector[(size_t)node.children[j] - startNodeIndex].nodeIndex = node.children[j];
				skeletonVector[(size_t)node.children[j] - startNodeIndex].nodeName = model.nodes[(size_t)node.children[j]].name;
				skeletonVector[(size_t)node.children[j] - startNodeIndex].parentIndex = (int)i;
				skeletonVector[(size_t)node.children[j] - startNodeIndex].parentName = node.name;
			}
		}

		skeletonTable.reserve(skeletonVector.size());
		for (size_t i = 0; i < skeletonVector.size(); i++)
		{
			skeleton_table table;

			table.nodeIndex = skeletonVector[i].nodeIndex;
			table.parentIndex = skeletonVector[i].parentIndex;

			memset(table.nodeName, 0, boneContainer::SKELETON_NAME_SIZE);
			strncpy_s(table.nodeName,
				boneContainer::SKELETON_NAME_SIZE,
				skeletonVector[i].nodeName.c_str(),
				boneContainer::SKELETON_NAME_SIZE - 1);

			skeletonTable.push_back(table);
		}

		int maxDepth = -1;
		for (size_t i = 0; i < skeletonTable.size(); i++)
		{
			int start = (int)i;
			int curr = start;
			int count = 0;
			while (curr != -1)
			{
				curr = (int)skeletonTable[(size_t)curr].parentIndex;
				count++;
			}

			if (count > maxDepth)
				maxDepth = count;
		}

		std::vector<std::vector<int>> table;
		for (size_t i = 0; i < skeletonTable.size(); i++)
		{
			std::vector<int> entry;

			int start = (int)i;
			int curr = start;
			int count = 0;
			while (curr != -1)
			{
				entry.push_back(skeletonTable[(size_t)curr].nodeIndex);

				curr = (int)skeletonTable[(size_t)curr].parentIndex;
				count++;
			}

			std::reverse(entry.begin(), entry.end());

			size_t extra = ((size_t)maxDepth - entry.size());
			for (size_t j = 0; j < extra; j++)
				entry.push_back(-1);

			table.push_back(entry);
		}

		std::vector<std::vector<int>> correctedTable;

		for (size_t k = 0; k < model.skins[0].joints.size(); k++)
		{
			size_t i = (unsigned int)model.skins[0].joints[k];
			correctedTable.push_back(table[i]);
		}

		hierarchyData* hData = new hierarchyData(correctedTable.size(), (unsigned int)maxDepth);
		size_t k = 0;
		for (size_t i = 0; i < correctedTable.size(); i++)
		{
			for (size_t j = 0; j < correctedTable[i].size(); j++)
				hData->data[k++] = (unsigned int)correctedTable[i][j];
		}

		return hData;
	}
}

// --- End of File ---
