#pragma once


/*
	������� ����� ������
	����������� ������� �������� ���������� Krais::CreateApplication(), ������� ��������� � CApplication.h � ������ ���� ����������� � ����������.
	������ � ���������� ������������ ������ �������� ����� ��������� CApplication, ������� ������������ � ���� ������������� CreateApplication().

	����� �������, � ���������� ���������� ����� �� ����������� main, � ������� ���������� Krais::CreateApplication
*/

#ifdef KRAIS_PLATFORM_WINDOWS

extern Krais::CApplication* Krais::CreateApplication();

int main(int argc, char** argv) {
	printf("Krais Entry Point\n");
	auto app = Krais::CreateApplication();
	app->Run();
	delete app;
}
#else
#error Krais Engine only support windows
#endif