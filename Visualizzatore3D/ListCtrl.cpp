#include "Visualizzatore3D.h"
#include "ListCtrl.h"

CListCtrl::CListCtrl()
	: CWindow()
{
}

CListCtrl::~CListCtrl()
{
    for (auto elemento = m_Elementi.begin(); elemento != m_Elementi.end(); elemento++)
        delete[] elemento->pszText;
}

unsigned int CListCtrl::GetNumeroElementi() const
{
    return static_cast<unsigned int>(ListView_GetItemCount(m_HandleFinestra));
}

void CListCtrl::AggiungiElemento(LPCTSTR descrizione, bool selezionato)
{
	LVITEM nuovoElemento = { 0 };
	nuovoElemento.iItem = sizeof(LVITEM);
	nuovoElemento.mask = LVIF_TEXT | LVIF_STATE;
    if (selezionato)
        nuovoElemento.state = LVIS_SELECTED | LVIS_FOCUSED;
    else
        nuovoElemento.state = LVIS_FOCUSED;
    nuovoElemento.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	nuovoElemento.pszText = new TCHAR[256];
    _tcscpy_s(nuovoElemento.pszText, 256, descrizione);
    if (ListView_InsertItem(m_HandleFinestra, &nuovoElemento) < 0)
    {
		MostraMessaggioDiErrore();
        DebugBreak();
    }
	m_Elementi.push_back(nuovoElemento);
    if (GetNumeroElementi() != m_Elementi.size())
        DebugBreak();
}

void CListCtrl::DisplayInfoNotification(LV_DISPINFO* pDisplayInfo)
{

}