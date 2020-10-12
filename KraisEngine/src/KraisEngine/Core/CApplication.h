#pragma once

#include <ke_api_defines.h>
#include <KraisEngine/Core/Log.h>
#include <KraisEngine/Core/CGraphicsManager.h>
#include <KraisEngine/Core/CThrottler.h>

namespace KE {

	class KRAIS_API CApplication
	{
	private:
		bool m_isRun = true;

		CGraphicsManager* m_graphics;

		std::unique_ptr<CThrottler> m_updateTimer;
		std::unique_ptr<CThrottler> m_renderTimer;

	protected:
		virtual int InitGraphics(const CGraphicsManager::InitData& initData);

	public:
		CApplication();

		virtual ~CApplication();

		/// <summary>
		/// ����� ������ ����������
		/// </summary>
		virtual void Run();
		virtual void StopApplication();

		KE::CGraphicsManager* GetGraphics() const { return m_graphics; }

	protected:
		/// <summary>
		/// ���������� ������ ����������
		/// </summary>
		/// <param name="dt_sec"></param>
		virtual void Update(float dt_sec);

		/// <summary>
		/// ������� ����� ��� ���������. �������� ������� ������, ����� ��������
		/// </summary>
		virtual void Render();

		/// <summary>
		/// ���������� ����� ��� ���������
		/// </summary>
		virtual void Render_Internal();
	};

	/* ���������� � ���������� */
	CApplication* CreateApplication();
}


