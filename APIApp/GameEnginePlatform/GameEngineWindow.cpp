#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::DrawHdc = nullptr;

//옛날 게임 비율_4:3
float4 GameEngineWindow::WindowSize = { 800, 600 };         //window 크기
float4 GameEngineWindow::WindowPos = { 100, 100 };          //window 위치
float4 GameEngineWindow::ScreenSize = { 800, 600 };

//윈도우 업데이트 체크 여부
bool IsWindowUpdate = true;


LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    //마우스 움직임
    case WM_MOUSEMOVE:
    {
        int a = 0;
        break;
    }
    // 내 윈도우 선택
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    //내 윈도우가 선택되지 않음
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    //윈도우 종료
    case WM_DESTROY:
    {
        //Message함수가 0을 리턴
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

//윈도우 생성하는 함수(창 띄움)
void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    //윈도우를 찍어낼수 있는 class를 만들어내는 용도
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;

    //넣어주지 않으면 윈도우 기본Icon
    wcex.hIcon = nullptr;                               //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    // 흰색 
    wcex.lpszMenuName = nullptr;                        //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;                             //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 윈도우에게 이런 내용을 window클래스를 GameEngineWindowDefault라는 이름으로 등록해줘.
    // 나중에 윈도우 만들때 쓸꺼냐.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }


    // 만약 1000번 프로그램이 윈도우를 띄워달라고 요청하면
    // 윈도우는 다시 특정 숫자를 가진 윈도우가 만들어졌다고 알려주는데.
    // 특정 숫자로 인식되는 우리의 윈도우에게 크기 변경 떠라

    //옵션
    // (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    DrawHdc = GetDC(HWnd);

    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    return;
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // 단축키
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg;


    // 기본 메시지 루프
    // GetMessage:  윈도우의 특별한 일이 생길 때까지 멈추는 함수
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // 윈도우 메세지 처리
        // GetMessage함수: 동기 함수(함수가 종료될 때까지 프로그램이 멈춤)
        // 윈도우에 무슨 일이 발생하면 리턴되는 함수
        // 윈도우에 무슨일이 생기게 만들어야 함
        // => 게임은 쉴새없이 돌아야 하므로 내가 메세지를 줄때까지 멈추면 안 됨
        if (GetMessage(&msg, nullptr, 0, 0))
        {
            if (nullptr != _Loop)
            {
                _Loop();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    //윈도우의 타이틀바와 프레임까지 고려해서 크기를 설정해줘야 함

    //         위치      크기
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // 내가 원하는 크기를 넣으면 타이틀바까지 고려한 크기를 리턴주는 함수
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };

    // 0을 넣어주면 기존의 크기를 유지
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

