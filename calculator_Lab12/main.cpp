#include <Windows.h>
#include <string>
#include "resource.h"

using namespace std;
HINSTANCE hInstance;
HWND resultText,Operand1,Operand2;
const UINT MAX_SIZE = 10;

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	::hInstance = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	case WM_INITDIALOG:
		resultText = GetDlgItem(hwnd, IDC_RESULT);
		Operand1 = GetDlgItem(hwnd, IDC_EDIT1);
		Operand2 = GetDlgItem(hwnd, IDC_EDIT2);
		SendDlgItemMessage(hwnd, IDC_RADIO1, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1 && HIWORD(wParam) == BN_CLICKED) {
			WCHAR op1[MAX_SIZE];
			WCHAR op2[MAX_SIZE];
			GetWindowText(Operand1, op1, MAX_SIZE);
			GetWindowText(Operand2, op2, MAX_SIZE);
			for (size_t i = 0; op1[i]!=0; i++)
			{
				if (op1[i] <'0' || op1[i] > '9')
				{
					MessageBox(hwnd, L"ERROR", 0, 0);
					return TRUE;
				}
			}
			for (size_t i = 0; op2[i] != 0; i++)
			{
				if (op2[i] < '0' || op2[i] > '9')
				{
					MessageBox(hwnd, L"ERROR", 0, 0);
					return TRUE;
				}
			}
			long intOp1 = wcstol(op1, NULL, MAX_SIZE);
			long intOp2 = wcstol(op2, NULL, MAX_SIZE);
			long double result;
			LRESULT operation = SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0);
			if (operation == BST_CHECKED)
				result = intOp1 + intOp2;
			else
			{
				operation = SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
				if (operation == BST_CHECKED)
					result = intOp1 - intOp2;
				else
				{
					operation = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
					if (operation == BST_CHECKED)
						result = intOp1 * intOp2;
					else if (intOp2 == 0)
					{
						MessageBox(hwnd, L"ERROR", 0, 0);
						return true;
					}
					else
						result = intOp1 / intOp2;
				}
			}
			SetWindowText(resultText, to_wstring(result).c_str());
		}
		return TRUE;
	}
	return FALSE;
}