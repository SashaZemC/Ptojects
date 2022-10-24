#pragma once


// Training_Dialog_Panel dialog

class Training_Dialog_Panel : public CDialog
{
	DECLARE_DYNAMIC(Training_Dialog_Panel)

public:
	Training_Dialog_Panel(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Training_Dialog_Panel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
public:
	CString LanguageMode;
	CString Word;
	CString Translation;
	CString E1;
	afx_msg void OnBnClickedButton1();
	CString main_ms, ms, t, z, h;
	CString word, translate, translate_check;
	CStringArray aLineArray;
	CString All_Lines;
	CString buffer1, buffer2;
	int word_pair_counter = 0;
	int arr_words_with_mistakes[20];
	char buff[20];
	bool File_control = true, Start_button_on = false;
	bool Language_Mode;
	char ch;
	afx_msg CString Training_Dialog_Panel::Translate_checking();
	afx_msg CString Training_Dialog_Panel::Cuttin_Word_From_String_number();
	afx_msg void OnMenuStart();
	afx_msg void OnMenuStop();
	afx_msg void OnMenuReset();
};
