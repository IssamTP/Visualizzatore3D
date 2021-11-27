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
	virtual void CreaFinestra(HWND parent);
	inline bool IsDisegnoAutonomo() const
	{
		return m_DisegnoAutonomo;
	}
	void AggiornaFinestra();
	void CentraFinestra();
	void MostraFinestra(int comandoShow);
	void MostraMessaggioDiErrore();
	void RegistraClasseFinestra();
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
	operator HWND();
protected:
	virtual void OnClose();
	virtual void OnHScroll(UINT operazione, int posizione, HANDLE scrollBar);
	virtual void OnNotify(UINT idNotificatore, LPNMHDR nmhdr);
	virtual void OnPaint(LPPAINTSTRUCT datiDisegno);
	virtual void OnVScroll(UINT operazione, int posizione, HANDLE scrollBar);
	virtual INT_PTR ProceduraFinestra(HWND handle, UINT messaggio, WPARAM wParam, LPARAM lParam);
	void OnPaint();
private:
	static INT_PTR CALLBACK WndProc(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
};
