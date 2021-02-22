
#include <KraisEngine/Core/Core.h>

#include <KraisEngine/Core/CAsset.h>

namespace KE {

	namespace fs = std::filesystem;

	//template<typename T>
	class CAssetManager {
	public:
		using AssetID = std::string;
		using AssetPtr = std::shared_ptr<CAsset>;
	public:
		virtual void Add(const AssetID& asset_id, const AssetPtr& asset) {
			KE_CORE_ASSERT(!Exists(asset_id), "Asset ID {0} already exists");
			m_Assets[asset_id] = asset;
		}
		virtual AssetPtr Load(const AssetID& asset_id, const std::filesystem::path& file_path) {
			std::ifstream asset_file;
			asset_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try {
				asset_file.open(file_path);
				std::stringstream asset_file_stream;
				asset_file_stream << asset_file.rdbuf();
				asset_file.close();

				std::string file_data = asset_file_stream.str();
			}
			catch (std::ifstream::failure e) {
				KE_ERROR("FILE READ ERROR {0}", file_path.string());
			}
		}
		virtual AssetPtr Load(const std::filesystem::path& file_path) {
			KE_CORE_ASSERT(file_path.has_filename(), "'{0}' - File name not defined!");
			auto filename = file_path.filename().string();
			return Load(filename, file_path);
		}
		virtual AssetPtr Get(const AssetID& asset_id) {
			KE_CORE_ASSERT(Exists(asset_id), "Asset ID {0} not found");
			return m_Assets[asset_id];
		}
		virtual bool Exists(const AssetID& assed_id) {
			return m_Assets.find(assed_id) != m_Assets.end();
		}
	protected:
		std::unordered_map<AssetID, AssetPtr> m_Assets;
	};
}
