#pragma once

namespace KE {
	class CTexture2D
	{
	public:
		virtual void Init(const std::string& path) = 0;
		virtual void Bind(int unit = 0) = 0;
		int Width() const { return m_Width; }
		int Height() const { return m_Height; }
		int Channels() const { return m_Channels; }
		bool IsSuccess() { return ErrorMessage() == ""; }
		std::string const& ErrorMessage() const { return m_ErrorMessage; }

		static std::shared_ptr<CTexture2D> Create(const std::string& path);

		unsigned int GetTextureId() const { return m_TextureId; }
	protected:
		int m_Width;
		int m_Height;
		int m_Channels;

		unsigned int m_TextureId;

		std::string m_ErrorMessage;
	};

}
