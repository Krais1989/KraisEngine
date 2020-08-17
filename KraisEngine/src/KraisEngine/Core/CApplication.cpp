#include <ke_pch.h>

#include "CApplication.h"

namespace KE {
	CApplication::CApplication()
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Update(float dt_sec)
	{

	}

	void CApplication::Run()
	{
		/*
			������������ ������� ���� (lag). ��� ���������� ������������� �������� (maxLag) ����� ����������� ����������
			���������� fps
		*/

		using clock = std::chrono::high_resolution_clock;

		auto lastTime = clock::now();			// ���������� ���������� ���������� ������
		auto lag = std::chrono::nanoseconds(0);	// ������� ����

		double maxFps = 60;											// ������������ ���������� ���������� � �������
		double nsFreq = 1.0 / maxFps * 1000000000.0;				// ������� ���������� � ns
		auto maxLag = std::chrono::nanoseconds((long long)nsFreq);	// ��������� ��� ���������� � ns

		KE_CORE_INFO("Running");
		while (m_isRun) {
			auto curTime = clock::now();	// ����� �� ������� ������
			auto dft = curTime - lastTime;	// ����� ����� �������� � ns.
			lastTime = curTime;				// �������� ������� ���������� �����
			lag += dft;						// ���������� ����
			
			if (lag > maxLag) {
				float dt = 1.0f * lag.count() / 1000000000.0f; // ����� ���������� � ��������
				Update(dt);
				lag = std::chrono::nanoseconds(0);
			}
		}
	}

	void CApplication::StopApplication()
	{
		m_isRun = false;
	}

}

