#pragma once

class CWindow
{
protected:
	static const UINT C_NUMERO_MASSIMO_CARATTERI = 100U;
protected:
	bool m_DisegnoAutonomo;
	ATOM m_RisultatoRegistrazione;
	HANDLE m_Cursore;
	HANDLE m_IconaFinestra;
	HINSTANCE m_Istanza;
	HWND m_HandleFinestra;
	HWND m_HandleProprietario;
	std::map<int, CWindow*> m_ControlliFinestra;
	std::wstring m_NomeClasseFinestra;
	std::wstring m_TitoloFinestra;
	WNDCLASSEX m_InformazioniFinestra;
public:
	CWindow();
	CWindow(HINSTANCE istanza, UINT idRisorsaNomeFinestra, HWND proprietaria);
	CWindow(HINSTANCE istanza, UINT idRisorsaNomeClasse, UINT idRisorsaNomeFinestra, HWND proprietaria);
	virtual void OnNotify(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint();
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
	virtual INT_PTR ProceduraFinestra(HWND handle, UINT messaggio, WPARAM wParam, LPARAM lParam);
	inline bool IsDisegnoAutonomo() const
	{
		return m_DisegnoAutonomo;
	}
	void AggiornaFinestra();
	void CreaFinestra();
	void MostraMessaggioDiErrore();
	void RegistraFinestra();
	void SetCursor(UINT idRisorsa, bool usaCaricamentoAvanzato);
	void SetIcon(UINT idRisorsa, bool usaCaricamentoAvanzato);
	inline void SetHandleFinestra(HWND handleFinestra)
	{
		m_HandleFinestra = handleFinestra;
	}
	inline HWND HandleFinestra()
	{
		return m_HandleFinestra;
	}
	LONG AltezzaFinestra() const;
	LONG LarghezzaFinestra() const;
private:
	static INT_PTR CALLBACK WndProc(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
};
