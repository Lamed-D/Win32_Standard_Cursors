// Windows_Standard_Cursors.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Windows_Standard_Cursors.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSSTANDARDCURSORS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSSTANDARDCURSORS));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSSTANDARDCURSORS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //메뉴바 삭제(코드 개발한 부분)
    wcex.lpszMenuName = 0; //MAKEINTRESOURCEW(IDC_WINDOWSSTANDARDCURSORS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    //윈도우 사이즈 조절 (코드 개발한 부분)
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 440, 550, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//버튼문자열 (코드 개발한 부분)
char IDC_CURSORS[][20] = { "IDC_ARROW","IDC_IBEAM","IDC_WAIT","IDC_CROSS","IDC_UPARROW",
                            "IDC_SIZE","IDC_ICON","IDC_SIZENWSE","IDC_SIZENESW","IDC_SIZEWE",
                            "IDC_SIZENS","IDC_SIZEALL","IDC_NO","IDC_HAND","IDC_APPSTARTING",
                            "IDC_HELP","IDC_PIN","IDC_PERSON" };
//윈도우 창의 커서 (코드 개발한 부분)
HICON SET_IDC_CURSORS = LoadCursor(0, IDC_ARROW);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //바뀌는 커서를 바꾸기위한 무한 루틴
    SetCursor(SET_IDC_CURSORS);
    switch (message)
    {
    //버튼 출력(코드 개발한 부분)
    case WM_CREATE:
        for (int i = 0, j = 0; i < 18; i++)
        {
            CreateWindowA("button", IDC_CURSORS[i], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                (20 + (j * 200)), 20 + ((i - (j * 12)) * 40), 135, 25, hWnd, (HMENU)(i + 1), hInst, NULL);
            if (i == 11)
                j++;
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            //버튼 기능들(코드 개발한 부분)=
            case 1:
                SET_IDC_CURSORS = LoadCursor(0, IDC_ARROW);
                break;
            case 2:
                SET_IDC_CURSORS = LoadCursor(0, IDC_IBEAM);
                break;
            case 3:
                SET_IDC_CURSORS = LoadCursor(0, IDC_WAIT);
                break;
            case 4:
                SET_IDC_CURSORS = LoadCursor(0, IDC_CROSS);
                break;
            case 5:
                SET_IDC_CURSORS = LoadCursor(0, IDC_UPARROW);
                break;
            case 6:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZE);
                break;
            case 7:
                SET_IDC_CURSORS = LoadCursor(0, IDC_ICON);
                break;
            case 8:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZENWSE);
                break;
            case 9:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZENESW);
                break;
            case 10:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZEWE);
                break;
            case 11:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZENS);
                break;
            case 12:
                SET_IDC_CURSORS = LoadCursor(0, IDC_SIZEALL);
                break;
            case 13:
                SET_IDC_CURSORS = LoadCursor(0, IDC_NO);
                break;
            case 14:
                SET_IDC_CURSORS = LoadCursor(0, IDC_HAND);
                break;
            case 15:
                SET_IDC_CURSORS = LoadCursor(0, IDC_APPSTARTING);
                break;
            case 16:
                SET_IDC_CURSORS = LoadCursor(0, IDC_PIN);
                break;
            case 17:
                SET_IDC_CURSORS = LoadCursor(0, IDC_PERSON);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //커서 출력(코드 개발한 부분)

            //실험용 코드들(무시하면 됨)
            //HICON icon = LoadIcon(0, IDC_ARROW);
            //HICON icon = LoadCursor(0, IDC_ARROW);
            //DrawIcon(hdc, 10, 20, icon);
            //ShowCursor(FALSE);

            HICON IDC_CURSORS[20];
            IDC_CURSORS[0] = LoadCursor(0, IDC_ARROW);
            IDC_CURSORS[1] = LoadCursor(0, IDC_IBEAM);
            IDC_CURSORS[2] = LoadCursor(0, IDC_WAIT);
            IDC_CURSORS[3] = LoadCursor(0, IDC_CROSS);
            IDC_CURSORS[4] = LoadCursor(0, IDC_UPARROW);
            IDC_CURSORS[5] = LoadCursor(0, IDC_SIZE);
            IDC_CURSORS[6] = LoadCursor(0, IDC_ICON);
            IDC_CURSORS[7] = LoadCursor(0, IDC_SIZENWSE);
            IDC_CURSORS[8] = LoadCursor(0, IDC_SIZENESW);
            IDC_CURSORS[9] = LoadCursor(0, IDC_SIZEWE);
            IDC_CURSORS[10] = LoadCursor(0, IDC_SIZENS);
            IDC_CURSORS[11] = LoadCursor(0, IDC_SIZEALL);
            IDC_CURSORS[12] = LoadCursor(0, IDC_NO);
            IDC_CURSORS[13] = LoadCursor(0, IDC_HAND);
            IDC_CURSORS[14] = LoadCursor(0, IDC_APPSTARTING);
            IDC_CURSORS[15] = LoadCursor(0, IDC_HELP);
            IDC_CURSORS[16] = LoadCursor(0, IDC_PIN);
            IDC_CURSORS[17] = LoadCursor(0, IDC_PERSON);

            for (int i = 0, j = 0; i < 18; i++)
            {
                DrawIcon(hdc, (165 + (j * 200)), 20 + ((i - (j * 12)) * 40), IDC_CURSORS[i]);
                if (i == 11)
                    j++;
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
