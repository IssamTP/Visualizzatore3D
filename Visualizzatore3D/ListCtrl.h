#pragma once

#include "Window.h"

class CListCtrl : public CWindow
{
protected:
	std::vector<LVITEM> m_Elementi;
public:
	CListCtrl();
	~CListCtrl();
	void GetElemento(LVITEM& elemento);
	unsigned int GetNumeroElementi() const;
	void AggiungiElemento(LPCTSTR descrizione, int indice, bool selezionato);
	void DisplayInfoNotification(LV_DISPINFO* pDisplayInfo);
	void SetImageList(HIMAGELIST imageList);
};
