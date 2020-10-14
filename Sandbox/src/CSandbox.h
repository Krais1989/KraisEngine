
#include <KraisEngine.h>
#include <KraisEngine/Core/CLayer.h>

class TestLayer : public KE::CLayer {

public:
	void OnAttach() override {
		KE_INFO("TestLayer: OnAttach");
	}


	void OnDetach() override {
		KE_INFO("TestLayer: OnDetach");
	}


	void OnUpdate(float dt) override {
		KE_INFO("TestLayer: OnUpdate > {0}", dt);
	}


	void OnEvent(KE::CEvent& ev) override {
		KE_INFO("TestLayer: OnEvent > {0}", ev.ToString());
	}

};

class TestLayer2 : public KE::CLayer {

public:
	void OnAttach() override {
		KE_INFO("TestLayer 2: OnAttach");
	}


	void OnDetach() override {
		KE_INFO("TestLayer 2: OnDetach");
	}


	void OnUpdate(float dt) override {
		KE_INFO("TestLayer 2: OnUpdate > {0}", dt);
	}


	void OnEvent(KE::CEvent& ev) override {
		KE_INFO("TestLayer 2: OnEvent > {0}", ev.ToString());
	}

};

class TestOverlay : public KE::CLayer {

public:
	void OnAttach() override {
		KE_INFO("TestOverlay: OnAttach");
	}


	void OnDetach() override {
		KE_INFO("TestOverlay: OnDetach");
	}


	void OnUpdate(float dt) override {
		KE_INFO("TestOverlay: OnUpdate > {0}", dt);
	}


	void OnEvent(KE::CEvent& ev) override {
		KE_INFO("TestOverlay: OnEvent > {0}", ev.ToString());
	}

};

class CSandbox : public KE::CApplication
{
public:
	CSandbox();
	~CSandbox() override;
};

KE::CApplication* KE::CreateApplication() {
	return new CSandbox();
}