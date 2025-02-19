#include "Application/Scene.h"
#include <type_traits>
#include <memory>

void WGF::App::Scene::SetNewScene(std::unique_ptr<Scene>&& scene)
{
	m_nextScene = std::move(scene);
	m_useNewScene = true;
}
