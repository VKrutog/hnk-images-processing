#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;



[STAThread]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BR2::MainForm form;
	//DelB::FormTesting form;
	Application::Run(%form);
}
