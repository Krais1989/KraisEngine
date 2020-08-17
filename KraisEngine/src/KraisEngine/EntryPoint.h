#pragma once

#include "KraisEngine/Core/Log.h"
#include "KraisEngine/Core/CApplication.h"

/*
	������� ����� ������
	����������� ������� �������� ���������� Krais::CreateApplication(), ������� ��������� � CApplication.h � ������ ���� ����������� � ����������.
	������ � ���������� ������������ ������ �������� ����� ��������� CApplication, ������� ������������ � ���� ������������� CreateApplication().

	����� �������, � ���������� ���������� ����� �� ����������� main, � ������� ���������� Krais::CreateApplication
*/

#ifdef KE_PLATFORM_WINDOWS


extern KE::CApplication* KE::CreateApplication();

int main(int argc, char** argv) {

	//printf("Krais Entry Point\n");
	KE::Log::Init();
	KE_CORE_INFO("RUNNING");
	KE_CORE_WARN("RUNNING");
	KE_CORE_ERROR("RUNNING");
	
	KE_INFO("RUNNING");
	KE_WARN("RUNNING");
	KE_ERROR("RUNNING");
	
	auto app = KE::CreateApplication();
	app->Run();
	delete app;

	system("\n\npause");
}
#else
#error Krais Engine only support windows
#endif