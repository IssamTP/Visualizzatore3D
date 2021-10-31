#pragma once

class CWindow
{
protected:
	HINSTANCE m_Istanza;
	HWND m_HandleFinestra;
	std::map<int, CWindow*> m_ControlliFinestra;
public:
	CWindow();
	inline void SetHandleFinestra(HWND handleFinestra)
	{
		m_HandleFinestra = handleFinestra;
	}
};

