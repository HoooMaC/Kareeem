#pragma once


#define BIT(x) (1 << x)

#define KRM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef _DEBUG
#define MAIN main()
#else
#define MAIN WinMain( HINSTANCE	hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int ShowCmd)
#endif