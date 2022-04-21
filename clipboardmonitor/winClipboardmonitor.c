#include <windows.h>
#include "winClipboardmonitor.h"
#include <stdbool.h>
#include <stdio.h>
HWND cbvhandle;
LRESULT CALLBACK WinProc(HWND   hWnd, UINT   message, WPARAM wParam, LPARAM lParam){
   
   switch(message)
    {
        case WM_CREATE:
       
            break;
        case WM_CLOSE:
           
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            ChangeClipboardChain(hWnd, cbvhandle);
            PostQuitMessage(0);
            break;
       
        case WM_SHOWWINDOW :
            ShowWindow(hWnd,1);
            break;
        case WM_DRAWCLIPBOARD :;
            WINBOOL cbopened=OpenClipboard(NULL);
             if (cbopened){
                 
                    HANDLE cbdatahanle = GetClipboardData(CF_TEXT);
                    if (cbdatahanle){
                        char * cbdata = (char*)GlobalLock(cbdatahanle);
                        if (cbdata){
                            
                            GoClipboardDataChangedEvent(cbdata);
                            GlobalUnlock(cbdatahanle);
                        }
                    }
                    CloseClipboard();
             }
                
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND StartClipBoardMonitor(){
    WNDCLASSEX winclassex;
    HINSTANCE hModule= GetModuleHandleW(0);
    winclassex.cbSize = sizeof(winclassex);
    winclassex.style = CS_HREDRAW | CS_VREDRAW;
    winclassex.lpfnWndProc = WinProc;
    winclassex.cbClsExtra=0;
    winclassex.cbWndExtra=0;
    winclassex.hInstance = hModule;
    winclassex.hIcon = LoadIcon(winclassex.hInstance, IDI_APPLICATION);
    winclassex.hIconSm = LoadIcon(winclassex.hInstance, IDI_APPLICATION);
    winclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclassex.hbrBackground =(HBRUSH)(COLOR_WINDOW+1);
    winclassex.lpszMenuName = NULL;
    winclassex.lpszClassName = "CLIPBOARDMONITORGUI";

    if (!RegisterClassEx(&winclassex)){
        return NULL;	   
    }
    HWND hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,"CLIPBOARDMONITORGUI", "CLIPBOARDMONITORGUI", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT,200,200,NULL,NULL,hModule,NULL);
    if (hwnd==NULL){
        return NULL;

    }
    ShowWindow(hwnd,0);
    UpdateWindow(hwnd);
    cbvhandle= SetClipboardViewer(hwnd);
    
    MSG msg;
    while (GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return hwnd;
}

