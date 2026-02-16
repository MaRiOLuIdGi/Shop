#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace OnlineShopApp {

    public ref class AddCustomerForm : public Form
    {
    public:
        AddCustomerForm(void)
        {
            InitializeComponent();
            this->Text = L"Добавление нового клиента";
        }

        AddCustomerForm(String^ lastName, String^ firstName, String^ phone, String^ email, bool hasDiscount, double discount)
        {
            InitializeComponent();
            this->Text = L"Редактирование клиента";

            textBoxLastName->Text = lastName;
            textBoxFirstName->Text = firstName;
            textBoxPhone->Text = phone;
            textBoxEmail->Text = email;
            checkBoxDiscount->Checked = hasDiscount;

            if (hasDiscount)
            {
                numericDiscount->Value = (Decimal)discount;
                numericDiscount->Enabled = true;
            }
        }

    protected:
        ~AddCustomerForm()
        {
            if (components)
            {
                delete components;
            }
        }

    public:
        property String^ LastName
        {
            String^ get() { return textBoxLastName->Text->Trim(); }
        }

        property String^ FirstName
        {
            String^ get() { return textBoxFirstName->Text->Trim(); }
        }

        property String^ Phone
        {
            String^ get() { return textBoxPhone->Text->Trim(); }
        }

        property String^ Email
        {
            String^ get() { return textBoxEmail->Text->Trim(); }
        }

        property bool HasDiscount
        {
            bool get() { return checkBoxDiscount->Checked; }
        }

        property double Discount
        {
            double get() { return (double)numericDiscount->Value; }
        }

    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::TextBox^ textBoxLastName;
        System::Windows::Forms::TextBox^ textBoxFirstName;
        System::Windows::Forms::TextBox^ textBoxPhone;
        System::Windows::Forms::TextBox^ textBoxEmail;
        System::Windows::Forms::CheckBox^ checkBoxDiscount;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::NumericUpDown^ numericDiscount;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->textBoxLastName = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->textBoxFirstName = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->textBoxPhone = (gcnew System::Windows::Forms::TextBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->textBoxEmail = (gcnew System::Windows::Forms::TextBox());
            this->checkBoxDiscount = (gcnew System::Windows::Forms::CheckBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->numericDiscount = (gcnew System::Windows::Forms::NumericUpDown());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericDiscount))->BeginInit();
            this->SuspendLayout();

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(20, 20);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(56, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Фамилия:";

            // textBoxLastName
            this->textBoxLastName->Location = System::Drawing::Point(120, 17);
            this->textBoxLastName->Name = L"textBoxLastName";
            this->textBoxLastName->Size = System::Drawing::Size(200, 20);
            this->textBoxLastName->TabIndex = 1;

            // label2
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(20, 50);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(32, 13);
            this->label2->TabIndex = 2;
            this->label2->Text = L"Имя:";

            // textBoxFirstName
            this->textBoxFirstName->Location = System::Drawing::Point(120, 47);
            this->textBoxFirstName->Name = L"textBoxFirstName";
            this->textBoxFirstName->Size = System::Drawing::Size(200, 20);
            this->textBoxFirstName->TabIndex = 3;

            // label3
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(20, 80);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(55, 13);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Телефон:";

            // textBoxPhone
            this->textBoxPhone->Location = System::Drawing::Point(120, 77);
            this->textBoxPhone->Name = L"textBoxPhone";
            this->textBoxPhone->Size = System::Drawing::Size(200, 20);
            this->textBoxPhone->TabIndex = 5;

            // label4
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(20, 110);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(38, 13);
            this->label4->TabIndex = 6;
            this->label4->Text = L"Email:";

            // textBoxEmail
            this->textBoxEmail->Location = System::Drawing::Point(120, 107);
            this->textBoxEmail->Name = L"textBoxEmail";
            this->textBoxEmail->Size = System::Drawing::Size(200, 20);
            this->textBoxEmail->TabIndex = 7;

            // checkBoxDiscount
            this->checkBoxDiscount->AutoSize = true;
            this->checkBoxDiscount->Location = System::Drawing::Point(20, 140);
            this->checkBoxDiscount->Name = L"checkBoxDiscount";
            this->checkBoxDiscount->Size = System::Drawing::Size(91, 17);
            this->checkBoxDiscount->TabIndex = 8;
            this->checkBoxDiscount->Text = L"Есть скидка";
            this->checkBoxDiscount->UseVisualStyleBackColor = true;
            this->checkBoxDiscount->CheckedChanged += gcnew System::EventHandler(this, &AddCustomerForm::checkBoxDiscount_CheckedChanged);

            // label5
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(20, 170);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(91, 13);
            this->label5->TabIndex = 9;
            this->label5->Text = L"Размер скидки (%):";

            // numericDiscount
            this->numericDiscount->Enabled = false;
            this->numericDiscount->Location = System::Drawing::Point(120, 168);
            this->numericDiscount->Name = L"numericDiscount";
            this->numericDiscount->Size = System::Drawing::Size(80, 20);
            this->numericDiscount->TabIndex = 10;
            this->numericDiscount->Minimum = Decimal(0);
            this->numericDiscount->Maximum = Decimal(100);
            this->numericDiscount->Value = Decimal(0);

            // btnSave
            this->btnSave->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->btnSave->Location = System::Drawing::Point(120, 210);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(80, 30);
            this->btnSave->TabIndex = 11;
            this->btnSave->Text = L"Сохранить";
            this->btnSave->UseVisualStyleBackColor = true;
            this->btnSave->Click += gcnew System::EventHandler(this, &AddCustomerForm::btnSave_Click);

            // btnCancel
            this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->btnCancel->Location = System::Drawing::Point(220, 210);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(80, 30);
            this->btnCancel->TabIndex = 12;
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->UseVisualStyleBackColor = true;

            // AddCustomerForm
            this->AcceptButton = this->btnSave;
            this->CancelButton = this->btnCancel;
            this->ClientSize = System::Drawing::Size(350, 260);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->numericDiscount);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->checkBoxDiscount);
            this->Controls->Add(this->textBoxEmail);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->textBoxPhone);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->textBoxFirstName);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->textBoxLastName);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AddCustomerForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericDiscount))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
        System::Void checkBoxDiscount_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
        {
            numericDiscount->Enabled = checkBoxDiscount->Checked;
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (String::IsNullOrEmpty(textBoxLastName->Text) ||
                String::IsNullOrEmpty(textBoxFirstName->Text) ||
                String::IsNullOrEmpty(textBoxPhone->Text) ||
                String::IsNullOrEmpty(textBoxEmail->Text))
            {
                MessageBox::Show(L"Заполните все обязательные поля!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                this->DialogResult = System::Windows::Forms::DialogResult::None;
            }
        }
    };
}