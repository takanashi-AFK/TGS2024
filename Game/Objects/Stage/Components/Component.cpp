#include "Component.h"
#include"../../../../Engine/ImGui/imgui.h"
#include"../StageObject.h"

Component::Component(StageObject* _holder, string _name, ComponentType _compType, Component* _compParent)
{
}

Component::Component(StageObject* _holder, string _name, ComponentType _compType)
{
}



void Component::OnCollision(GameObject* _target, Collider* _collider)
{
	this->OnCollision(_target, _collider);
}

void Component::Save(json& _saveObj)
{
	this->Save(_saveObj);
}

void Component::Load(json& _loadObj)
{
	this->Load(_loadObj);
}

void Component::DrawImgui()
{
	if (ImGui::TreeNode(this->componentname_.c_str())) {
		ImGui::SameLine();

		if (ImGui::SmallButton("Delete")) {
			holder_->DeleteComponent(this);
		}

		this->DrawImgui();

		ImGui::TreePop();
	}



}

void Component::ChildInitialize()
{
	this->Initialize();

	/*for (auto comp : childComponent_) {
		comp->ChildInitialize();
	}*/
}

void Component::ChildUpdate()
{
	this->Update();

	/*for (auto comp : childComponent_) {
		comp->ChildUpdate();
	}*/
}

void Component::ChildRelease()
{
	this->Release();

}

//void Component::ChildOnCollision(GameObject* _childtarget, Collider* _childcollider)
//{
//}
//
//void Component::ChildSave(json& _childsaveObj)
//{
//}
//
//void Component::ChildLoad(json& _childloadObj)
//{
//}
//
//void Component::ChildDrawImgui()
//{
//}
//
//bool Component::AddChildComponent(Component* _childComp)
//{
//	
//}
//
//bool Component::DeleteChildComponent(string _childComp)
//{
//	return false;
//}
//
//bool Component::FindChildComponent(string _childComp)
//{
//	return false;
//}
//
//Component* Component::GetChildComponent(string _compname)
//{
//	return nullptr;
//}

//vector<Component*> Component::GetChildComponent(ComponentType _comptype)
//{
//
//	/*vector<Component*>compresult;
//	for (auto comp : childComponent_) {
//
//	}*/
//}

//Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder, Component* _parent)
//{
//	return nullptr;
//}


//Component* CreateComponent(string _name, ComponentType _type, StageObject* _holder)
//{
//	return nullptr;
//}

//string ComponentTypeToString(ComponentType _comptype)
//{
//	return string();
//}


