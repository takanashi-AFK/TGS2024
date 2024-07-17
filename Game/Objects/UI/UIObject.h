#pragma once
#include <vector>
#include "../../../Engine/Json/JsonReader.h"
#include "../../../../../Engine/GameObject/Transform.h"
#include "../../../../../Engine/Collider/BoxCollider.h"
#include "../../../../../Engine/Collider/SphereCollider.h"


using std::vector;

enum UIType {
	UI_NONE,
	UI_BUTTON,
	UI_IMAGE,
	UI_TEXT,
	UI_PANEL,
	UI_PROGRESSBAR,
	UI_MAX,
};

class UIObject
{
private:
	bool isPositionLocked_;
	bool isRotateLocked_;
	bool isScaleLocked_;

protected:
	std::string objectName_; // ƒIƒuƒWƒFƒNƒg–¼
	Transform transform_; // ˆÊ’u‚âŒü‚«‚È‚Ç‚ðŠÇ—‚·‚éƒIƒuƒWƒFƒNƒg
	bool isEnable_;	// —LŒø‚©‚Ç‚¤‚©
	UIType type_;	// UI‚ÌŽí—Þ
	int layerNumber_; // ƒŒƒCƒ„[”Ô†
	std::vector<UIObject*> childList_;  // ŽqƒIƒuƒWƒFƒNƒg‚ÌƒŠƒXƒg
	UIObject* pParent_;// eƒIƒuƒWƒFƒNƒg

	//ƒtƒ‰ƒO
	struct UI_STATE
	{
		unsigned initialized : 1;	//‰Šú‰»Ï‚Ý‚©
		unsigned entered : 1;		//XV‚·‚é‚©
		unsigned visible : 1;		//•`‰æ‚·‚é‚©
		unsigned dead : 1;			//íœ‚·‚é‚©
	};
	UI_STATE state_;

public:

	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	UIObject();
	UIObject(UIObject* parent);
	UIObject(string _name, UIType _type, UIObject* parent, int _layerNum);

	//ƒfƒXƒgƒ‰ƒNƒ^
	virtual ~UIObject();

	//ŠeƒIƒuƒWƒFƒNƒg‚Å•K‚¸ì‚éŠÖ”
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Release() {};

	//Ž©•ª‚ÌŠY“–ŠÖ”‚ð“Ç‚ñ‚¾ŒãAŽq‹Ÿ‚ÌŠÖ”‚àŒÄ‚Ô
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	bool IsDead(); //íœ‚·‚é‚©‚Ç‚¤‚©


	virtual void Save(json& saveObj) {};
	virtual void Load(json& loadObj) {};
	virtual void DrawData() {};
	  
	void ChildSave(json& _saveObj);
	void ChildLoad(json& _loadObj);
	void ChildDrawData();

	void KillMe();	// Ž©•ª‚ðíœ‚·‚é

	//–¼‘O‚ÅƒIƒuƒWƒFƒNƒg‚ðŒŸõi‘ÎÛ‚ÍŽ©•ª‚ÌŽq‹ŸˆÈ‰ºj
	//ˆø”Fname	ŒŸõ‚·‚é–¼‘O
	//–ß’lFŒ©‚Â‚¯‚½ƒIƒuƒWƒFƒNƒg‚ÌƒAƒhƒŒƒXiŒ©‚Â‚©‚ç‚È‚¯‚ê‚Înullptrj
	UIObject* FindChildObject(const std::string& name);
	UIObject* FindObject(const std::string& name){ return GetRootJob()->FindChildObject(name); }


	//ƒIƒuƒWƒFƒNƒg‚Ì–¼‘O‚ðŽæ“¾
	//–ß’lF–¼‘O
	const std::string& GetObjectName(void) const;

	//RootƒIƒuƒWƒFƒNƒg‚ðŽæ“¾(UIPanel)
	UIObject* GetRootJob();

	//eƒIƒuƒWƒFƒNƒg‚ðŽæ“¾
	UIObject* GetParent();

	/// <summary>
	/// ŽqƒIƒuƒWƒFƒNƒg‚ð’Ç‰Á(ƒŠƒXƒg‚ÌÅŒã‚Ö)
	/// </summary>
	/// <param name="obj"></param>
	void PushBackChild(UIObject* obj);

	/// <summary>
	/// V‚µ‚¢ƒŒƒCƒ„[”Ô†‚ðÝ’è
	/// </summary>
	/// <param name="newLayerNumber_">V‚µ‚¢ƒŒƒCƒ„[”Ô†</param>
	void SetLayerNumber(int newLayerNumber_);
	// Getter
	int GetLayerNumber() { return layerNumber_; }

	/// <summary>
	/// ƒŒƒCƒ„[‚ªd•¡‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
	/// </summary>
	/// <param name="newLayerNumber_"></param>
	/// <returns></returns>
	bool IsLayerNumberDuplicate(int newLayerNumber_);

	//ƒIƒuƒWƒFƒNƒg‚ðƒŒƒCƒ„[”Ô†‚Å”äŠr‚·‚é‚½‚ß‚ÌŠÖ”
	static bool CompareLayerNumber(UIObject* _object1, UIObject* _object2);

	void LockPosition() { isPositionLocked_ = true; }
	void LockRotate() { isRotateLocked_ = true; }
	void LockScale() { isScaleLocked_ = true; }

	void UnlockPosition() { isPositionLocked_ = false; }
	void UnlockRotate() { isRotateLocked_ = false; }
	void UnlockScale() { isScaleLocked_ = false; }
};

UIObject* CreateUIObject(string _name, UIType _type, UIObject* _parent, int _layerNum);
string GetUITypeString(UIType _type);

