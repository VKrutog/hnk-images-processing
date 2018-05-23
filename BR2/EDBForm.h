#pragma once
#include "Recognition.h"

namespace BR2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Summary for EDBForm
	/// </summary>
	public ref class EDBForm : public System::Windows::Forms::Form
	{
	public:
		EDBForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EDBForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:




	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::Panel^  panel3;







	private: System::Windows::Forms::Panel^  panel6;
	private: System::Windows::Forms::Label^  lblDif;







	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  tbLet;





	private: System::Windows::Forms::ListBox^  lb1;









	public: System::Windows::Forms::ToolStripStatusLabel^  lblNameEDB;
	private:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		Recognition* rec;
	private: System::Windows::Forms::Label^  lblCode;
			 int current;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->lblNameEDB = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->lb1 = (gcnew System::Windows::Forms::ListBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->lblDif = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->lblCode = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tbLet = (gcnew System::Windows::Forms::TextBox());
			this->statusStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->lblNameEDB });
			this->statusStrip1->Location = System::Drawing::Point(0, 508);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(505, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// lblNameEDB
			// 
			this->lblNameEDB->Name = L"lblNameEDB";
			this->lblNameEDB->Size = System::Drawing::Size(16, 17);
			this->lblNameEDB->Text = L"...";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->lb1);
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(505, 508);
			this->panel1->TabIndex = 2;
			// 
			// lb1
			// 
			this->lb1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lb1->FormattingEnabled = true;
			this->lb1->Location = System::Drawing::Point(0, 66);
			this->lb1->Name = L"lb1";
			this->lb1->Size = System::Drawing::Size(505, 442);
			this->lb1->TabIndex = 2;
			this->lb1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EDBForm::lb1_KeyDown);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->panel6);
			this->panel3->Controls->Add(this->panel4);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(505, 66);
			this->panel3->TabIndex = 1;
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->lblDif);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(0, 25);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(505, 31);
			this->panel6->TabIndex = 4;
			// 
			// lblDif
			// 
			this->lblDif->Dock = System::Windows::Forms::DockStyle::Left;
			this->lblDif->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblDif->Location = System::Drawing::Point(0, 0);
			this->lblDif->Name = L"lblDif";
			this->lblDif->Size = System::Drawing::Size(71, 31);
			this->lblDif->TabIndex = 2;
			this->lblDif->Text = L"...";
			this->lblDif->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->lblCode);
			this->panel4->Controls->Add(this->button5);
			this->panel4->Controls->Add(this->tbLet);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(505, 25);
			this->panel4->TabIndex = 2;
			// 
			// lblCode
			// 
			this->lblCode->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblCode->ForeColor = System::Drawing::Color::Red;
			this->lblCode->Location = System::Drawing::Point(0, 0);
			this->lblCode->Name = L"lblCode";
			this->lblCode->Size = System::Drawing::Size(389, 25);
			this->lblCode->TabIndex = 4;
			this->lblCode->Text = L"...";
			this->lblCode->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Right;
			this->button5->ForeColor = System::Drawing::Color::Black;
			this->button5->Location = System::Drawing::Point(389, 0);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(56, 25);
			this->button5->TabIndex = 3;
			this->button5->Text = L"Insert";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &EDBForm::button5_Click);
			// 
			// tbLet
			// 
			this->tbLet->Dock = System::Windows::Forms::DockStyle::Right;
			this->tbLet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbLet->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->tbLet->Location = System::Drawing::Point(445, 0);
			this->tbLet->Name = L"tbLet";
			this->tbLet->Size = System::Drawing::Size(60, 26);
			this->tbLet->TabIndex = 2;
			this->tbLet->Text = L"...";
			this->tbLet->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// EDBForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(505, 530);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->statusStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"EDBForm";
			this->Text = L"EDB manager";
			this->TopMost = true;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &EDBForm::EDBForm_FormClosing);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void EDBForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
	{
		e->Cancel = true;
		this->Visible = false;
	}

	public: System::Void SetRec(Recognition* _rec)
	{
		rec = _rec;
		current = 0;
	}
	public: System::Void NewRec(std::string str)
	{
		int dif = 0;
		current= rec->BestVar(str, dif);
		lb1->SelectedIndex = current;
		System::String^ tmp = gcnew System::String(str.c_str());
		lblCode->Text = tmp;
		std::string tmp2 = "";
		tmp2+=(str[str.length() - 1]);
		System::String^ tmp1 = gcnew System::String(tmp2.c_str());
		tbLet->Text = tmp1;
		lblDif->Text = dif.ToString();
	}

	public: System::Void NewListBoxEDB()
	{
		lb1->Items->Clear();
		for (int i = 0; i < rec->edb_counter; i++)
		{
			System::String^ tmp = gcnew System::String(rec->edb[i].c_str());
			lb1->Items->Add(tmp);
		}
	}

	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		rec->DRec(lb1->SelectedIndex);
		NewListBoxEDB();
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		lb1->Items->Clear();
		rec->NewEDB();
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		std::string tmp ="";
		for (int ii = 0; ii < lblCode->Text->Length; ii++)
			tmp += lblCode->Text[ii];
		tmp = rec->ChangeLet(tmp, tbLet->Text[0]);
		rec->ARec(tmp);
		NewListBoxEDB();
	}
	public: System::Void NewEDB()
	{
		lb1->Items->Clear();
		lblCode->Text = "";
		tbLet->Text = "";
		lblDif->Text = "";
		lblNameEDB->Text = "";
	}

	private: System::Void lb1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
	{
		if (e->KeyCode == Keys::Delete)
		{
			rec->DRec(lb1->SelectedIndex);
			NewListBoxEDB();
		}

	}
};
}
