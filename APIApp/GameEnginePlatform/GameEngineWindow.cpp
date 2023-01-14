#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;


float4 GameEngineWindow::WindowSize = { 800, 600 };         //window ũ��
float4 GameEngineWindow::WindowPos = { 100, 100 };          //window ��ġ
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;


//������ ������Ʈ üũ ����
bool IsWindowUpdate = true;


LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    //���콺 ������
    case WM_MOUSEMOVE:
    {
        int a = 0;
        break;
    }
    //Ű������ ��Ŀ���� �̵��� �� �Լ� ����
    //�޽����� ���� ������ �̹� ��Ŀ�� �̵��� �Ϸ�� ��
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    //������ Ȱ��ȭ | ��Ȱ��ȭ
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    //�� �����찡 ���õ��� ����
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    //������ ����
    case WM_DESTROY:
    {
        //Message�Լ��� 0�� ����
        //���ø����̼� ���� �� �޽��� ���� �ߴ��� ����
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow() 
{
}

GameEngineWindow::~GameEngineWindow() 
{
}

//������ �����ϴ� �Լ�(â ���)
void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    //�����츦 ���� �ִ� class�� ������ �뵵
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;

    //�־����� ������ ������ �⺻Icon
    wcex.hIcon = nullptr;                               //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // ��� 
    wcex.lpszMenuName = nullptr;                        //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;                             //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // �����쿡�� �̷� ������ windowŬ������ GameEngineWindowDefault��� �̸����� �������.
    // ���߿� ������ ���鶧 ������.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }


    // ���� 1000�� ���α׷��� �����츦 ����޶�� ��û�ϸ�
    // ������� �ٽ� Ư�� ���ڸ� ���� �����찡 ��������ٰ� �˷��ִµ�.
    // Ư�� ���ڷ� �νĵǴ� �츮�� �����쿡�� ũ�� ���� ����

    //�ɼ�
    // (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    //�����찡 ��������鼭 ���� ������ ���� 2���� �迭�� ���������� ����
    WindowBackBufferHdc = GetDC(HWnd);

    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    //ũ�� ���� �� ������
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // ����Ű
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg;                                                    //MSG ����ü


    // �⺻ �޽��� ����
    // GetMessage:  �������� Ư���� ���� ���� ������ ���ߴ� �Լ�
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // ������ �޼��� ó��
        // GetMessage�Լ�: ���� �Լ�(�Լ��� ����� ������ ���α׷��� ����)
        // �����쿡 ���� ���� �߻��ϸ� ���ϵǴ� �Լ�
        // �����쿡 �������� ����� ������ ��
        // => ������ �������� ���ƾ� �ϹǷ� ���� �޼����� �ٶ����� ���߸� �� ��
      /*  if (GetMessage(&msg, nullptr, 0, 0))
        {
            if (nullptr != _Loop)
            {
                _Loop();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }*/
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            // ���� �޼��� ���� ���� ����X ����
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // �޼����� �������� ������ ����
            if (nullptr != _Loop)
            {
                _Loop();
            }
            continue;
        }

        // ����Ÿ��
        // ����Ÿ�ӿ� ������ �����ϴ°�. 
        if (nullptr != _Loop)
        {
            _Loop();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    if (nullptr != BackBufferImage)
    {

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    //�������� Ÿ��Ʋ�ٿ� �����ӱ��� ����ؼ� ũ�⸦ ��������� ��

    //         ��ġ      ũ��
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    //���ϴ� ũ�⸦ ������ Ÿ��Ʋ�ٱ��� ����� ũ�⸦ �����ϴ� �Լ�
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };

    //0�� �־��ָ� ������ ũ�⸦ ����
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

