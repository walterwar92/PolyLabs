#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Data::SqlClient;

[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    DatabaseManagerApp::MainForm mainForm;
    Application::Run(% mainForm);
    return 0;
}

namespace DatabaseManagerApp {


}
