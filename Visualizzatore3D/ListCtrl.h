#pragma once

#include "Window.h"

class CListCtrl : public CWindow
{
protected:
	std::vector<std::wstring> m_Etichette;
	std::vector<LVITEM> m_Elementi;
public:
	CListCtrl();
	unsigned int GetNumeroElementi() const;
	void AggiungiElemento(LPCTSTR descrizione, bool selezionato);
	void DisplayInfoNotification(LV_DISPINFO* pDisplayInfo);
};
