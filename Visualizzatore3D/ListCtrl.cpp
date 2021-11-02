#include "Visualizzatore3D.h"
#include "ListCtrl.h"

CListCtrl::CListCtrl()
	: CWindow()
{
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
	nuovoElemento.pszText = LPSTR_TEXTCALLBACK;
	int posizioneInserimento = ListView_InsertItem(m_HandleFinestra, &nuovoElemento);
	m_Elementi.push_back(nuovoElemento);
    std::wstring wstrDescrizione(descrizione);
	m_Etichette.push_back(wstrDescrizione);
	if (posizioneInserimento == -1)
		MostraMessaggioDiErrore();
    if (GetNumeroElementi() != m_Elementi.size())
        DebugBreak();
}

void CListCtrl::DisplayInfoNotification(LV_DISPINFO* pDisplayInfo)
{
    TCHAR szString[MAX_PATH];
    memset(szString, 0, MAX_PATH * sizeof(TCHAR));
    if (pDisplayInfo->item.mask & LVIF_TEXT)
        _tcsncpy_s(pDisplayInfo->item.pszText, pDisplayInfo->item.cchTextMax, szString, _TRUNCATE);
    if (pDisplayInfo->item.mask & LVIF_IMAGE)
        pDisplayInfo->item.iImage = 0;
}
/*
#define ErrorHandler() ErrorHandlerEx(__LINE__, __FILE__)
void ErrorHandlerEx(WORD, LPSTR);

LRESULT ListViewNotify(HWND, LPARAM);
void SwitchView(HWND, DWORD);
BOOL DoContextMenu(HWND, WPARAM, LPARAM);
void UpdateMenu(HWND, HMENU);
BOOL InsertListViewItems(HWND);
void PositionHeader(HWND);
*/


/******************************************************************************
   MainWndProc
******************************************************************************

LRESULT CALLBACK MainWndProc(HWND hWnd,
    UINT uMessage,
    WPARAM wParam,
    LPARAM lParam)
{
    static HWND hwndListView;

    switch (uMessage)
    {

    case WM_NOTIFY:
        return ListViewNotify(hWnd, lParam);

    case WM_SIZE:
        ResizeListView(hwndListView, hWnd);
        break;

    case WM_INITMENUPOPUP:
        UpdateMenu(hwndListView, GetMenu(hWnd));
        break;

    case WM_CONTEXTMENU:
        if (DoContextMenu(hWnd, wParam, lParam))
            return FALSE;
        break;

    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wParam, lParam))
        {
        case IDM_LARGE_ICONS:
            SwitchView(hwndListView, LVS_ICON);
            break;

        case IDM_SMALL_ICONS:
            SwitchView(hwndListView, LVS_SMALLICON);
            break;

        case IDM_LIST:
            SwitchView(hwndListView, LVS_LIST);
            break;

        case IDM_REPORT:
            SwitchView(hwndListView, LVS_REPORT);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        case IDM_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, AboutDlgProc);
            break;

        }
        break;
    }
    return DefWindowProc(hWnd, uMessage, wParam, lParam);
}
*/
/******************************************************************************
   CreateListView
******************************************************************************

HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
{
    DWORD       dwStyle;
    HWND        hwndListView;
    HIMAGELIST  himlSmall;
    HIMAGELIST  himlLarge;
    BOOL        bSuccess = TRUE;

    dwStyle = WS_TABSTOP |
        WS_CHILD |
        WS_BORDER |
        WS_VISIBLE |
        LVS_AUTOARRANGE |
        LVS_REPORT |
        LVS_OWNERDATA;

    hwndListView = CreateWindowEx(WS_EX_CLIENTEDGE,          // ex style
        WC_LISTVIEW,               // class name - defined in commctrl.h
        TEXT(""),                        // dummy text
        dwStyle,                   // style
        0,                         // x position
        0,                         // y position
        0,                         // width
        0,                         // height
        hwndParent,                // parent
        (HMENU)ID_LISTVIEW,        // ID
        g_hInst,                   // instance
        NULL);                     // no extra data

    if (!hwndListView)
        return NULL;

    ResizeListView(hwndListView, hwndParent);

    //set the image lists
    himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
    himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

    if (himlSmall && himlLarge)
    {
        HICON hIcon;

        //set up the small image list
        hIcon = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
        ImageList_AddIcon(himlSmall, hIcon);

        //set up the large image list
        hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
        ImageList_AddIcon(himlLarge, hIcon);

        ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
        ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
    }

    return hwndListView;
}
*/
/******************************************************************************
   ResizeListView
******************************************************************************/

void ResizeListView(HWND hwndListView, HWND hwndParent)
{
    RECT  rc;

    GetClientRect(hwndParent, &rc);

    MoveWindow(hwndListView,
        rc.left,
        rc.top,
        rc.right - rc.left,
        rc.bottom - rc.top,
        TRUE);

    //only call this if we want the LVS_NOSCROLL style
    //PositionHeader(hwndListView);
}

/******************************************************************************
   PositionHeader
   this needs to be called when the ListView is created, resized, the view is
   changed or a WM_SYSPARAMETERCHANGE message is received
******************************************************************************/

void PositionHeader(HWND hwndListView)
{
    HWND  hwndHeader = GetWindow(hwndListView, GW_CHILD);
    DWORD dwStyle = GetWindowLong(hwndListView, GWL_STYLE);

    /*To ensure that the first item will be visible, create the control without
    the LVS_NOSCROLL style and then add it here*/
    dwStyle |= LVS_NOSCROLL;
    SetWindowLong(hwndListView, GWL_STYLE, dwStyle);

    //only do this if we are in report view and were able to get the header hWnd
    if (((dwStyle & LVS_TYPEMASK) == LVS_REPORT) && hwndHeader)
    {
        RECT        rc;
        HD_LAYOUT   hdLayout;
        WINDOWPOS   wpos;

        GetClientRect(hwndListView, &rc);
        hdLayout.prc = &rc;
        hdLayout.pwpos = &wpos;

        Header_Layout(hwndHeader, &hdLayout);

        SetWindowPos(hwndHeader,
            wpos.hwndInsertAfter,
            wpos.x,
            wpos.y,
            wpos.cx,
            wpos.cy,
            wpos.flags | SWP_SHOWWINDOW);

        ListView_EnsureVisible(hwndListView, 0, FALSE);
    }
}

/******************************************************************************
   InitListView
******************************************************************************/

//BOOL InitListView(HWND hwndListView)
//{
//    LV_COLUMN   lvColumn;
//    int         i;
//    TCHAR       szString[5][20] = { TEXT("Main Column"), TEXT("Column 1"), TEXT("Column 2"), TEXT("Column 3"), TEXT("Column 4") };
//
//    //empty the list
//    ListView_DeleteAllItems(hwndListView);
//
//    //initialize the columns
//    lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//    lvColumn.fmt = LVCFMT_LEFT;
//    lvColumn.cx = 120;
//    for (i = 0; i < 5; i++)
//    {
//        lvColumn.pszText = szString[i];
//        ListView_InsertColumn(hwndListView, i, &lvColumn);
//    }
//
//    InsertListViewItems(hwndListView);
//
//    return TRUE;
//}

/******************************************************************************
   InsertListViewItems
******************************************************************************/
//
//BOOL InsertListViewItems(HWND hwndListView)
//{
//    //empty the list
//    ListView_DeleteAllItems(hwndListView);
//
//    //set the number of items in the list
//    ListView_SetItemCount(hwndListView, ITEM_COUNT);
//
//    return TRUE;
//}

/**************************************************************************
   ErrorHandlerEx()
**************************************************************************/

//void ErrorHandlerEx(WORD wLine, LPSTR lpszFile)
//{
//    LPVOID lpvMessage;
//    DWORD  dwError;
//    TCHAR  szBuffer[256];
//
//    // Allow FormatMessage() to look up the error code returned by GetLastError
//    dwError = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
//        FORMAT_MESSAGE_FROM_SYSTEM,
//        NULL,
//        GetLastError(),
//        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
//        (LPTSTR)&lpvMessage,
//        0,
//        NULL);
//
//    // Check to see if an error occurred calling FormatMessage()
//    if (0 == dwError)
//    {
//        _sntprintf_s(szBuffer, _countof(szBuffer), _TRUNCATE,
//            TEXT("An error occurred calling FormatMessage().")
//            TEXT("Error Code %d"),
//            GetLastError());
//        MessageBox(NULL,
//            szBuffer,
//            TEXT("Generic"),
//            MB_ICONSTOP | MB_ICONEXCLAMATION);
//        return;
//    }
//
//    // Display the error information along with the place the error happened.
//    _sntprintf_s(szBuffer, _countof(szBuffer), _TRUNCATE,
//        TEXT("Generic, Line=%d, File=%s"), wLine, lpszFile);
//    MessageBox(NULL, lpvMessage, szBuffer, MB_ICONEXCLAMATION | MB_OK);
//}

/**************************************************************************
   SwitchView()
**************************************************************************/

void SwitchView(HWND hwndListView, DWORD dwView)
{
    DWORD dwStyle = GetWindowLong(hwndListView, GWL_STYLE);

    SetWindowLong(hwndListView, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
    ResizeListView(hwndListView, GetParent(hwndListView));
}