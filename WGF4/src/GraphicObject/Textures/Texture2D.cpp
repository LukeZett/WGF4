#include "GraphicObject/Textures/Texture2D.h"
#include "GraphicObject/Textures/Image.h"

using namespace WGF;

void Texture2D::Init(uint32_t width, uint32_t height)
{
    i_Init(width, height, 1);
}

void Texture2D::Init(const std::filesystem::path& path)
{
    Image img(path);
    SetDefaultDescriptor<2>();
    SetDefaultViewDescriptor<2>();

    i_Init(img.Width(), img.Height(), 1);
    i_Write(img.Data(), { 0,0,0 }, { img.Width(), img.Height(), 1 }, img.Channels());
}