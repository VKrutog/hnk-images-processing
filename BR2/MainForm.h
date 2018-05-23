#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Preprocessing.h"
#include "Recognition.h"
#include "EDBForm.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>




namespace BR2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			Set();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

#pragma region Properties

	private:
		Mat* src_mat;
		Mat* res_mat;
		array<System::String^>^ script_items;
		int items_counter = 0;
		Blob_* blobs;
		int blobs_counter = 0;
		int current_blob = 0;
		cv::Point* koord;
		cv::Point* old_koord;
		EDBForm^ edbForm;
		Recognition* rec;

#pragma endregion

#pragma region Components


	private: System::Windows::Forms::Panel^  panel1;





	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Panel^  panel2;

	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  btClearScript;
	private: System::Windows::Forms::Button^  btDelScriptRow;
	private: System::Windows::Forms::ListBox^  listBoxScript;




	private: System::Windows::Forms::Label^  lblbScriptName;
	private: System::Windows::Forms::ToolStripMenuItem^  loadScriptToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveScriptToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::Button^  btRunScript;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblFileName;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveImageToolStripMenuItem;





	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
















private: System::Windows::Forms::ToolStripProgressBar^  progressBar;
private: System::Windows::Forms::Button^  button16;
private: System::Windows::Forms::Button^  button15;
private: System::Windows::Forms::ToolStripStatusLabel^  lblCounterBlobs;
private: System::Windows::Forms::ToolStripStatusLabel^  lblTicketYesNo;
private: System::Windows::Forms::ToolStripStatusLabel^  lblAngle;
private: System::Windows::Forms::Button^  button18;
private: System::Windows::Forms::Button^  button17;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::Button^  button19;
private: System::Windows::Forms::Button^  button20;
private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::Button^  button22;
private: System::Windows::Forms::Button^  button23;
private: System::Windows::Forms::Button^  button24;
private: System::Windows::Forms::Button^  button25;
private: System::Windows::Forms::Button^  button26;
private: System::Windows::Forms::Button^  button27;
private: System::Windows::Forms::Button^  button29;
private: System::Windows::Forms::Button^  button28;
private: System::Windows::Forms::Button^  button31;
private: System::Windows::Forms::Button^  button30;
private: System::Windows::Forms::GroupBox^  groupBox4;

private: System::Windows::Forms::Button^  button40;
private: System::Windows::Forms::Panel^  panelBlobs1;
private: System::Windows::Forms::Panel^  panelBlobs2;
private: System::Windows::Forms::TrackBar^  trackBarBlobs;

private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  labelBlobs;
private: System::Windows::Forms::Timer^  timer1;

private: System::Windows::Forms::ToolStripMenuItem^  saveBlobToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  loadImageToolStripMenuItem;

private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::Button^  button32;





private: System::Windows::Forms::ToolStripMenuItem^  eDBToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  loadEDBToolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  saveEDBToolStripMenuItem1;

private: System::Windows::Forms::ToolStripMenuItem^  newEDBToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  eDBManagerToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
private: System::Windows::Forms::ToolStripMenuItem^  saveBlobSrcToolStripMenuItem;







private: System::ComponentModel::IContainer^  components;













#pragma endregion





	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->listBoxScript = (gcnew System::Windows::Forms::ListBox());
			this->lblbScriptName = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->btRunScript = (gcnew System::Windows::Forms::Button());
			this->btClearScript = (gcnew System::Windows::Forms::Button());
			this->btDelScriptRow = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button32 = (gcnew System::Windows::Forms::Button());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button30 = (gcnew System::Windows::Forms::Button());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button40 = (gcnew System::Windows::Forms::Button());
			this->panelBlobs1 = (gcnew System::Windows::Forms::Panel());
			this->panelBlobs2 = (gcnew System::Windows::Forms::Panel());
			this->trackBarBlobs = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelBlobs = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->lblFileName = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->progressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->lblCounterBlobs = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblTicketYesNo = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblAngle = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadScriptToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveBlobToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveScriptToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eDBToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eDBManagerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->loadEDBToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveEDBToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->saveBlobSrcToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->panelBlobs1->SuspendLayout();
			this->panelBlobs2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarBlobs))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->tabControl1);
			this->panel1->Controls->Add(this->statusStrip1);
			this->panel1->Controls->Add(this->menuStrip1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(719, 407);
			this->panel1->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->listBoxScript);
			this->panel2->Controls->Add(this->lblbScriptName);
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel2->Location = System::Drawing::Point(342, 24);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(377, 361);
			this->panel2->TabIndex = 5;
			// 
			// listBoxScript
			// 
			this->listBoxScript->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBoxScript->FormattingEnabled = true;
			this->listBoxScript->Location = System::Drawing::Point(0, 13);
			this->listBoxScript->Name = L"listBoxScript";
			this->listBoxScript->Size = System::Drawing::Size(377, 317);
			this->listBoxScript->TabIndex = 3;
			// 
			// lblbScriptName
			// 
			this->lblbScriptName->Dock = System::Windows::Forms::DockStyle::Top;
			this->lblbScriptName->Location = System::Drawing::Point(0, 0);
			this->lblbScriptName->Name = L"lblbScriptName";
			this->lblbScriptName->Size = System::Drawing::Size(377, 13);
			this->lblbScriptName->TabIndex = 2;
			this->lblbScriptName->Text = L"Script";
			this->lblbScriptName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->btRunScript);
			this->panel3->Controls->Add(this->btClearScript);
			this->panel3->Controls->Add(this->btDelScriptRow);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel3->Location = System::Drawing::Point(0, 330);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(377, 31);
			this->panel3->TabIndex = 0;
			// 
			// btRunScript
			// 
			this->btRunScript->Dock = System::Windows::Forms::DockStyle::Right;
			this->btRunScript->Location = System::Drawing::Point(219, 0);
			this->btRunScript->Name = L"btRunScript";
			this->btRunScript->Size = System::Drawing::Size(58, 31);
			this->btRunScript->TabIndex = 2;
			this->btRunScript->Text = L"Run";
			this->btRunScript->UseVisualStyleBackColor = true;
			this->btRunScript->Click += gcnew System::EventHandler(this, &MainForm::btRunScript_Click);
			// 
			// btClearScript
			// 
			this->btClearScript->Dock = System::Windows::Forms::DockStyle::Right;
			this->btClearScript->Location = System::Drawing::Point(277, 0);
			this->btClearScript->Name = L"btClearScript";
			this->btClearScript->Size = System::Drawing::Size(43, 31);
			this->btClearScript->TabIndex = 1;
			this->btClearScript->Text = L"Clear";
			this->btClearScript->UseVisualStyleBackColor = true;
			this->btClearScript->Click += gcnew System::EventHandler(this, &MainForm::btClearScript_Click);
			// 
			// btDelScriptRow
			// 
			this->btDelScriptRow->Dock = System::Windows::Forms::DockStyle::Right;
			this->btDelScriptRow->Location = System::Drawing::Point(320, 0);
			this->btDelScriptRow->Name = L"btDelScriptRow";
			this->btDelScriptRow->Size = System::Drawing::Size(57, 31);
			this->btDelScriptRow->TabIndex = 0;
			this->btDelScriptRow->Text = L"Del";
			this->btDelScriptRow->UseVisualStyleBackColor = true;
			this->btDelScriptRow->Click += gcnew System::EventHandler(this, &MainForm::btDelScriptRow_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Bottom;
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 24);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(719, 361);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->groupBox5);
			this->tabPage4->Location = System::Drawing::Point(4, 4);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(711, 335);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Recognition";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button32);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Left;
			this->groupBox5->Location = System::Drawing::Point(0, 0);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(166, 335);
			this->groupBox5->TabIndex = 5;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"functions";
			// 
			// button32
			// 
			this->button32->Dock = System::Windows::Forms::DockStyle::Top;
			this->button32->Location = System::Drawing::Point(3, 16);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(160, 28);
			this->button32->TabIndex = 0;
			this->button32->Text = L"Recognize";
			this->button32->UseVisualStyleBackColor = true;
			this->button32->Click += gcnew System::EventHandler(this, &MainForm::button32_Click);
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 4);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(711, 335);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Preprocessing";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button31);
			this->groupBox2->Controls->Add(this->button29);
			this->groupBox2->Controls->Add(this->button18);
			this->groupBox2->Controls->Add(this->button16);
			this->groupBox2->Controls->Add(this->button8);
			this->groupBox2->Controls->Add(this->button9);
			this->groupBox2->Controls->Add(this->button10);
			this->groupBox2->Controls->Add(this->button11);
			this->groupBox2->Controls->Add(this->button12);
			this->groupBox2->Controls->Add(this->button13);
			this->groupBox2->Controls->Add(this->button14);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Left;
			this->groupBox2->Location = System::Drawing::Point(171, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(168, 329);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"set of functions";
			// 
			// button31
			// 
			this->button31->Dock = System::Windows::Forms::DockStyle::Top;
			this->button31->Location = System::Drawing::Point(3, 296);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(162, 28);
			this->button31->TabIndex = 10;
			this->button31->Text = L"TopBottom";
			this->button31->UseVisualStyleBackColor = true;
			this->button31->Click += gcnew System::EventHandler(this, &MainForm::button31_Click);
			// 
			// button29
			// 
			this->button29->Dock = System::Windows::Forms::DockStyle::Top;
			this->button29->Location = System::Drawing::Point(3, 268);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(162, 28);
			this->button29->TabIndex = 9;
			this->button29->Text = L"Canny";
			this->button29->UseVisualStyleBackColor = true;
			this->button29->Click += gcnew System::EventHandler(this, &MainForm::button29_Click);
			// 
			// button18
			// 
			this->button18->Dock = System::Windows::Forms::DockStyle::Top;
			this->button18->Location = System::Drawing::Point(3, 240);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(162, 28);
			this->button18->TabIndex = 8;
			this->button18->Text = L"Contrast";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &MainForm::button18_Click);
			// 
			// button16
			// 
			this->button16->Dock = System::Windows::Forms::DockStyle::Top;
			this->button16->Location = System::Drawing::Point(3, 212);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(162, 28);
			this->button16->TabIndex = 7;
			this->button16->Text = L"FewBlobs";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MainForm::button16_Click);
			// 
			// button8
			// 
			this->button8->Dock = System::Windows::Forms::DockStyle::Top;
			this->button8->Location = System::Drawing::Point(3, 184);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(162, 28);
			this->button8->TabIndex = 6;
			this->button8->Text = L"Invert";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Dock = System::Windows::Forms::DockStyle::Top;
			this->button9->Location = System::Drawing::Point(3, 156);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(162, 28);
			this->button9->TabIndex = 5;
			this->button9->Text = L"Threshold";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MainForm::button9_Click);
			// 
			// button10
			// 
			this->button10->Dock = System::Windows::Forms::DockStyle::Top;
			this->button10->Location = System::Drawing::Point(3, 128);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(162, 28);
			this->button10->TabIndex = 4;
			this->button10->Text = L"Sobel";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MainForm::button10_Click);
			// 
			// button11
			// 
			this->button11->Dock = System::Windows::Forms::DockStyle::Top;
			this->button11->Location = System::Drawing::Point(3, 100);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(162, 28);
			this->button11->TabIndex = 3;
			this->button11->Text = L"ColorRemove";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MainForm::button11_Click);
			// 
			// button12
			// 
			this->button12->Dock = System::Windows::Forms::DockStyle::Top;
			this->button12->Location = System::Drawing::Point(3, 72);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(162, 28);
			this->button12->TabIndex = 2;
			this->button12->Text = L"TicketYesNo";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MainForm::button12_Click);
			// 
			// button13
			// 
			this->button13->Dock = System::Windows::Forms::DockStyle::Top;
			this->button13->Location = System::Drawing::Point(3, 44);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(162, 28);
			this->button13->TabIndex = 1;
			this->button13->Text = L"greyscale";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MainForm::button13_Click);
			// 
			// button14
			// 
			this->button14->Dock = System::Windows::Forms::DockStyle::Top;
			this->button14->Location = System::Drawing::Point(3, 16);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(162, 28);
			this->button14->TabIndex = 0;
			this->button14->Text = L"transpose";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MainForm::button14_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button30);
			this->groupBox1->Controls->Add(this->button28);
			this->groupBox1->Controls->Add(this->button17);
			this->groupBox1->Controls->Add(this->button15);
			this->groupBox1->Controls->Add(this->button7);
			this->groupBox1->Controls->Add(this->button6);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Left;
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(168, 329);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"functions";
			// 
			// button30
			// 
			this->button30->Dock = System::Windows::Forms::DockStyle::Top;
			this->button30->Location = System::Drawing::Point(3, 296);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(162, 28);
			this->button30->TabIndex = 10;
			this->button30->Text = L"Laplasian";
			this->button30->UseVisualStyleBackColor = true;
			this->button30->Click += gcnew System::EventHandler(this, &MainForm::button30_Click);
			// 
			// button28
			// 
			this->button28->Dock = System::Windows::Forms::DockStyle::Top;
			this->button28->Location = System::Drawing::Point(3, 268);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(162, 28);
			this->button28->TabIndex = 9;
			this->button28->Text = L"Dif2";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &MainForm::button28_Click);
			// 
			// button17
			// 
			this->button17->Dock = System::Windows::Forms::DockStyle::Top;
			this->button17->Location = System::Drawing::Point(3, 240);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(162, 28);
			this->button17->TabIndex = 8;
			this->button17->Text = L"Cutting";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &MainForm::button17_Click);
			// 
			// button15
			// 
			this->button15->Dock = System::Windows::Forms::DockStyle::Top;
			this->button15->Location = System::Drawing::Point(3, 212);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(162, 28);
			this->button15->TabIndex = 7;
			this->button15->Text = L"Rotation";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &MainForm::button15_Click);
			// 
			// button7
			// 
			this->button7->Dock = System::Windows::Forms::DockStyle::Top;
			this->button7->Location = System::Drawing::Point(3, 184);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(162, 28);
			this->button7->TabIndex = 6;
			this->button7->Text = L"BlackWhite";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7_Click);
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Top;
			this->button6->Location = System::Drawing::Point(3, 156);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(162, 28);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Blur";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Top;
			this->button5->Location = System::Drawing::Point(3, 128);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(162, 28);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Dilation";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Top;
			this->button4->Location = System::Drawing::Point(3, 100);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(162, 28);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Erosion";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Top;
			this->button3->Location = System::Drawing::Point(3, 72);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(162, 28);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Equalizing";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Top;
			this->button2->Location = System::Drawing::Point(3, 44);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(162, 28);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Enhance";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Top;
			this->button1->Location = System::Drawing::Point(3, 16);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(162, 28);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Sharpen";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox3);
			this->tabPage2->Location = System::Drawing::Point(4, 4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(711, 335);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Background Removal";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button19);
			this->groupBox3->Controls->Add(this->button20);
			this->groupBox3->Controls->Add(this->button21);
			this->groupBox3->Controls->Add(this->button22);
			this->groupBox3->Controls->Add(this->button23);
			this->groupBox3->Controls->Add(this->button24);
			this->groupBox3->Controls->Add(this->button25);
			this->groupBox3->Controls->Add(this->button27);
			this->groupBox3->Controls->Add(this->button26);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Left;
			this->groupBox3->Location = System::Drawing::Point(3, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(168, 329);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"functions";
			// 
			// button19
			// 
			this->button19->Dock = System::Windows::Forms::DockStyle::Top;
			this->button19->Location = System::Drawing::Point(3, 240);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(162, 28);
			this->button19->TabIndex = 8;
			this->button19->UseVisualStyleBackColor = true;
			// 
			// button20
			// 
			this->button20->Dock = System::Windows::Forms::DockStyle::Top;
			this->button20->Location = System::Drawing::Point(3, 212);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(162, 28);
			this->button20->TabIndex = 7;
			this->button20->UseVisualStyleBackColor = true;
			// 
			// button21
			// 
			this->button21->Dock = System::Windows::Forms::DockStyle::Top;
			this->button21->Location = System::Drawing::Point(3, 184);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(162, 28);
			this->button21->TabIndex = 6;
			this->button21->UseVisualStyleBackColor = true;
			// 
			// button22
			// 
			this->button22->Dock = System::Windows::Forms::DockStyle::Top;
			this->button22->Location = System::Drawing::Point(3, 156);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(162, 28);
			this->button22->TabIndex = 5;
			this->button22->UseVisualStyleBackColor = true;
			// 
			// button23
			// 
			this->button23->Dock = System::Windows::Forms::DockStyle::Top;
			this->button23->Location = System::Drawing::Point(3, 128);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(162, 28);
			this->button23->TabIndex = 4;
			this->button23->UseVisualStyleBackColor = true;
			// 
			// button24
			// 
			this->button24->Dock = System::Windows::Forms::DockStyle::Top;
			this->button24->Location = System::Drawing::Point(3, 100);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(162, 28);
			this->button24->TabIndex = 3;
			this->button24->UseVisualStyleBackColor = true;
			// 
			// button25
			// 
			this->button25->Dock = System::Windows::Forms::DockStyle::Top;
			this->button25->Location = System::Drawing::Point(3, 72);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(162, 28);
			this->button25->TabIndex = 2;
			this->button25->Text = L"ContrastSISThreshold";
			this->button25->UseVisualStyleBackColor = true;
			this->button25->Click += gcnew System::EventHandler(this, &MainForm::button25_Click);
			// 
			// button27
			// 
			this->button27->Dock = System::Windows::Forms::DockStyle::Top;
			this->button27->Location = System::Drawing::Point(3, 44);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(162, 28);
			this->button27->TabIndex = 0;
			this->button27->Text = L"Demount/Mount";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &MainForm::button27_Click);
			// 
			// button26
			// 
			this->button26->Dock = System::Windows::Forms::DockStyle::Top;
			this->button26->Location = System::Drawing::Point(3, 16);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(162, 28);
			this->button26->TabIndex = 1;
			this->button26->Text = L"BorderDetecting";
			this->button26->UseVisualStyleBackColor = true;
			this->button26->Click += gcnew System::EventHandler(this, &MainForm::button26_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox4);
			this->tabPage3->Controls->Add(this->panelBlobs1);
			this->tabPage3->Location = System::Drawing::Point(4, 4);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(711, 335);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Normalizing";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->button40);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Left;
			this->groupBox4->Location = System::Drawing::Point(0, 61);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(162, 274);
			this->groupBox4->TabIndex = 4;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"functions";
			// 
			// button40
			// 
			this->button40->Dock = System::Windows::Forms::DockStyle::Top;
			this->button40->Location = System::Drawing::Point(3, 16);
			this->button40->Name = L"button40";
			this->button40->Size = System::Drawing::Size(156, 28);
			this->button40->TabIndex = 1;
			this->button40->Text = L"Marking";
			this->button40->UseVisualStyleBackColor = true;
			this->button40->Click += gcnew System::EventHandler(this, &MainForm::button40_Click);
			// 
			// panelBlobs1
			// 
			this->panelBlobs1->Controls->Add(this->panelBlobs2);
			this->panelBlobs1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelBlobs1->Location = System::Drawing::Point(0, 0);
			this->panelBlobs1->Name = L"panelBlobs1";
			this->panelBlobs1->Size = System::Drawing::Size(711, 61);
			this->panelBlobs1->TabIndex = 3;
			// 
			// panelBlobs2
			// 
			this->panelBlobs2->Controls->Add(this->trackBarBlobs);
			this->panelBlobs2->Controls->Add(this->label5);
			this->panelBlobs2->Controls->Add(this->label4);
			this->panelBlobs2->Controls->Add(this->label3);
			this->panelBlobs2->Controls->Add(this->label2);
			this->panelBlobs2->Controls->Add(this->labelBlobs);
			this->panelBlobs2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panelBlobs2->Location = System::Drawing::Point(0, 0);
			this->panelBlobs2->Name = L"panelBlobs2";
			this->panelBlobs2->Size = System::Drawing::Size(393, 61);
			this->panelBlobs2->TabIndex = 0;
			// 
			// trackBarBlobs
			// 
			this->trackBarBlobs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->trackBarBlobs->Location = System::Drawing::Point(80, 30);
			this->trackBarBlobs->Name = L"trackBarBlobs";
			this->trackBarBlobs->Size = System::Drawing::Size(233, 31);
			this->trackBarBlobs->TabIndex = 5;
			this->trackBarBlobs->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->trackBarBlobs->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::trackBarBlobs_MouseUp);
			// 
			// label5
			// 
			this->label5->Dock = System::Windows::Forms::DockStyle::Right;
			this->label5->Location = System::Drawing::Point(313, 30);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(40, 31);
			this->label5->TabIndex = 4;
			this->label5->Text = L">>>";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label5->Click += gcnew System::EventHandler(this, &MainForm::label5_Click);
			// 
			// label4
			// 
			this->label4->Dock = System::Windows::Forms::DockStyle::Right;
			this->label4->Location = System::Drawing::Point(353, 30);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 31);
			this->label4->TabIndex = 3;
			this->label4->Text = L">|";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label4->Click += gcnew System::EventHandler(this, &MainForm::label4_Click);
			// 
			// label3
			// 
			this->label3->Dock = System::Windows::Forms::DockStyle::Left;
			this->label3->Location = System::Drawing::Point(40, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 31);
			this->label3->TabIndex = 2;
			this->label3->Text = L"<<<";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label3->Click += gcnew System::EventHandler(this, &MainForm::label3_Click);
			// 
			// label2
			// 
			this->label2->Dock = System::Windows::Forms::DockStyle::Left;
			this->label2->Location = System::Drawing::Point(0, 30);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(40, 31);
			this->label2->TabIndex = 1;
			this->label2->Text = L"|<";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label2->Click += gcnew System::EventHandler(this, &MainForm::label2_Click);
			// 
			// labelBlobs
			// 
			this->labelBlobs->Dock = System::Windows::Forms::DockStyle::Top;
			this->labelBlobs->Location = System::Drawing::Point(0, 0);
			this->labelBlobs->Name = L"labelBlobs";
			this->labelBlobs->Size = System::Drawing::Size(393, 30);
			this->labelBlobs->TabIndex = 0;
			this->labelBlobs->Text = L"Blobs";
			this->labelBlobs->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->lblFileName, this->progressBar,
					this->lblCounterBlobs, this->lblTicketYesNo, this->lblAngle
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 385);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(719, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// lblFileName
			// 
			this->lblFileName->Name = L"lblFileName";
			this->lblFileName->Size = System::Drawing::Size(0, 17);
			// 
			// progressBar
			// 
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(100, 16);
			// 
			// lblCounterBlobs
			// 
			this->lblCounterBlobs->Name = L"lblCounterBlobs";
			this->lblCounterBlobs->Size = System::Drawing::Size(34, 17);
			this->lblCounterBlobs->Text = L"         ";
			// 
			// lblTicketYesNo
			// 
			this->lblTicketYesNo->Name = L"lblTicketYesNo";
			this->lblTicketYesNo->Size = System::Drawing::Size(16, 17);
			this->lblTicketYesNo->Text = L"...";
			// 
			// lblAngle
			// 
			this->lblAngle->Name = L"lblAngle";
			this->lblAngle->Size = System::Drawing::Size(13, 17);
			this->lblAngle->Text = L"  ";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->newToolStripMenuItem, this->eDBToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(719, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->loadImageToolStripMenuItem,
					this->loadScriptToolStripMenuItem, this->toolStripSeparator1, this->saveImageToolStripMenuItem, this->saveBlobToolStripMenuItem,
					this->saveBlobSrcToolStripMenuItem, this->saveScriptToolStripMenuItem, this->toolStripSeparator2, this->closeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadImageToolStripMenuItem
			// 
			this->loadImageToolStripMenuItem->Name = L"loadImageToolStripMenuItem";
			this->loadImageToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->loadImageToolStripMenuItem->Text = L"Load image";
			this->loadImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadToolStripMenuItem_Click);
			// 
			// loadScriptToolStripMenuItem
			// 
			this->loadScriptToolStripMenuItem->Name = L"loadScriptToolStripMenuItem";
			this->loadScriptToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->loadScriptToolStripMenuItem->Text = L"Load script";
			this->loadScriptToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadScriptToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// saveImageToolStripMenuItem
			// 
			this->saveImageToolStripMenuItem->Name = L"saveImageToolStripMenuItem";
			this->saveImageToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveImageToolStripMenuItem->Text = L"Save image";
			this->saveImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveImageToolStripMenuItem_Click);
			// 
			// saveBlobToolStripMenuItem
			// 
			this->saveBlobToolStripMenuItem->Name = L"saveBlobToolStripMenuItem";
			this->saveBlobToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveBlobToolStripMenuItem->Text = L"Save blob";
			this->saveBlobToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveBlobToolStripMenuItem_Click);
			// 
			// saveScriptToolStripMenuItem
			// 
			this->saveScriptToolStripMenuItem->Name = L"saveScriptToolStripMenuItem";
			this->saveScriptToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveScriptToolStripMenuItem->Text = L"Save script";
			this->saveScriptToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveScriptToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(149, 6);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->closeToolStripMenuItem->Text = L"Close";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::closeToolStripMenuItem_Click);
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
			// 
			// eDBToolStripMenuItem
			// 
			this->eDBToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->eDBManagerToolStripMenuItem,
					this->toolStripMenuItem2, this->toolStripSeparator3, this->loadEDBToolStripMenuItem1, this->saveEDBToolStripMenuItem1
			});
			this->eDBToolStripMenuItem->Name = L"eDBToolStripMenuItem";
			this->eDBToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->eDBToolStripMenuItem->Text = L"EDB";
			// 
			// eDBManagerToolStripMenuItem
			// 
			this->eDBManagerToolStripMenuItem->Name = L"eDBManagerToolStripMenuItem";
			this->eDBManagerToolStripMenuItem->Size = System::Drawing::Size(145, 22);
			this->eDBManagerToolStripMenuItem->Text = L"EDB manager";
			this->eDBManagerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::dBToolStripMenuItem_Click);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(145, 22);
			this->toolStripMenuItem2->Text = L"New EDB";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuItem2_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(142, 6);
			// 
			// loadEDBToolStripMenuItem1
			// 
			this->loadEDBToolStripMenuItem1->Name = L"loadEDBToolStripMenuItem1";
			this->loadEDBToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->loadEDBToolStripMenuItem1->Text = L"Load EDB";
			this->loadEDBToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::loadEDBToolStripMenuItem_Click);
			// 
			// saveEDBToolStripMenuItem1
			// 
			this->saveEDBToolStripMenuItem1->Name = L"saveEDBToolStripMenuItem1";
			this->saveEDBToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->saveEDBToolStripMenuItem1->Text = L"Save EDB";
			this->saveEDBToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::saveEDBToolStripMenuItem_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// saveBlobSrcToolStripMenuItem
			// 
			this->saveBlobSrcToolStripMenuItem->Name = L"saveBlobSrcToolStripMenuItem";
			this->saveBlobSrcToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveBlobSrcToolStripMenuItem->Text = L"Save blob src";
			this->saveBlobSrcToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveBlobSrcToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(719, 407);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"HIP. Test";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->panelBlobs1->ResumeLayout(false);
			this->panelBlobs2->ResumeLayout(false);
			this->panelBlobs2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarBlobs))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion




	private: System::Void Show()
	{

		if (src_mat != NULL)
			imshow("Source", src_mat[0]);
		
		if (blobs_counter > 0)
		{
			
			trackBarBlobs->Value = current_blob;
			Mat tmp;
			Mat tmp1;
			Mat tmp2;
			res_mat[0].copyTo(tmp);
			blobs[current_blob].image.copyTo(tmp1);
			blobs[current_blob].src.copyTo(tmp2);
			/*Preprocessing::ReSize3(&tmp1, 100, 150);
			Preprocessing::SisThreshold(&tmp1);*/
			imshow("Recognition", tmp1);
			imshow("Recognition source", tmp2);

			Preprocessing::MarkingSelected(&tmp, blobs[current_blob].location, blobs[current_blob].image.cols, blobs[current_blob].image.rows);
			imshow("Processed", tmp);
			
			//cv::String res = Preprocessing::GetCode(&blobs[current_blob].image, 4, 5);

			//System::String^ yop = gcnew  System::String(res.c_str());
			System::String^ yop = gcnew  System::String(blobs[current_blob].code.c_str());
			edbForm->NewRec(blobs[current_blob].code);
			//labelBlobs->Text = "Blobs. " + current_blob.ToString() + "(" + blobs_counter.ToString() + ")" + " Recognition-???" + " Size:" + blobs[current_blob].image.cols.ToString() + "X" + blobs[current_blob].image.rows.ToString() + " Code:" + yop;
			labelBlobs->Text = "Blobs. " + current_blob.ToString() + "(" + blobs_counter.ToString() + ")" + " Recognition-" + yop[yop->Length - 1] + " Size:" + blobs[current_blob].image.cols.ToString() + "X" + blobs[current_blob].image.rows.ToString() + " Code:" + yop;
			tmp.release();
			tmp1.release();
			tmp2.release();
		}
		else
		{
			if (res_mat != NULL)
				imshow("Processed", res_mat[0]);
			labelBlobs->Text = "Blobs. " + current_blob.ToString() + "(" + blobs_counter.ToString() + ")" + " Recognition-???";
		}
		
	}

	private: System::Void SetScript()
	{
		script_items = gcnew array<System::String^>{"Sharpen", "Enhance", "Equalizing", "Erosion", "Dilation", "Blur", "BlackWhite", "transpose", "GreyScale", "TicketYesNo", "ColorRemove", 
			"Sobel", "Threshold", "Invert", "FewBlobs", "Rotation", "Cutting", "DemountMount", "Contrast", "Dif2", "Canny", "Laplacian", "TopBottom","BorderDetecting", "ContrastSISThreshold", "Marking"};
		items_counter = 25;
	}

	private: System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		GC::Collect();
		OpenFileDialog^ od = gcnew  OpenFileDialog;
		od->Multiselect = true;
		od->Filter = "All files (*.*)| *.*|Bitmap files (*.bmp)| *.bmp|Enhanced Metafile files (*.emf)|*.emf|CompuServe Gif files (*.gif)|*.gif|Icon files (*.ico)|*.ico|Jpeg compressed files (*.jpg)|*.jpg|Portable Network Graphics files (*.png)|*.png|Tagged Image files (*.tiff)|*.tiff|Windows meta files (*.wmf)|*.wmf|Mimas DFD files (*.dfd)|*.dfd";
		od->FilterIndex = 1;
		od->RestoreDirectory = true;
		if (od->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			
			if (od->FileNames->Length > 1) return;

			

			if (src_mat != NULL)
				src_mat[0].release();

			System::String^ str = od->FileNames[0]->ToString();
			lblFileName->Text = str;
			cv::String t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];

			src_mat[0] = imread(t, IMREAD_COLOR);
			if (res_mat != NULL)
				res_mat[0].release();
			src_mat[0].copyTo(res_mat[0]);
			blobs_counter = 0;
			rec->NewImage();
			Show();
			lblTicketYesNo->Text = " Ticket = ???";
			lblCounterBlobs->Text = "???";
		}
		
		GC::Collect();
		
	}

	private: System::Void New()
	{
		res_mat[0].release();
		src_mat[0].copyTo(res_mat[0]);

		if (blobs_counter > 0)
		{
			for (int i = 0; i < blobs_counter; i++)
			{
				blobs[i].image.release();
			}
			//delete blobs;
			blobs_counter = 0;
			current_blob = 0;
		}

		Show();
	}

			

	private: System::Void Set()
	{
		SetScript();
		namedWindow("Source", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
		namedWindow("Processed", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
		namedWindow("Recognition", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
		namedWindow("Recognition source", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);

		moveWindow("Source", 10, 10);
		moveWindow("Processed", 20, 20);
		moveWindow("Recognition", 30, 30);
		moveWindow("Recognition source", 40, 40);

		src_mat = new Mat[1];
		res_mat = new Mat[1];
		koord = new cv::Point[1];
		old_koord = new cv::Point[1];
		koord[0].x = 0;
		koord[0].y = 0;
		old_koord[0].x = 0;
		old_koord[0].y = 0;

		edbForm = gcnew EDBForm();
		rec = new Recognition();
		edbForm->SetRec(rec);
		listBoxScript->Items->Clear();
		setMouseCallback("Processed", Preprocessing::onMouse, koord);

	}
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		New();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (res_mat[0].cols == 0) return;
		Sharpen();
		Show();
		SetListBox(0);
	}
	private: System::Void Sharpen()
	{
		Mat tmp;
		Preprocessing::Sharpen(res_mat[0], tmp);
		tmp.copyTo(res_mat[0]);
		tmp.release();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Enhance();
		Show();
		SetListBox(1);
	}
	private: System::Void Enhance()
	{
		Preprocessing::Enhance(&res_mat[0]);
	}
	private: System::Void saveImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Mat tmp = res_mat[0];
		SaveFileDialog^ sd = gcnew SaveFileDialog;
		sd->FileName = "";
		sd->Filter = "Bitmap files (*.bmp)| *.bmp|Enhanced Metafile files (*.emf)|*.emf|CompuServe Gif files (*.gif)|*.gif|Icon files (*.ico)|*.ico|Jpeg compressed files (*.jpg)|*.jpg|Portable Network Graphics files (*.png)|*.png|Tagged Image files (*.tiff)|*.tiff|Windows meta files (*.wmf)|*.wmf|Mimas DFD files (*.dfd)|*.dfd";
		sd->FilterIndex = 1;
		sd->RestoreDirectory = true;

		if (System::Windows::Forms::DialogResult::OK == sd->ShowDialog())
		{

			System::String^ str = sd->FileName->ToString();
			cv::String t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			imwrite(t, tmp);
		}
	}
	private: System::Void SetListBox(int item){

		listBoxScript->Items->Add(script_items[item]);
	}

	private: System::Void btClearScript_Click(System::Object^  sender, System::EventArgs^  e) {
		listBoxScript->Items->Clear();
	}
	private: System::Void saveScriptToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		SaveFileDialog^ sd = gcnew SaveFileDialog;
		sd->FileName = "";
		sd->Filter = "All files (*.*)| *.*|Text files (*.txt)| *.txt";
		sd->FilterIndex = 1;
		sd->RestoreDirectory = true;

		if (System::Windows::Forms::DialogResult::OK == sd->ShowDialog())
		{
			System::String^ str = sd->FileName->ToString();
			string t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			ofstream strm(t);
			strm << listBoxScript->Items->Count << '\n';
			for (int i = 0; i < listBoxScript->Items->Count; i++)
			{
				
				IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(listBoxScript->Items[i]->ToString());
				char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());

				strm << nativeString << '\n';
			}
			strm.close();
		}
	}
	private: System::Void loadScriptToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		OpenFileDialog^ od = gcnew  OpenFileDialog;
		//od->Multiselect = true;
		/*od->FileName = "";*/
		od->Filter = "All files (*.*)| *.*|Text files (*.txt)| *.txt";
		od->FilterIndex = 1;
		od->RestoreDirectory = true;
		if (od->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			listBoxScript->Items->Clear();
			System::String^ str = od->FileName->ToString();
			string t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			ifstream strm(t);
			char ss[20] = { 0 };
			strm.getline(ss, 20);
			str = "";
			for (int i = 0; i < 20; i++)
				str += Convert::ToChar(ss[i]);
			int counter = Convert::ToInt32(str);
			for (int i = 0; i < counter; i++)
			{
				char ss[20] = { 0 };
				strm.getline(ss, 20);
				str = "";
				for (int j = 0; j < 20; j++)
				{
					wchar_t p = Convert::ToChar(listBoxScript->Items[i]->ToString());
					str += p;
				}
				listBoxScript->Items->Add(Convert::ToString(str));
			}
			strm.close();
			lblbScriptName->Text = od->FileName->ToString();
		}
	}
	private: System::Void btRunScript_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (res_mat[0].cols == 0) return;
		int index = -1;
		progressBar->Maximum = listBoxScript->Items->Count;
		progressBar->Value = 0;
		int counter = 0;
		for (int i = 0; i < listBoxScript->Items->Count; i++)
		{
			index = -1;
			progressBar->Value = i;
			this->Refresh();
			listBoxScript->SelectedIndex = i;
			for (int j = 0; j < items_counter; j++)
			{
				int y = listBoxScript->Items[i]->ToString()->CompareTo(script_items[j]);
				if (y == 0)
					index = j;
			}
			switch (index)
			{
			case 0:
				Sharpen();
				break;
			case 1:
				Enhance();
				break;
			case 2:
				Equalizing();
				break;
			case 3:
				Erosion();
				break;
			case 4:
				Dilation();
				break;
			case 5:
				Blur();
				break;
			case 6:
				BlackWhite();
				break;
			case 7:
				Transpose();
				break;
			case 8:
				GreyScale();
				break;
			case 9:
			{
				/*int counter = 0;
				TicketYesNo(counter);*/
			}
				break;
			case 10:
				ColorRemove();
				break;
			case 11:
				Sobel();
				break;
			case 12:
				Threshold();
				break;
			case 13:
				Invert();
				break;
			case 14:
				FewBlobs();
				break;
			case 15:
				Rotation();
				break;
			case 16:
				Cutting(counter);
				break;
			case 17:
				//int counter = 0;
				DemountMount(counter);
				break;
			case 18:
				Contrast();
				break;
			case 19:
				Dif2();
				break;
			case 20:
				Canny();
				break;
			case 21:
				Laplacian();
				break;
			case 22:
				TopBottom();
				break;
			case 23:
				BorderDetecting(counter);
				break;
			case 24:
				ContrastSISThreshold(counter);
				break;
			case 25:
				Marking();
				break;
			}

		}
		progressBar->Value = 0;
		Show();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Equalizing();
		Show();
		SetListBox(2);
	}
	private: System::Void Equalizing()
	{

		Preprocessing::Equal(res_mat, 0);

	}


	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Erosion();
		Show();
		SetListBox(3);
	}
	private: System::Void Erosion()
	{

		Preprocessing::Erosion2(res_mat);

	}

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Dilation();
		Show();
		SetListBox(4);
	}

	private: System::Void Dilation()
	{

		Preprocessing::Dilation2(res_mat);

	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Blur();
		Show();
		SetListBox(5);
	}

	private: System::Void Blur()
	{
		Preprocessing::Blur(res_mat);
	}

	private: System::Void btDelScriptRow_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		listBoxScript->Items->RemoveAt(listBoxScript->SelectedIndex);
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//BlackWhite();
		SearchTicket();
		Show();
		SetListBox(6);
	}

	private: System::Void BlackWhite()
	{
		Preprocessing::BlackWhite(res_mat, 20, 50);
	}
			 private: System::Void SearchTicket()
			 {
				 /*Preprocessing::SearchTicket4(res_mat);*/
				 Preprocessing::SearchTicket4_bottom(res_mat);
				 Preprocessing::SearchTicket4(res_mat);
			 }

	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Transpose();
		Show();
		SetListBox(7);
	}

			 private: System::Void Transpose()
			 {
				 Preprocessing::Transpose_(res_mat);
			 }
	private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		GreyScale();
		Show();
		SetListBox(8);
	}
			 private: System::Void GreyScale()
			 {
				 //Preprocessing::GreyScale(res_mat);
				 Preprocessing::GrayScale3Ch(res_mat);
			 }
	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		int counter = 0;
		bool res = TicketYesNo(counter);
		if (res)
			lblTicketYesNo->Text = " Ticket = Yes";
		else
			lblTicketYesNo->Text = " Ticket = No";
		lblCounterBlobs->Text = counter.ToString();
		Show();
		SetListBox(9);
	}
private: bool TicketYesNo(int& counter)
{
	return Preprocessing::TicketYesNo_0(res_mat, counter);
}


	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		ColorRemove();
		Show();
		SetListBox(10);
	}
			 private: System::Void ColorRemove()
			 {

				 Preprocessing::ColorRemove(res_mat);

			 }
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Sobel();
		Show();
		SetListBox(11);
	}
			 private: System::Void Sobel()
			 {

				 Preprocessing::Sobel_(res_mat);
				 //Preprocessing::Sobel2(res_mat);

			 }
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Threshold();
		Show();
		SetListBox(12);
	}
			 private: System::Void Threshold()
			 {

				 //Preprocessing::Threshold(res_mat);
				 Preprocessing::SisThreshold(res_mat);

			 }
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Invert();
		Show();
		SetListBox(13);
	}

			 private: System::Void Invert()
			 {

				 Preprocessing::Invert(res_mat);

			 }

	private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		FewBlobs();
		Show();
		SetListBox(14);
	}
			 private: System::Void FewBlobs()
			 {
				 Preprocessing::RemoveBigSmallBlobs(res_mat);
				 /*int res = Preprocessing::FewBlobsTop2(res_mat);
				 lblCounterBlobs->Text = res.ToString();*/

			 }
	private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
		
		Rotation();
		Show();
		SetListBox(15);
	}
			  private: System::Void Rotation()
			  {

				  double res =Preprocessing::Rotation(res_mat);
				  lblAngle->Text = "Angle=" + res.ToString("F1");
				  

			  }
	private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
		int counter = 0;
		bool res = Cutting(counter);
		if (res)
			lblTicketYesNo->Text = " Ticket = Yes";
		else
			lblTicketYesNo->Text = " Ticket = No";
		lblCounterBlobs->Text = counter.ToString();
		Show();
		SetListBox(16);

	}
			
private: bool Cutting(int& counter)
			 {
				 return Preprocessing::RotateAndCut(res_mat, counter);
				 //return Preprocessing::TicketYesNo(res_mat, counter);
				 //Preprocessing::Cutting(res_mat);
				 //lblAngle->Text = "Angle=" + res.ToString("F1");

			 }
	private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		int counter = 0;
		bool res = DemountMount(counter);
		if (res)
			lblTicketYesNo->Text = " Ticket = Yes";
		else
			lblTicketYesNo->Text = " Ticket = No";
		lblCounterBlobs->Text = counter.ToString();
		Show();
		SetListBox(17);
		if (!res)
		{
			MessageBox::Show("Ticket = NO");
		}
	}
			  private: bool DemountMount(int& counter)
			  {
				 return Preprocessing::TicketYesNo1(res_mat, counter);
			  }
	private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Contrast();
		Show();
		SetListBox(18);
	}
			 private: System::Void Contrast()
			 {
				 //Preprocessing::ContrastBrightness(res_mat, 4.0, 0);
				 Preprocessing::Contrast(res_mat, 100);
			 }
	private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Dif2();
		Show();
		SetListBox(19);
	}
			 private: System::Void Dif2()
			 {
				 //Preprocessing::ContrastBrightness(res_mat, 4.0, 0);
				 Preprocessing::Df2(src_mat, res_mat);
			 }
	private: System::Void button29_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Canny();
		Show();
		SetListBox(20);
	}
			 private: System::Void Canny()
			 {
				 Preprocessing::Canny_(res_mat);
			 }
	private: System::Void button30_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Laplacian();
		Show();
		SetListBox(21);
	}
			 private: System::Void Laplacian()
			 {
				 Preprocessing::Laplacian_(res_mat);
			 }
	private: System::Void button31_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		/*TopBottom();
		Show();
		SetListBox(22);*/
		/*Preprocessing::VertStich(res_mat);
		Show();*/
		//Preprocessing::HorStich(res_mat, 3/*av_w / 12 + 1*/);

		Preprocessing::MSER_Test(res_mat);
		Show();
	}
			 private: System::Void TopBottom()
			 {
				 Preprocessing::TopBottom(res_mat);
			 }
	private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) 
	{

		int counter = 0;
		bool res = BorderDetecting(counter);
		if (res)
			lblTicketYesNo->Text = " Ticket = Yes";
		else
			lblTicketYesNo->Text = " Ticket = No";
		lblCounterBlobs->Text = counter.ToString();
		Show();
		SetListBox(23);
		if (!res)
		{
			MessageBox::Show("Ticket = NO");
		}
	}
			 private: bool BorderDetecting(int& counter)
			 {
				 return Preprocessing::TicketYesNo(res_mat, counter);
			 }
	private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		int counter = 0;
		bool res = ContrastSISThreshold(counter);
		if (res)
			lblTicketYesNo->Text = " Ticket = Yes";
		else
			lblTicketYesNo->Text = " Ticket = No";
		lblCounterBlobs->Text = counter.ToString();
		Show();
		SetListBox(24);
		if (!res)
		{
			MessageBox::Show("Ticket = NO");
		}
	}
			  private: bool ContrastSISThreshold(int& counter)
			  {
				  return Preprocessing::TicketYesNo2(res_mat, counter);
			  }
	private: System::Void button40_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Marking();
		edbForm->NewListBoxEDB();
		std::string tmp = rec->edb_file_name;

		System::String^ yop = "";
		for (int i = 0; i < tmp.length(); i++)
			yop += tmp[i];
		edbForm->lblNameEDB->Text = yop;
		SetListBox(25);
		
		Show();
		
	}
			 
	

	private: System::Void Marking()
			 {
				 int temp = 0;
				 blobs = Preprocessing::Marking2(res_mat, temp);
				 if (temp > 0)
				 {
					 blobs_counter = temp;
					 trackBarBlobs->Value = 0;
					 trackBarBlobs->Maximum = blobs_counter - 1;
					 current_blob = 0;
					 Show();
				 }

			 }
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		current_blob = 0;
		
		Show();
	}
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (blobs_counter > 0)
		{
			current_blob = blobs_counter - 1;
			
			Show();
		}
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (current_blob - 1 > 0)
		{
			current_blob--;
			Show();
		}
	}
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (current_blob + 1 < blobs_counter)
		{
			current_blob++;
			Show();
		}
	}
	private: System::Void trackBarBlobs_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		current_blob = trackBarBlobs->Value;
		Show();
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		if (koord[0].x == old_koord[0].x && koord[0].y == old_koord[0].y) return;
		old_koord[0].x = koord[0].x;
		old_koord[0].y = koord[0].y;

		int val = Preprocessing::FindBlob(koord[0].x, koord[0].y, blobs, blobs_counter);

		if (val != -1)
			current_blob = val;
		Show();
	}
	private: System::Void saveBlobToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
		if (blobs_counter <= 0) return;
		
		Mat tmp = blobs[current_blob].image;
		SaveFileDialog^ sd = gcnew SaveFileDialog;
		sd->FileName = "";
		sd->Filter = "Bitmap files (*.bmp)| *.bmp|Enhanced Metafile files (*.emf)|*.emf|CompuServe Gif files (*.gif)|*.gif|Icon files (*.ico)|*.ico|Jpeg compressed files (*.jpg)|*.jpg|Portable Network Graphics files (*.png)|*.png|Tagged Image files (*.tiff)|*.tiff|Windows meta files (*.wmf)|*.wmf|Mimas DFD files (*.dfd)|*.dfd";
		sd->FilterIndex = 1;
		sd->RestoreDirectory = true;

		if (System::Windows::Forms::DialogResult::OK == sd->ShowDialog())
		{

			System::String^ str = sd->FileName->ToString();
			cv::String t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			imwrite(t, tmp);
		}
	}
	private: System::Void dBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		edbForm->Visible = !edbForm->Visible;
		/*Recognition* rcg = new Recognition();
		rcg->SetEDB("C://0test.txt");*/
		
	}
	private: System::Void button32_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		int str_counter = 0;
		current_blob = 0;

		std::string* ret= rec->SetImage(res_mat, str_counter);

		//rec->Get_Strings();
		if (str_counter == 1)
		{
			System::String^ code = gcnew System::String(ret[0].c_str());
			MessageBox::Show("Error. Code=" + code, "Warning");
			blobs_counter = 0;
			return;
		}

		//rec->SetBlobSourceImage(src_mat);
		//rec->ReProcessing(src_mat);

		int t = 0;
		blobs = rec->GetBlobs(t);
		blobs_counter = t;
		trackBarBlobs->Value = 0;
		trackBarBlobs->Maximum = blobs_counter - 1;


		System::String^ tmp = gcnew System::String(rec->edb_file_name.c_str());
		edbForm->lblNameEDB->Text = tmp;
		edbForm->NewListBoxEDB();
		listBoxScript->Items->Clear();
		for (int i = 0; i < str_counter; i++)
		{
			System::String^ tmp = gcnew System::String(ret[i].c_str());
			listBoxScript->Items->Add(tmp);
		}
		Show();
	}
	private: System::Void loadEDBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		OpenFileDialog^ od = gcnew  OpenFileDialog;
		od->Multiselect = true;
		od->Filter = "EDB files (*.edb)| *.edb|All files (*.*)| *.*";
		od->FilterIndex = 1;
		od->RestoreDirectory = true;
		if (od->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			int counter = od->FileNames->Length;
			if (counter == 1)
			{
				System::String^ str = od->FileName->ToString();
				std::string t = "";
				for (int ii = 0; ii < str->Length; ii++)
					t += str[ii];
				rec->ReadEDB(t);
				edbForm->lblNameEDB->Text = od->FileName->ToString();
				edbForm->NewListBoxEDB();
			}
			else
			{
				std::string* file_names = new std::string[counter];
				for (int i = 0; i < od->FileNames->Length; i++)
				{
					System::String^ str = od->FileNames[i]->ToString();
					cv::String t = "";
					for (int ii = 0; ii < str->Length; ii++)
						t += str[ii];
					file_names[i] = t;
				}
				rec->SetEDB_fileNames(file_names, counter);
			}
		}
	}
	private: System::Void saveEDBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		SaveFileDialog^ sd = gcnew SaveFileDialog;
		sd->FileName = "";
		sd->Filter = "EDB files (*.edb)| *.edb|All files (*.*)| *.*";
		sd->FilterIndex = 1;
		sd->RestoreDirectory = true;

		if (System::Windows::Forms::DialogResult::OK == sd->ShowDialog())
		{
			System::String^ str = sd->FileName->ToString();
			std::string t = "";
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			rec->WriteEDB(t);
			edbForm->lblNameEDB->Text = sd->FileName->ToString();
			
		}
	}
	private: System::Void button33_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	private: System::Void newEDBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}

	private: System::Void toolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		rec->NewEDB();
		edbForm->NewEDB();
	}

	private: System::Void saveBlobSrcToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (blobs_counter <= 0) return;

		Mat tmp = blobs[current_blob].src;
		SaveFileDialog^ sd = gcnew SaveFileDialog;
		sd->FileName = "";
		sd->Filter = "Bitmap files (*.bmp)| *.bmp|Enhanced Metafile files (*.emf)|*.emf|CompuServe Gif files (*.gif)|*.gif|Icon files (*.ico)|*.ico|Jpeg compressed files (*.jpg)|*.jpg|Portable Network Graphics files (*.png)|*.png|Tagged Image files (*.tiff)|*.tiff|Windows meta files (*.wmf)|*.wmf|Mimas DFD files (*.dfd)|*.dfd";
		sd->FilterIndex = 1;
		sd->RestoreDirectory = true;

		if (System::Windows::Forms::DialogResult::OK == sd->ShowDialog())
		{

			System::String^ str = sd->FileName->ToString();
			cv::String t = cv::String();
			for (int ii = 0; ii < str->Length; ii++)
				t += str[ii];
			imwrite(t, tmp);
		}
	}
};
}
