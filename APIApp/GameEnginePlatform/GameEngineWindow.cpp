#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>



HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;

//The pixel aspect ratio of both consoles is 8:7
//GameEngineWindow::SettingWindowSize({ 720.0f, (720.0f / 800.0f) * 700.0f });

float4 GameEngineWindow::WindowSize = { 720, 630 };         //window 크기
float4 GameEngineWindow::WindowPos = { 80, 80 };            //window 위치
float4 GameEngineWindow::ScreenSize = { 720, 630 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;
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
    //키보드의 포커스가 이돌될 때 함수 실행
    //메시지를 받은 시점은 이미 포커스 이동이 완료된 후
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    //윈도우 활성화 | 비활성화
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
        //애플리케이션 종료 및 메시지 루프 중단을 위함
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

    //윈도우가 만들어지면서 부터 생성된 색상 2차원 배열의 수정권한을 받음
    WindowBackBufferHdc = GetDC(HWnd);

    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    //크기 변경 후 가져옴
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // 단축키
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg;                                                    //MSG 구조체


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
            // 동기 메세지 존재 여부 관계X 진행
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // 메세지가 있을때도 게임을 실행
            if (nullptr != _Loop)
            {
                _Loop();
            }
            continue;
        }

        // 데드타임
        // 데드타임에 게임을 실행하는것. 
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
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    //윈도우의 타이틀바와 프레임까지 고려해서 크기를 설정해줘야 함

    //         위치      크기
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    //원하는 크기를 넣으면 타이틀바까지 고려한 크기를 리턴하는 함수
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };

    //0을 넣어주면 기존의 크기를 유지
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);
}

void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
