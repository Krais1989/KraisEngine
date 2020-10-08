#pragma once

#include <ke_api_defines.h>
#include <KraisEngine/Core/Log.h>
#include <KraisEngine/Core/CGraphics.h>
#include <KraisEngine/Core/CLagger.h>

namespace KE {

	class KRAIS_API CApplication
	{
	private:
		bool m_isRun = true;

		CGraphics* m_graphics;

		std::unique_ptr<CLagger> m_updateTimer;
		std::unique_ptr<CLagger> m_renderTimer;

	protected:
		virtual int InitGraphics(const CGraphics::InitData& initData);

	public:
		CApplication();

		virtual ~CApplication();

		/// <summary>
		/// ����� ������ ����������
		/// </summary>
		virtual void Run();
		virtual void StopApplication();

		KE::CGraphics* GetGraphics() const { return m_graphics; }

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


