#include "framework.h"
#include "Visualizzatore3D.h"
#include "Visualizzatore3DDlg.h"
#include "SliderCtrl.h"

CVisualizzatore3DDlg::CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa)
	: CDialog(istanza, idRisorsa)
{

}

void CVisualizzatore3DDlg::CreaControlliDaRisorse()
{
	auto controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_SLIDER1, new CSliderCtrl()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_SLIDER1));
	m_VSlider = reinterpret_cast<CSliderCtrl *>(controllo->second);
	m_VSlider->SetIntervallo(0U, 360U);

	controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_SLIDER2, new CSliderCtrl()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_SLIDER2));
	m_HSlider = reinterpret_cast<CSliderCtrl *>(controllo->second);
	m_HSlider->SetIntervallo(0u, 360U);

	m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_LIST1, new CWindow()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_LIST1));
}

void CVisualizzatore3DDlg::OnHScroll(WPARAM wParam, LPARAM lParam)
{

}

void CVisualizzatore3DDlg::OnVScroll(WPARAM wParam, LPARAM lParam)
{

}