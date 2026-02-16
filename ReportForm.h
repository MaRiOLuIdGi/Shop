#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

namespace OnlineShopApp {

    public ref class ReportForm : public Form
    {
    public:
        ReportForm(String^ reportData)
        {
            InitializeComponent();
            this->Text = L"Отчет магазина";
            textBoxReport->Text = reportData;
        }

        ReportForm(String^ reportData, bool saveToFile)
        {
            InitializeComponent();
            this->Text = L"Отчет магазина - сохранение";
            textBoxReport->Text = reportData;
            btnSave->Visible = saveToFile;

            if (saveToFile)
            {
                SaveReportToFile(reportData);
            }
        }

    private:
        System::Windows::Forms::TextBox^ textBoxReport;
        System::Windows::Forms::Button^ btnClose;
        System::Windows::Forms::Button^ btnSave;

        void InitializeComponent(void)
        {
            this->textBoxReport = (gcnew System::Windows::Forms::TextBox());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // textBoxReport
            this->textBoxReport->Location = System::Drawing::Point(20, 20);
            this->textBoxReport->Multiline = true;
            this->textBoxReport->Name = L"textBoxReport";
            this->textBoxReport->ReadOnly = true;
            this->textBoxReport->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->textBoxReport->Size = System::Drawing::Size(560, 300);
            this->textBoxReport->TabIndex = 0;

            // btnClose
            this->btnClose->Location = System::Drawing::Point(460, 330);
            this->btnClose->Name = L"btnClose";
            this->btnClose->Size = System::Drawing::Size(120, 30);
            this->btnClose->TabIndex = 1;
            this->btnClose->Text = L"Закрыть";
            this->btnClose->UseVisualStyleBackColor = true;
            this->btnClose->Click += gcnew System::EventHandler(this, &ReportForm::btnClose_Click);

            // btnSave
            this->btnSave->Location = System::Drawing::Point(330, 330);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(120, 30);
            this->btnSave->TabIndex = 2;
            this->btnSave->Text = L"Сохранить в файл";
            this->btnSave->UseVisualStyleBackColor = true;
            this->btnSave->Click += gcnew System::EventHandler(this, &ReportForm::btnSave_Click);
            this->btnSave->Visible = false;

            // ReportForm
            this->AcceptButton = this->btnClose;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 370);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnClose);
            this->Controls->Add(this->textBoxReport);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"ReportForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Отчет магазина";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
            saveDialog->Title = L"Сохранить отчет";
            saveDialog->FileName = L"Отчет_магазина_" + DateTime::Now.ToString("yyyyMMdd_HHmmss") + ".txt";

            if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    StreamWriter^ writer = gcnew StreamWriter(saveDialog->FileName);
                    writer->Write(textBoxReport->Text);
                    writer->Close();

                    MessageBox::Show(L"Отчет сохранен в файл!",
                        L"Успех",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show(L"Ошибка при сохранении: " + ex->Message,
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                }
            }
        }

        void SaveReportToFile(String^ reportData)
        {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
            saveDialog->Title = L"Сохранить отчет";
            saveDialog->FileName = L"Отчет_магазина_" + DateTime::Now.ToString("yyyyMMdd_HHmmss") + ".txt";

            if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    StreamWriter^ writer = gcnew StreamWriter(saveDialog->FileName);
                    writer->Write(reportData);
                    writer->Close();

                    MessageBox::Show(L"Отчет автоматически сохранен в файл!",
                        L"Успех",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show(L"Ошибка при сохранении: " + ex->Message,
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                }
            }
        }
    };
}