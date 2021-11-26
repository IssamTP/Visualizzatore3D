#pragma once

#include "Window.h"

class CListCtrl : public CWindow
{
protected:
	std::vector<LVITEM> m_Elementi;
public:
	CListCtrl();
	~CListCtrl();
	UINT GetNumeroElementi() const;
	void AggiungiElemento(LPCTSTR descrizione, int indice, bool selezionato);
	void GetElemento(LVITEM& elemento);
	void SetImageList(HIMAGELIST imageList);
};
