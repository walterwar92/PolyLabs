#pragma once

namespace DatabaseManagerApp {

	using namespace System;
	using namespace System::Data;
	using namespace System::Windows::Forms;
	using namespace System::Data::SqlClient;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::TextBox^ txtID;
		System::Windows::Forms::TextBox^ txtName;
		System::Windows::Forms::TextBox^ txtPhone;
		System::Windows::Forms::TextBox^ txtEmail;
		System::Windows::Forms::Button^ btnAdd;
		System::Windows::Forms::Button^ btnSearch;
		System::Windows::Forms::Button^ btnDelete;
		System::Windows::Forms::Button^ btnViewAll;

		System::Windows::Forms::DataGridView^ dataGridView;
		System::Windows::Forms::TextBox^ txtServer;
		System::Windows::Forms::TextBox^ txtUsername;
		System::Windows::Forms::TextBox^ txtPassword;
		System::Windows::Forms::Button^ btnConnect;

		String^ connectionString;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ labelServer;
	private: System::Windows::Forms::Label^ labelUsername;
	private: System::Windows::Forms::Label^ labelPassword;

	private: System::ComponentModel::IContainer^ components;

	private:
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->txtID = (gcnew System::Windows::Forms::TextBox());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->txtPhone = (gcnew System::Windows::Forms::TextBox());
			this->txtEmail = (gcnew System::Windows::Forms::TextBox());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnViewAll = (gcnew System::Windows::Forms::Button());
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtServer = (gcnew System::Windows::Forms::TextBox());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnConnect = (gcnew System::Windows::Forms::Button());
			this->labelServer = (gcnew System::Windows::Forms::Label());
			this->labelUsername = (gcnew System::Windows::Forms::Label());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// txtID
			// 
			this->txtID->Location = System::Drawing::Point(20, 160);
			this->txtID->Name = L"txtID";
			this->txtID->Size = System::Drawing::Size(200, 22);
			this->txtID->TabIndex = 7;
			// 
			// txtName
			// 
			this->txtName->Location = System::Drawing::Point(20, 190);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(200, 22);
			this->txtName->TabIndex = 8;
			// 
			// txtPhone
			// 
			this->txtPhone->Location = System::Drawing::Point(20, 220);
			this->txtPhone->Name = L"txtPhone";
			this->txtPhone->Size = System::Drawing::Size(200, 22);
			this->txtPhone->TabIndex = 9;
			// 
			// txtEmail
			// 
			this->txtEmail->Location = System::Drawing::Point(20, 250);
			this->txtEmail->Name = L"txtEmail";
			this->txtEmail->Size = System::Drawing::Size(200, 22);
			this->txtEmail->TabIndex = 10;
			// 
			// btnAdd
			// 
			this->btnAdd->Location = System::Drawing::Point(20, 280);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(100, 30);
			this->btnAdd->TabIndex = 11;
			this->btnAdd->Text = L"Добавить";
			this->btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
			// 
			// btnSearch
			// 
			this->btnSearch->Location = System::Drawing::Point(130, 280);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(100, 30);
			this->btnSearch->TabIndex = 12;
			this->btnSearch->Text = L"Найти";
			this->btnSearch->Click += gcnew System::EventHandler(this, &MainForm::btnSearch_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Location = System::Drawing::Point(20, 320);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(100, 30);
			this->btnDelete->TabIndex = 13;
			this->btnDelete->Text = L"Удалить";
			this->btnDelete->Click += gcnew System::EventHandler(this, &MainForm::btnDelete_Click);
			// 
			// btnViewAll
			// 
			this->btnViewAll->Location = System::Drawing::Point(130, 320);
			this->btnViewAll->Name = L"btnViewAll";
			this->btnViewAll->Size = System::Drawing::Size(100, 30);
			this->btnViewAll->TabIndex = 14;
			this->btnViewAll->Text = L"Посмотреть все";
			this->btnViewAll->Click += gcnew System::EventHandler(this, &MainForm::btnViewAll_Click);
			// 
			// dataGridView
			// 
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView->Location = System::Drawing::Point(240, 160);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->Size = System::Drawing::Size(300, 300);
			this->dataGridView->TabIndex = 15;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 23);
			this->label1->TabIndex = 19;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 23);
			this->label2->TabIndex = 18;
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(0, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(100, 23);
			this->label3->TabIndex = 17;
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(0, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(100, 23);
			this->label4->TabIndex = 16;
			// 
			// txtServer
			// 
			this->txtServer->Location = System::Drawing::Point(144, 20);
			this->txtServer->Name = L"txtServer";
			this->txtServer->Size = System::Drawing::Size(200, 22);
			this->txtServer->TabIndex = 0;
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(144, 50);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(200, 22);
			this->txtUsername->TabIndex = 2;
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(144, 78);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(200, 22);
			this->txtPassword->TabIndex = 4;
			this->txtPassword->UseSystemPasswordChar = true;
			// 
			// btnConnect
			// 
			this->btnConnect->Location = System::Drawing::Point(144, 106);
			this->btnConnect->Name = L"btnConnect";
			this->btnConnect->Size = System::Drawing::Size(100, 30);
			this->btnConnect->TabIndex = 6;
			this->btnConnect->Text = L"Подключиться";
			this->btnConnect->Click += gcnew System::EventHandler(this, &MainForm::btnConnect_Click);
			// 
			// labelServer
			// 
			this->labelServer->AutoSize = true;
			this->labelServer->Location = System::Drawing::Point(20, 23);
			this->labelServer->Name = L"labelServer";
			this->labelServer->Size = System::Drawing::Size(118, 13);
			this->labelServer->TabIndex = 1;
			this->labelServer->Text = L"Сервер (Data Source)";
			// 
			// labelUsername
			// 
			this->labelUsername->AutoSize = true;
			this->labelUsername->Location = System::Drawing::Point(20, 53);
			this->labelUsername->Name = L"labelUsername";
			this->labelUsername->Size = System::Drawing::Size(105, 13);
			this->labelUsername->TabIndex = 3;
			this->labelUsername->Text = L"Имя пользователя";
			// 
			// labelPassword
			// 
			this->labelPassword->AutoSize = true;
			this->labelPassword->Location = System::Drawing::Point(20, 83);
			this->labelPassword->Name = L"labelPassword";
			this->labelPassword->Size = System::Drawing::Size(47, 13);
			this->labelPassword->TabIndex = 5;
			this->labelPassword->Text = L"Пароль";
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(600, 480);
			this->Controls->Add(this->dataGridView);
			this->Controls->Add(this->btnViewAll);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->txtEmail);
			this->Controls->Add(this->txtPhone);
			this->Controls->Add(this->txtName);
			this->Controls->Add(this->txtID);
			this->Controls->Add(this->btnConnect);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->labelPassword);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->labelUsername);
			this->Controls->Add(this->txtServer);
			this->Controls->Add(this->labelServer);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MainForm";
			this->Text = L"Управление БД";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	private:
		void MainForm::btnConnect_Click(System::Object^ sender, System::EventArgs^ e) {
			// Получаем значения из текстовых полей
			String^ server = txtServer->Text;
			String^ username = txtUsername->Text;
			String^ password = txtPassword->Text;

			// Формируем строку подключения
			connectionString = "Data Source=" + server + ";User ID=" + username + ";Password=" + password + ";";

			try {
				// Проверяем соединение
				SqlConnection^ connection = gcnew SqlConnection(connectionString);
				connection->Open();
				MessageBox::Show("Подключение успешно!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				connection->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка подключения: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {

			String^ id = txtID->Text;
			String^ name = txtName->Text;
			String^ phone = txtPhone->Text;
			String^ email = txtEmail->Text;

			try {
				// Создаем подключение
				SqlConnection^ connection = gcnew SqlConnection(connectionString);
				connection->Open();

				// Создаем команду
				String^ query = "INSERT INTO Clients (ID, Name, Phone, Email) VALUES (@ID, @Name, @Phone, @Email)";
				SqlCommand^ command = gcnew SqlCommand(query, connection);
				command->Parameters->AddWithValue("@ID", id);
				command->Parameters->AddWithValue("@Name", name);
				command->Parameters->AddWithValue("@Phone", phone);
				command->Parameters->AddWithValue("@Email", email);

				// Выполняем запрос и проверяем, были ли затронуты строки
				int rowsAffected = command->ExecuteNonQuery();
				if (rowsAffected > 0) {
					MessageBox::Show("Данные успешно добавлены!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Ошибка при добавлении данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

				connection->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void MainForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
			// Логика поиска записи в базе данных
			String^ id = txtID->Text;

			if (connectionString == "") {
				MessageBox::Show("Сначала подключитесь к базе данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				SqlConnection^ connection = gcnew SqlConnection(connectionString);
				connection->Open();

				String^ query = "SELECT Name, Phone, Email FROM Clients WHERE ID = @ID";
				SqlCommand^ command = gcnew SqlCommand(query, connection);
				command->Parameters->AddWithValue("@ID", id);

				SqlDataReader^ reader = command->ExecuteReader();
				if (reader->Read()) {
					txtName->Text = reader["Name"]->ToString();
					txtPhone->Text = reader["Phone"]->ToString();
					txtEmail->Text = reader["Email"]->ToString();
				}
				else {
					MessageBox::Show("Запись не найдена.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				reader->Close();
				connection->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка поиска записи: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void MainForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
			// Логика удаления записи из базы данных
			String^ id = txtID->Text;

			if (connectionString == "") {
				MessageBox::Show("Сначала подключитесь к базе данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				SqlConnection^ connection = gcnew SqlConnection(connectionString);
				connection->Open();

				String^ query = "DELETE FROM Clients WHERE ID = @ID";
				SqlCommand^ command = gcnew SqlCommand(query, connection);
				command->Parameters->AddWithValue("@ID", id);

				int rowsAffected = command->ExecuteNonQuery();
				if (rowsAffected > 0) {
					MessageBox::Show("Запись удалена!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Запись не найдена.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				connection->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка удаления записи: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void MainForm::btnViewAll_Click(System::Object^ sender, System::EventArgs^ e) {
			// Логика просмотра всех записей из базы данных
			if (connectionString == "") {
				MessageBox::Show("Сначала подключитесь к базе данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			try {
				SqlConnection^ connection = gcnew SqlConnection(connectionString);
				connection->Open();

				String^ query = "SELECT ID, Name, Phone, Email FROM Clients";
				SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, connection);
				DataTable^ dataTable = gcnew DataTable();
				adapter->Fill(dataTable);
				dataGridView->DataSource = dataTable;

				connection->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка получения записей: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
