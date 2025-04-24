// SoftwareRenderer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "SoftwareRenderer.h"
#include "MatrixUtils.h"
#include "ParsingFile.h"
#include "Rasterizer.h"
#include "Matrix4x4.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Quaternion.h"
#include "Mesh.h"
#include "Clipper.h"

using namespace std;

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;
HDC hdc;

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
    LoadStringW(hInstance, IDC_SOFTWARERENDERER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOFTWARERENDERER));

    Matrix4x4 view;
    Matrix4x4 projection;
    Matrix4x4 tmpModel;
    Shader shader;
    string o_dragon = "./resources/dragon.obj";
    string o_skull = "./resources/skull.obj";
    string o_teapot = "./resources/teapot.obj";
    ParsingFile file(o_dragon);
    
    cout << "pasring finish" << endl;

    RECT client_rect;
    GetClientRect(hWnd, &client_rect);
    int width = client_rect.right - 1;
    int height = client_rect.bottom - 1;
    float ratio = static_cast<float>(width) / static_cast<float>(height);
    MatrixUtils::modelMatrix(tmpModel, Vector3(0, 0, 0), 
        Quaternion(Vector3(0, 1, 0), 0), Vector3(1, 1, 1));
    MatrixUtils::perspectiveMatrix(projection, 60, ratio, 0.1, 500);
    MatrixUtils::viewMatrix(view, Vector3(0, 5, -13), Vector3(0, 0, 1));
    shader.setModelMatrix(tmpModel);
    shader.setProjectionMatrix(projection);
    shader.setViewMatrix(view);
    Clipper clipper;

    RenderTexture render_target(width, height);
    Rasterizer rasterizer(width, height);
    rasterizer.setTarget(&render_target);
    Mesh mesh(file.getTrianglesSize());

    /*for (int i = 0; i < file.getTrianglesSize(); i++)
        mesh.get(i) = file.getTrianglesFactor(i);*/
    
    {
        MatrixUtils::viewMatrix(view, Vector3(0, 0, -3), Vector3(0, 0, 1));
        shader.setViewMatrix(view);
        mesh.setTestVertices();
        //mesh.setTestTriangle();
        //mesh.setTestOverlapVertices();
    }
    rasterizer.draw(mesh, mesh.getSize(), &shader, &clipper);

    hdc = GetDC(hWnd);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector4 color = render_target.pixelColor(x, y);
            SetPixel(hdc, x, y, RGB(color.x * 255, color.y * 255, color.z * 255));
        }
    }
    ReleaseDC(hWnd, hdc);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOFTWARERENDERER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOFTWARERENDERER);
    wcex.lpszClassName  = L"SoftwareRasterizer";
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

   RECT windowRect = { 0, 0, 800, 650};
   hWnd = CreateWindowW(L"SoftwareRasterizer", L"SoftwareRasterizer",
       WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
       CW_USEDEFAULT, 0, windowRect.right - windowRect.left,
       windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
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
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
