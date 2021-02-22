#pragma once

#include <KraisEngine/Core/Core.h>

namespace KE {
	enum class EAssetType {
		Shader,
		Texture,
		Audio,
		Mesh
	};

	class CAsset {
	protected:
		EAssetType m_AssetType;
	public:
		CAsset(EAssetType type, std::string name, const std::filesystem::path& file_path)
			: m_AssetType(type), m_AssetName(name)
		{
			Load(file_path);
		}

		CAsset(const std::filesystem::path& file_path) 
		{
			Load(file_path);
		}

		std::string GetFileName() const { return m_FileName; }
		std::filesystem::path GetFilePath() const { return m_FilePath; }
		const char* GetRawData() {
			return m_RawData.get();
		};
		size_t GetSize() const { return m_RawDataSize; }
	protected:
		std::string m_AssetName;
		std::string m_FileName;
		std::unique_ptr<char[]> m_RawData;
		size_t m_RawDataSize;
		std::filesystem::path m_FilePath;
	protected:

		virtual void Load(const std::filesystem::path& file_path) {
			m_FilePath = file_path;
			m_FileName = file_path.filename().string();

			std::ifstream ifs(file_path, std::ios::binary | std::ios::ate);
			//ifs.seekg(0, std::ios::end);
			m_RawDataSize = ifs.tellg();
			m_RawData = std::make_unique<char[]>((m_RawDataSize + 1) * sizeof(char));
			ifs.seekg(0, std::ios::beg);
			ifs.read(m_RawData.get(), m_RawDataSize);
			ifs.close();
		}
	};
}