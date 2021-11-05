#pragma once

class CWindow
{
protected:
	bool m_DisegnoAutonomo;
	HINSTANCE m_Istanza;
	HWND m_HandleFinestra;
	std::map<int, CWindow*> m_ControlliFinestra;
public:
	CWindow();
	virtual void OnNotify(LPNMHDR pNMHDR);
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint();
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
	inline bool IsDisegnoAutonomo() const
	{
		return m_DisegnoAutonomo;
	}
	void MostraMessaggioDiErrore();
	inline void SetHandleFinestra(HWND handleFinestra)
	{
		m_HandleFinestra = handleFinestra;
	}
};

