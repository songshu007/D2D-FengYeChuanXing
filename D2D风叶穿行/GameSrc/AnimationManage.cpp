#include "AnimationManage.h"

AnimationManage* AnimationManage::it = nullptr;

AnimationManage::AnimationManage(shu::Direct2dRender& rt)
	:m_rt(rt)
{
	it = this;
}

AnimationManage::~AnimationManage()
{
	for (auto& it : AnimationData)
	{
		for (auto& anim : it.second)
		{
			for (auto bitmap = anim.second.first.begin(); bitmap != anim.second.first.end();)
			{
				(*bitmap)->Release();
				bitmap = anim.second.first.erase(bitmap);
			}
		}
	}
}

_Animation* AnimationManage::GetAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	auto anim = it->AnimationData.find(std::make_pair(bitmapFile, jsonFile));

	if (anim == it->AnimationData.end())
	{
		// 没找到，加载
		it->AnimationData[std::make_pair(bitmapFile, jsonFile)];

		if (!it->loadAnimation(bitmapFile, jsonFile, it->AnimationData.at(std::make_pair(bitmapFile, jsonFile)), duration))
			return nullptr;
		else
			return &it->AnimationData[std::make_pair(bitmapFile, jsonFile)];

		return nullptr;
	}
	else
	{
		// 找到了就返回
		return &anim->second;
	}
}

bool AnimationManage::loadAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, _Animation& root, float duration)
{
	char buf[256] = { 0 };

	// 加载图片
	ID2D1Bitmap1* Src_Bitmap = nullptr;
	Src_Bitmap = shu::Resource::GetBitmap(bitmapFile);
	if (Src_Bitmap == nullptr) return false;

	// 加载Json
	Json::Value* data_;
	data_ = shu::Resource::GetJson(jsonFile);
	if (data_ == nullptr) return false;
	Json::Value& data = *data_;

	int animation_num = data["meta"]["frameTags"].size();

	for (int j = 0; j < animation_num; j++)
	{
		std::string name = data["meta"]["frameTags"][j]["name"].asString();

		int from = data["meta"]["frameTags"][j]["from"].asInt();
		int to = data["meta"]["frameTags"][j]["to"].asInt();

		int count = 0;
		for (int i = from; i != to + 1; i++)
		{
			animation_data anim_data = { 0 };
			anim_data.Frame.x = data["frames"][i]["frame"]["x"].asUInt();
			anim_data.Frame.y = data["frames"][i]["frame"]["y"].asUInt();
			anim_data.Frame.w = data["frames"][i]["frame"]["w"].asUInt();
			anim_data.Frame.h = data["frames"][i]["frame"]["h"].asUInt();

			anim_data.SourceSize.w = data["frames"][i]["sourceSize"]["w"].asUInt();
			anim_data.SourceSize.h = data["frames"][i]["sourceSize"]["h"].asUInt();

			anim_data.SpriteSourcePos.x = data["frames"][i]["spriteSourceSize"]["x"].asUInt();
			anim_data.SpriteSourcePos.y = data["frames"][i]["spriteSourceSize"]["y"].asUInt();
			anim_data.SpriteSourcePos.w = data["frames"][i]["spriteSourceSize"]["w"].asUInt();
			anim_data.SpriteSourcePos.h = data["frames"][i]["spriteSourceSize"]["h"].asUInt();

			root[name].first.push_back(nullptr);
			root[name].first.at(count) = CreateSpritesBitmap(Src_Bitmap, &anim_data);
			if (root[name].first.at(count) == nullptr)
			{
				sprintf_s(buf, "Faile: %s Line: %d \n", __FILE__, __LINE__);
				Loger::Write(buf);
				return false;
			}
			root[name].second = duration;
			//m_now_animation = &root.find(name);

			count++;
		}
	}

	shu::Resource::ReleaseBitmap(bitmapFile);
	return true;
}

ID2D1Bitmap1* AnimationManage::CreateSpritesBitmap(ID2D1Bitmap1* srcBitmap, animation_data* d)
{
	ID2D1Bitmap1* recBitmap = nullptr;
	// 创建 一个 bitmap
	D2D1_BITMAP_PROPERTIES1 d2d1_bitmap_def = {};
	d2d1_bitmap_def.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	d2d1_bitmap_def.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	d2d1_bitmap_def.dpiX = USER_DEFAULT_SCREEN_DPI;
	d2d1_bitmap_def.dpiY = USER_DEFAULT_SCREEN_DPI;
	d2d1_bitmap_def.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;
	auto hr = m_rt.GetDC().CreateBitmap
	(
		{ d->SourceSize.w, d->SourceSize.h }, 0, 0,
		d2d1_bitmap_def,
		&recBitmap
	);
	if (FAILED(hr)) return nullptr;

	// 获取原来的矩阵，做一下备份
	D2D1_MATRIX_3X2_F last_matrix;
	m_rt.GetDC().GetTransform(&last_matrix);
	m_rt.GetDC().SetTarget(recBitmap);
	m_rt.GetDC().SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));	// 记得先归位摄像机
		 		
	m_rt.GetDC().BeginDraw();
	m_rt.GetDC().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
	m_rt.GetDC().DrawBitmap(srcBitmap,
		D2D1::RectF(d->SpriteSourcePos.x, d->SpriteSourcePos.y, d->SpriteSourcePos.x + d->SpriteSourcePos.w, d->SpriteSourcePos.y + d->SpriteSourcePos.h),
		1.0f,
		D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(d->Frame.x, d->Frame.y, d->Frame.x + d->Frame.w, d->Frame.y + d->Frame.h)
	);
	hr = m_rt.GetDC().EndDraw();

	if (FAILED(hr)) return nullptr;

	m_rt.GetDC().SetTarget(m_rt.GetRenderTarget());
	m_rt.GetDC().SetTransform(last_matrix);

	return recBitmap;
}