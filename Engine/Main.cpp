
//
//�@�ŏI�X�V���F2023/10/20
//

#include <Windows.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "global.h"
#include "GameObject/RootObject.h"
#include "../Game/Objects/UI/UIPanel.h"
#include "../Game/Otheres/GameEditor.h"
#include "ResourceManager/Model.h"
#include "ResourceManager/Image.h"
#include "GameObject/Camera.h"
#include "DirectX/Input.h"
#include "ResourceManager/Audio.h"
#include "../Game/Otheres/AudioController.h"
#include "ResourceManager/VFX.h"
#include "ResourceManager/Transition.h"
#include "../Game/Otheres/OptionMenu.h"

// effekseer�̃w�b�_�[���C���N���[�h

#include "../EffekseeLib/EffekseerVFX.h"/*������*/


// ImGui�̃w�b�_�[���C���N���[�h
#include "ImGui/imgui.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib,"Winmm.lib")

RECT windowRect = {};  // ���̃E�B���h�E�T�C�Y��ۑ�
//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";	//�E�B���h�E�N���X��

//�v���g�^�C�v�錾
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void ToggleFullScreen(HWND hWnd, bool& isFullScreen, RECT& windowRect);

// �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif

	srand((unsigned)time(NULL));
	SetCurrentDirectory("Assets");

	//�������t�@�C���isetup.ini�j����K�v�ȏ����擾
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//�X�N���[���̕�
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//�X�N���[���̍���
	int fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");				//FPS�i��ʍX�V���x�j
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");		//�L���v�V�����Ɍ��݂�FPS��\�����邩�ǂ���

	//�E�B���h�E���쐬
	HWND hWnd = InitApp(hInstance, screenWidth, screenHeight, nCmdShow);

	//Direct3D����
	Direct3D::Initialize(hWnd, screenWidth, screenHeight);

	//ImGui����
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(Direct3D::pDevice_, Direct3D::pContext_);

	// �E�B���h�E�̐F��ύX����
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.f); // RGBA�Ŏw��
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.3f, 0.5f, 1.0f); // RGBA�Ŏw��
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.2f, 0.3f, 1.0f); // RGBA�Ŏw��
		//style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.1f, 0.5f, 1.0f); // RGBA�Ŏw��
	}

	//�J����������
	Camera::Initialize();

	//���͏����i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�̏���
	Input::Initialize(hWnd);

	//�I�[�f�B�I�i���ʉ��j�̏���
	Audio::Initialize();

	//�g�����W�V�����̏�����
	Transition::Initialize();

	// effekseer�̏�����
	EFFEKSEERLIB::gEfk = new EFFEKSEERLIB::EffekseerManager;/*������*/
	EFFEKSEERLIB::gEfk->Initialize(Direct3D::pDevice_,Direct3D::pContext_);/*������*/


	//���[�g�I�u�W�F�N�g����
	//���ׂẴQ�[���I�u�W�F�N�g�̐e�ƂȂ�I�u�W�F�N�g
	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();

	//UIPanel�̃C���X�^���X�擾�Ə�����
	UIPanel* pUIPanel_ = UIPanel::GetInstance();
	pUIPanel_->Initialize();




	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����i���������D��j
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ��i�����ŃQ�[���̏����j
		else
		{
			//���Ԍv��
			timeBeginPeriod(1);	//���Ԍv���̐��x���グ��
			static int FPS = 0;								//��ʍX�V�񐔂̃J�E���^
			static DWORD lastFpsResetTime = timeGetTime();	//�Ō�ɃL���v�V������FPS��\������
			static DWORD lastUpdateTime = timeGetTime();	//�Ō�ɉ�ʂ��X�V��������
			DWORD nowTime = timeGetTime();					//���݂̎���


			//�L���v�V�����Ɍ��݂�FPS��\������
			if (isDrawFps)
			{
				//1�b�i1000�~���b�j�o������
				if (nowTime - lastFpsResetTime > 1000)
				{
					//FPS�̒l��\��
					char string[16];
					wsprintf(string, "FPS:%d", FPS);
					SetWindowText(GetActiveWindow(), string);
					FPS = 0;
					lastFpsResetTime = nowTime;
				}
			}

			// �O��̃t���[������̌o�ߎ��Ԃ��v�Z
			float deltaTime = (nowTime - lastUpdateTime);/*������*/

			//�w�肵�����ԁiFPS��60�ɐݒ肵���ꍇ��60����1�b�j�o�߂��Ă�����X�V����
			if (deltaTime * fpsLimit > 1000.0f)
			{
				//���Ԍv���֘A
				lastUpdateTime = nowTime;	//���݂̎��ԁi�Ō�ɉ�ʂ��X�V�������ԁj���o���Ă���
				FPS++;						//��ʍX�V�񐔂��J�E���g����


				//���́i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�����X�V
				Input::Update();

				if (Input::IsKeyDown(DIK_F4)) {
					// ��ʕ\���ؑ�
					ToggleFullScreen(hWnd, Direct3D::isFullScreen_, windowRect);
				}

				if (Input::IsKeyDown(DIK_ESCAPE)) {
					// �I�v�V�������j���[���J��
					OptionMenu::isOptionMenu = !OptionMenu::isOptionMenu;
				}

				//ImGui�̍X�V
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				// ImGui�ŕ\������E�B���h�E�̐ݒ���s��
				ImGui::SetNextWindowPos(ImVec2(0, Direct3D::screenHeight_ ));
				ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_, Direct3D::screenHeight_));

				// �E�B���h�E��\��
				ImGui::Begin("Debug", NULL,
					ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				if(!OptionMenu::isOptionMenu){
					//�S�I�u�W�F�N�g�̍X�V����
					//���[�g�I�u�W�F�N�g��Update���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
					pRootObject->UpdateSub();

					pUIPanel_->UpdateSub();

					// �I�[�f�B�I�̍X�V
					AudioController::Update(pRootObject);

					//�J�������X�V
					Camera::Update();

					// effekseer�̍X�V
					EFFEKSEERLIB::gEfk->Update(deltaTime / 1000.f);/*������*/

					// �����搶�쐬�G�t�F�N�g�̍X�V
					// VFX::Update();

					//�g�����W�V�����̍X�V
					Transition::Update();

					//���̃t���[���̕`��J�n
					Direct3D::BeginDraw();

					//�S�I�u�W�F�N�g��`��
					//���[�g�I�u�W�F�N�g��Draw���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
					pRootObject->DrawSub();

					pUIPanel_->DrawSub();

					// effekseer�̕`��
					EFFEKSEERLIB::gEfk->Draw();/*������*/
					
					// �����搶�쐬�G�t�F�N�g�̕`��
					// VFX::Draw();

					//�g�����W�V�����̕`��
					Transition::Draw();

				}
				else {
					OptionMenu::Draw(pRootObject);
				}
			

				ImGui::End();


				//ImGui�̕`��
				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

				//�`��I��
				Direct3D::EndDraw();



			
			
				//������Ƌx�܂���
				Sleep(1);
			}
			timeEndPeriod(1);	//���Ԍv���̐��x��߂�
		}
	}

	//ImGui�I������
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	//���낢����
	Transition::Release();
	VFX::Release();
	Audio::AllRelease();
	Model::AllRelease();
	Image::AllRelease();
	pRootObject->ReleaseSub();
	pUIPanel_->ReleaseSub();
	SAFE_DELETE(pRootObject);
	Direct3D::Release();

	return 0;
}


//�E�B���h�E�̍쐬
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;						//�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;				//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;						//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;				//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//�A�C�R��
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	//�������A�C�R��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//�}�E�X�J�[�\��
	wc.lpszMenuName = nullptr;						//���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�w�i�i���j
	RegisterClassEx(&wc);

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//�^�C�g���o�[�ɕ\��������e
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,					//�E�B���h�E�N���X��
		caption,						//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,		//�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,					//�\���ʒu���i���܂����j
		CW_USEDEFAULT,					//�\���ʒu��i���܂����j
		winRect.right - winRect.left,	//�E�B���h�E��
		winRect.bottom - winRect.top,	//�E�B���h�E����
		nullptr,						//�e�E�C���h�E�i�Ȃ��j
		nullptr,						//���j���[�i�Ȃ��j
		hInstance,						//�C���X�^���X
		nullptr							//�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);


//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//�E�B���h�E�����
	case WM_DESTROY:
		PostQuitMessage(0);	//�v���O�����I��
		return 0;

	//�}�E�X��������
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// �t���X�N���[�����[�h�ƃE�B���h�E���[�h��؂�ւ���֐�
void ToggleFullScreen(HWND hWnd, bool& isFullScreen, RECT& windowRect) {
	if (isFullScreen) {
		// �E�B���h�E���[�h�ɖ߂�
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW); 
		SetWindowPos(hWnd, HWND_NOTOPMOST, windowRect.left, windowRect.top,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else {
		// �t���X�N���[���ɐ؂�ւ�
		GetWindowRect(hWnd, &windowRect);  // ���̃E�B���h�E�T�C�Y��ۑ�
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
		MONITORINFO mi = { sizeof(mi) };
		if (GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowPos(hWnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	}
	isFullScreen = !isFullScreen;  // �t���X�N���[����Ԃ𔽓]
}
