#include <windows.h>

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) { //���ڴ����� 
	switch(Message) {
		case WM_CREATE:
			//�ö����� 
			SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//������Ϣ�� 
	//MessageBox(NULL,"Test MassageBox","Test MassageBox",MB_YESNO | MB_ICONINFORMATION);
	/*
	MessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UNIT uType)
	����������
	HWND�����ھ������    lpText��������Ϣ�ı�    lpCaption�����������ı�    uType��ͼ�갴ť��� 
	*/
	wchar_t szAppClassName[] = L"GDATest";
	
	//����Ӧ�� 
	//1.��ƴ�����
	/*typedef struct tagWNDCLASSW {   //WNDCLASS��ԭ�ͺͶ��� 
    UINT        style;
    WNDPROC     lpfnWndProc;  //���ڴ���������ͷ�� 
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
} WNDCLASSW, *PWNDCLASSW, NEAR *NPWNDCLASSW, FAR *LPWNDCLASSW;*/
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //���Ͻ�ͼ�� 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(51,85,159));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppClassName;
	
	//2.ע�ᴰ���� 
	if(FALSE == RegisterClass(&wc))
	{
		MessageBox(NULL,"Error!\nPlease check again.","Test Waring",MB_YESNO | MB_ICONINFORMATION);
		return 0;
	}
	
	//3.��������
	HWND hWnd = CreateWindow(
		szAppClassName,  //���������� 
		"Test Program", //������
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,  //���ڷ�� 
		200,  //���ں����� 
		200,  //���������� 
		800,  //���ڿ� 
		600,  //���ڸ�
		NULL, //������
		NULL, //�˵����
		hInstance,  //��ǰ����ʵ�����
		NULL  //���Ӳ��� 
	);
	
	//4.��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	
	//5.���´���
	UpdateWindow(hWnd);
	MSG msg;
	//6.��Ϣѭ��
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		//����Ϣת���ͷַ�
		DispatchMessage(&msg); 
	}
	
	 
	
	return 0; 
}

