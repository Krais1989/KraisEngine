#include "CShader.h"
#include <KraisEngine/Core/CAsset.h>
#include <Platform/OpenGL/COpenGLShader.h>


std::shared_ptr<KE::CShader> KE::CShader::CreateFromData(const std::string name, const char* vertexSrc, const char* fragSrc)
{
	return std::make_shared<COpenGLShader>(name, vertexSrc, fragSrc);
}

std::shared_ptr<KE::CShader> KE::CShader::CreateFromFile(const std::string name, const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath)
{
	CAsset vertAsset(vertexPath);
	CAsset fragAsset(fragPath);
	return CreateFromData(name, vertAsset.GetRawData(), fragAsset.GetRawData());
}
