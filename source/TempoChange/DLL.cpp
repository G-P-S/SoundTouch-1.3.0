// DLL.cpp
#include <windows.h>
#include <streams.h>
#include <dllsetup.h>

STDAPI DllRegisterServer()
{
	return AMovieDllRegisterServer2(TRUE);
}

STDAPI DllUnregisterServer()
{
	return AMovieDllRegisterServer2(FALSE);
}
