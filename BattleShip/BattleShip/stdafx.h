// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <string>
#include <time.h>
#include <vector>
#include <stack>
#include <conio.h>
#include "Network.h"
#include "PacketType.h"
#include "ShipData.h"
#include <Windows.h>
#include <crtdbg.h>

#ifdef _DEBUG
//#include <vld.h>
#pragma comment(lib, "BGNL_debug.lib")
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#else
#pragma comment(lib, "BGNL.lib")
#endif