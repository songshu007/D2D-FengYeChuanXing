#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "Render.h"
#include "json/json.h"

namespace shu
{
	using namespace Microsoft::WRL;

	class Resource
	{
	public:
		Resource(shu::Direct2dRender& rt);
		~Resource();

		static ID2D1Bitmap1* GetBitmap(std::wstring file);
		static Json::Value* GetJson(std::wstring file);

		static void ReleaseBitmap(const std::wstring& file);

	private:

		std::map<std::wstring, ComPtr<ID2D1Bitmap1>> m_Bitmaps;
		std::map<std::wstring, std::unique_ptr<Json::Value>> m_Jsons;

		shu::Direct2dRender& m_rt;
		static Resource* ptr;

	};
}
