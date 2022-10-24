// Training_Dialog_Panel.cpp : implementation file
//

#include "pch.h"
#include "Training_English_Words_MemoryDlg_V2.h"
#include "Training_Dialog_Panel.h"
#include "afxdialogex.h"
#include <fstream>
#include <cstdio>

using namespace std;
// Training_Dialog_Panel dialog

IMPLEMENT_DYNAMIC(Training_Dialog_Panel, CDialog)

Training_Dialog_Panel::Training_Dialog_Panel(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, LanguageMode(_T("English-Russian"))
	, Word(_T(""))
	, Translation(_T(""))
	, E1(_T("All right"))
{

}

Training_Dialog_Panel::~Training_Dialog_Panel()
{
}

void Training_Dialog_Panel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, LanguageMode);
	DDX_Text(pDX, IDC_EDIT2, Word);
	DDX_Text(pDX, IDC_EDIT1, Translation);
	DDX_Text(pDX, IDC_E1, E1);
}


BEGIN_MESSAGE_MAP(Training_Dialog_Panel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Training_Dialog_Panel::OnBnClickedButton1)
	ON_COMMAND(ID_MENU_START, &Training_Dialog_Panel::OnMenuStart)
	ON_COMMAND(ID_MENU_STOP, &Training_Dialog_Panel::OnMenuStop)
	ON_COMMAND(ID_MENU_RESET, &Training_Dialog_Panel::OnMenuReset)
END_MESSAGE_MAP()


// Training_Dialog_Panel message handlers


BOOL Training_Dialog_Panel::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	setlocale(LC_ALL, "rus");
	CStdioFile inf(L"data.txt", CFile::modeRead);
	while (inf.ReadString(All_Lines))	//read all strings from file data.txt
	{
		aLineArray.Add(All_Lines);
	}
	inf.Close();


	for (int w = 0; w < 20; w++)
	{
		arr_words_with_mistakes[w] = 2365;
	}

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Training_Dialog_Panel::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	if (File_control)
	{
		if (Start_button_on)
		{
			Translate_checking();
			word = "";

			word_pair_counter++;
			t = aLineArray[word_pair_counter];
			if (!(t == "File is empty, you know all words in it"))
			{
				Cuttin_Word_From_String_number();

				UpdateData(true);
				Word = word;
				Translation = "";
				UpdateData(false);
				word.Empty();
			}
			else
			{
				ms += "\n";
				ms += "File is empty, you know all words in it";
				UpdateData(true);
				E1 = ms;
				UpdateData(false);
				File_control = false;
			}

		}
	}


}

CString Training_Dialog_Panel::Translate_checking()
{
	t = aLineArray[word_pair_counter];// word_pair_counter begins from 1
	ms = "";

	UpdateData(true);
	translate = Translation;
	UpdateData(false);

	Cuttin_Word_From_String_number();

	if (translate == translate_check)  //comparison
	{
		ms = "Properly";
		UpdateData(true);
		E1 = ms;
		UpdateData(false);
	}
	else
	{
		ms = "False, correct: ";
		ms += translate_check;
		UpdateData(true);
		E1 = ms;
		UpdateData(false);
		for (int w = 0; w < 20; w++)
		{
			if (arr_words_with_mistakes[w] == 2365) {
				arr_words_with_mistakes[w] = word_pair_counter; break;
			}

		}
	}
	translate_check.Empty();
	return ms;
}

CString Training_Dialog_Panel::Cuttin_Word_From_String_number()
{
	bool fg = false;
	CString buffer1, buffer2;

	if (Language_Mode) //cutting translate_check
	{
		for (int j = 0; (j < t.GetLength()); j++) // cut second word from string
		{
			if ((fg == false))buff[0] = t.GetAt(j);
			if (fg == true)buffer1 += t[j];
			if (buff[0] == ' ')fg = true;
		}
	}
	if (!Language_Mode)
	{
		for (int j = 0; (j < t.GetLength()); j++)// cut first word from string
		{
			if (fg == false)buff[0] = t.GetAt(j);
			if (buff[0] == ' ')break;
			if (fg == false)buffer1 += t[j];

		}
	}
	translate_check = buffer1;

	fg = false;
	if (Language_Mode) //cutting word
	{
		for (int j = 0; (j < t.GetLength()); j++)// cut first word from string
		{
			if (fg == false)buff[0] = t.GetAt(j);
			if (buff[0] == ' ')break;
			if (fg == false)buffer2 += t[j];
		}
	}
	if (!Language_Mode)
	{
		for (int j = 0; (j < t.GetLength()); j++) // cut second word from string
		{
			if ((fg == false))buff[0] = t.GetAt(j);
			if (fg == true)buffer2 += t[j];
			if (buff[0] == ' ')fg = true;
		}
	}
	word = buffer2;

	return translate_check, word;
}

void Training_Dialog_Panel::OnMenuStart()
{
	// TODO: Add your command handler code here
	UpdateData(true);
	h = LanguageMode;
	UpdateData(false);

	if (h == "English-Russian")Language_Mode = true; //choosing language type english
	if (h == "Russian-English")Language_Mode = false; //choosing language type ukrainian

	t = aLineArray[word_pair_counter];
	Cuttin_Word_From_String_number();

	UpdateData(true);
	Word = word;
	h = LanguageMode;
	UpdateData(false);

	Start_button_on = true;
}


void Training_Dialog_Panel::OnMenuStop()
{
	// TODO: Add your command handler code here
	Start_button_on = false;
}


void Training_Dialog_Panel::OnMenuReset()
{
	// TODO: Add your command handler code here
	word_pair_counter = 0;
	Start_button_on = false;
	File_control = true;
	UpdateData(true);
	Word = "";
	E1 = "";
	Translation = "";
	UpdateData(false);
}
