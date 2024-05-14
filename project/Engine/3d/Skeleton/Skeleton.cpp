#include "Skeleton.h"
#include "Model.h"

void Skeleton::Update(SkeletonData& skeleton)
{
	
}

int32_t Skeleton::CreateJoint(const Node& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints)
{
	Joint joint;
	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = MakeIdentity4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size()); // 現在登録されてる数をIndexに
	joint.parent = parent;
	joints.push_back(joint); // SkeletonのJoint列に追加
	for (const Node& child : node.children) {
		// 子Indexを作成し、そのIndexを尊く
		int32_t childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].chaidren.push_back(childIndex);
	}
	// 自身のIndexを返す
	return joint.index;
}

SkeletonData Skeleton::CreateSkeleton(const Node& rootNode)
{
	SkeletonData skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);

	// 名前とindexのマッピングを行いアクセスしやすくする
	for (const Joint& joint : skeleton.joints) {
		skeleton.jointMap.emplace(joint.name, joint.index);
	}
	return skeleton;
}
