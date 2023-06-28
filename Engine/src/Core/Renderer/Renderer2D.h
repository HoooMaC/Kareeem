#pragma once

namespace krm {

	class Renderer2D
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit();
	private:
		static void Flush();
	};


}