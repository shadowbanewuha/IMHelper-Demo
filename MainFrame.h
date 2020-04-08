#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "framework.h"

class UIFunction;
class UIMessage;

class MainFrame : public WindowImplBase
{
public:

	MainFrame();
	~MainFrame();

public:
	void Init();

	LPCTSTR GetWindowClassName() const;
	//virtual void OnFinalMessage(HWND hWnd);
	//virtual void InitWindow();
	//virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	//virtual UILIB_RESOURCETYPE GetResourceType() const;
	//virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	//virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual LPCTSTR GetResourceID() const;
	//DWORD GetBkColor();
	//void SetBkColor(DWORD dwBackColor);

protected:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SwitchTabWithNotifyMessage(TNotifyUI& msg);

	void handleMenuItemClickMessage(TNotifyUI& msg);

public:
	CPaintManagerUI m_pm;

private:
	CDialogBuilder m_dlgBuilder;

	CControlUI *m_pRootControl;

	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pSearch;

	CListUI* m_pAccountList;

	CTabLayoutUI *m_pMainTab;
	CLabelUI *m_pTitelLabel;

	UIFunction *m_pFunctionController;
	UIMessage *m_pMessageController;

	CWindowWnd *m_pMessageBox;
};

#endif // MAINFRAME_HPP