#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Text::RegularExpressions;

#include "AddCustomerForm.h"
#include "ProductsForm.h"
#include "ReportForm.h"

namespace OnlineShopApp {

    public ref class MainForm : public Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            this->Text = L"Система управления интернет-магазином";
            LoadTestData();
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
        System::Windows::Forms::DataGridView^ dataGridViewCustomers;
        System::Windows::Forms::Button^ btnAddCustomer;
        System::Windows::Forms::Button^ btnEditCustomer;
        System::Windows::Forms::Button^ btnDeleteCustomer;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnLoad;
        System::Windows::Forms::Button^ btnSortByName;
        System::Windows::Forms::Button^ btnSortByPhone;
        System::Windows::Forms::Button^ btnSortByDiscount;
        System::Windows::Forms::Button^ btnCalculateOrders;
        System::Windows::Forms::Button^ btnManageProducts;
        System::Windows::Forms::Button^ btnMakeOrder;
        System::Windows::Forms::Button^ btnReport;
        System::Windows::Forms::TextBox^ txtSearch;
        System::Windows::Forms::Button^ btnSearch;
        System::Windows::Forms::Label^ lblSearch;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblStats;
        System::Windows::Forms::SaveFileDialog^ saveFileDialog;
        System::Windows::Forms::OpenFileDialog^ openFileDialog;
        System::Windows::Forms::ContextMenuStrip^ contextMenuStrip;
        System::Windows::Forms::ToolStripMenuItem^ addRowToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ editRowToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ deleteRowToolStripMenuItem;
        System::Windows::Forms::Button^ btnQuickAdd;
        System::Windows::Forms::ToolTip^ toolTip;
        System::ComponentModel::Container^ components;
        bool isAddingNewRow;
        bool isEditingCell;

        static int CompareByLastName(DataGridViewRow^ a, DataGridViewRow^ b)
        {
            String^ valA = safe_cast<String^>(a->Cells[0]->Value);
            String^ valB = safe_cast<String^>(b->Cells[0]->Value);
            return String::Compare(valA, valB);
        }

        static int CompareByPhone(DataGridViewRow^ a, DataGridViewRow^ b)
        {
            String^ valA = safe_cast<String^>(a->Cells[2]->Value);
            String^ valB = safe_cast<String^>(b->Cells[2]->Value);
            return String::Compare(valA, valB);
        }

        static int CompareByDiscount(DataGridViewRow^ a, DataGridViewRow^ b)
        {
            String^ valA = safe_cast<String^>(a->Cells[4]->Value);
            String^ valB = safe_cast<String^>(b->Cells[4]->Value);

            if (valA == "Нет" && valB == "Да") return -1;
            if (valA == "Да" && valB == "Нет") return 1;
            return String::Compare(valA, valB);
        }

        // Методы проверки данных
        bool ValidateName(String^ name, String^ fieldName)
        {
            if (String::IsNullOrWhiteSpace(name))
            {
                MessageBox::Show(String::Format(L"Поле '{0}' не может быть пустым!", fieldName),
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            if (name->Length > 40)
            {
                MessageBox::Show(String::Format(L"Поле '{0}' не может превышать 40 символов!", fieldName),
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            // Проверка на допустимые символы (только буквы, пробелы и дефисы)
            Regex^ regex = gcnew Regex("^[a-zA-Zа-яА-ЯёЁ\\s\\-]+$");
            if (!regex->IsMatch(name))
            {
                MessageBox::Show(String::Format(L"Поле '{0}' содержит недопустимые символы! Разрешены только буквы, пробелы и дефисы.", fieldName),
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        bool ValidatePhone(String^ phone)
        {
            if (String::IsNullOrWhiteSpace(phone))
            {
                MessageBox::Show(L"Поле 'Телефон' не может быть пустым!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            if (phone->Length > 20)
            {
                MessageBox::Show(L"Номер телефона не может превышать 20 символов!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            // Проверка формата телефона (разрешены цифры, +, -, пробелы, скобки)
            Regex^ regex = gcnew Regex("^[\\+\\d\\s\\-\\(\\)]+$");
            if (!regex->IsMatch(phone))
            {
                MessageBox::Show(L"Номер телефона содержит недопустимые символы! Разрешены только цифры, +, -, пробелы и скобки.",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            // Минимальная длина номера (включая код страны)
            String^ cleanedPhone = phone->Replace(" ", "")->Replace("-", "")->Replace("(", "")->Replace(")", "");
            if (cleanedPhone->Length < 10)
            {
                MessageBox::Show(L"Номер телефона слишком короткий! Должно быть минимум 10 цифр.",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        bool ValidateEmail(String^ email)
        {
            if (String::IsNullOrWhiteSpace(email))
            {
                MessageBox::Show(L"Поле 'Email' не может быть пустым!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            if (email->Length > 50)
            {
                MessageBox::Show(L"Email не может превышать 50 символов!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            // Проверка формата email
            try
            {
                Regex^ regex = gcnew Regex("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$");
                if (!regex->IsMatch(email))
                {
                    MessageBox::Show(L"Email имеет неверный формат! Пример: user@example.com",
                        L"Ошибка ввода",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    return false;
                }
            }
            catch (Exception^)
            {
                return false;
            }

            return true;
        }

        bool ValidateDiscount(String^ discountStr)
        {
            if (String::IsNullOrWhiteSpace(discountStr))
            {
                MessageBox::Show(L"Поле 'Скидка %' не может быть пустым!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            double discount;
            if (!Double::TryParse(discountStr, discount))
            {
                MessageBox::Show(L"Скидка должна быть числом!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            if (discount < 0 || discount > 100)
            {
                MessageBox::Show(L"Скидка должна быть в диапазоне от 0 до 100%!",
                    L"Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }

            return true;
        }

        bool ValidateRow(DataGridViewRow^ row)
        {
            return ValidateRow(row, true);
        }

        bool ValidateRow(DataGridViewRow^ row, bool showErrors)
        {
            if (row == nullptr || row->IsNewRow)
                return false;

            // Проверяем каждое поле
            bool isValid = true;
            String^ errorMessage = L"";

            // Фамилия
            if (row->Cells[0]->Value == nullptr || String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[0]->Value)))
            {
                isValid = false;
                errorMessage += L"• Фамилия не может быть пустой\n";
            }
            else if (!ValidateName(safe_cast<String^>(row->Cells[0]->Value), "Фамилия") && showErrors)
            {
                return false;
            }

            // Имя
            if (row->Cells[1]->Value == nullptr || String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[1]->Value)))
            {
                isValid = false;
                errorMessage += L"• Имя не может быть пустым\n";
            }
            else if (!ValidateName(safe_cast<String^>(row->Cells[1]->Value), "Имя") && showErrors)
            {
                return false;
            }

            // Телефон
            if (row->Cells[2]->Value == nullptr || String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[2]->Value)))
            {
                isValid = false;
                errorMessage += L"• Телефон не может быть пустым\n";
            }
            else if (!ValidatePhone(safe_cast<String^>(row->Cells[2]->Value)) && showErrors)
            {
                return false;
            }

            // Email
            if (row->Cells[3]->Value == nullptr || String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[3]->Value)))
            {
                isValid = false;
                errorMessage += L"• Email не может быть пустым\n";
            }
            else if (!ValidateEmail(safe_cast<String^>(row->Cells[3]->Value)) && showErrors)
            {
                return false;
            }

            // Скидка
            if (row->Cells[4]->Value != nullptr)
            {
                String^ hasDiscount = safe_cast<String^>(row->Cells[4]->Value);
                if (hasDiscount != "Да" && hasDiscount != "Нет")
                {
                    isValid = false;
                    errorMessage += L"• Поле 'Скидка' должно содержать 'Да' или 'Нет'\n";
                }
            }
            else
            {
                isValid = false;
                errorMessage += L"• Поле 'Скидка' не может быть пустым\n";
            }

            // Скидка %
            if (row->Cells[5]->Value == nullptr || String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[5]->Value)))
            {
                isValid = false;
                errorMessage += L"• Поле 'Скидка %' не может быть пустым\n";
            }
            else if (!ValidateDiscount(safe_cast<String^>(row->Cells[5]->Value)) && showErrors)
            {
                return false;
            }

            // Проверяем связь между полями Скидка и Скидка %
            if (row->Cells[4]->Value != nullptr && row->Cells[5]->Value != nullptr)
            {
                String^ hasDiscount = safe_cast<String^>(row->Cells[4]->Value);
                String^ discountStr = safe_cast<String^>(row->Cells[5]->Value);
                double discount = 0;
                Double::TryParse(discountStr, discount);

                if (hasDiscount == "Нет" && discount > 0)
                {
                    isValid = false;
                    errorMessage += L"• При отсутствии скидки поле 'Скидка %' должно быть 0\n";
                }
                else if (hasDiscount == "Да" && discount == 0)
                {
                    isValid = false;
                    errorMessage += L"• При наличии скидки поле 'Скидка %' должно быть больше 0\n";
                }
            }

            if (!isValid && showErrors && !String::IsNullOrEmpty(errorMessage))
            {
                MessageBox::Show(L"Обнаружены ошибки в данных:\n\n" + errorMessage,
                    L"Ошибка валидации",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
            }

            return isValid;
        }

        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->dataGridViewCustomers = (gcnew System::Windows::Forms::DataGridView());
            this->btnAddCustomer = (gcnew System::Windows::Forms::Button());
            this->btnEditCustomer = (gcnew System::Windows::Forms::Button());
            this->btnDeleteCustomer = (gcnew System::Windows::Forms::Button());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnLoad = (gcnew System::Windows::Forms::Button());
            this->btnSortByName = (gcnew System::Windows::Forms::Button());
            this->btnSortByPhone = (gcnew System::Windows::Forms::Button());
            this->btnSortByDiscount = (gcnew System::Windows::Forms::Button());
            this->btnCalculateOrders = (gcnew System::Windows::Forms::Button());
            this->btnManageProducts = (gcnew System::Windows::Forms::Button());
            this->btnMakeOrder = (gcnew System::Windows::Forms::Button());
            this->btnReport = (gcnew System::Windows::Forms::Button());
            this->txtSearch = (gcnew System::Windows::Forms::TextBox());
            this->btnSearch = (gcnew System::Windows::Forms::Button());
            this->lblSearch = (gcnew System::Windows::Forms::Label());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblStats = (gcnew System::Windows::Forms::Label());
            this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
            this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
            this->contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->addRowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->editRowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->deleteRowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->btnQuickAdd = (gcnew System::Windows::Forms::Button());
            this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewCustomers))->BeginInit();
            this->contextMenuStrip->SuspendLayout();
            this->SuspendLayout();

            // dataGridViewCustomers
            this->dataGridViewCustomers->AllowUserToAddRows = false;
            this->dataGridViewCustomers->AllowUserToDeleteRows = false;
            this->dataGridViewCustomers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewCustomers->ContextMenuStrip = this->contextMenuStrip;
            this->dataGridViewCustomers->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
            this->dataGridViewCustomers->Location = System::Drawing::Point(20, 60);
            this->dataGridViewCustomers->MultiSelect = false;
            this->dataGridViewCustomers->Name = L"dataGridViewCustomers";
            this->dataGridViewCustomers->ReadOnly = false;
            this->dataGridViewCustomers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dataGridViewCustomers->Size = System::Drawing::Size(740, 200);
            this->dataGridViewCustomers->TabIndex = 0;

            // Колонки для клиентов
            this->dataGridViewCustomers->Columns->Add("LastName", "Фамилия");
            this->dataGridViewCustomers->Columns->Add("FirstName", "Имя");
            this->dataGridViewCustomers->Columns->Add("Phone", "Телефон");
            this->dataGridViewCustomers->Columns->Add("Email", "Email");
            this->dataGridViewCustomers->Columns->Add("Discount", "Скидка");
            this->dataGridViewCustomers->Columns->Add("DiscountPercent", "Скидка %");

            // Обработчики событий для DataGridView
            this->dataGridViewCustomers->CellBeginEdit += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &MainForm::dataGridViewCustomers_CellBeginEdit);
            this->dataGridViewCustomers->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridViewCustomers_CellEndEdit);
            this->dataGridViewCustomers->CellValidating += gcnew System::Windows::Forms::DataGridViewCellValidatingEventHandler(this, &MainForm::dataGridViewCustomers_CellValidating);
            this->dataGridViewCustomers->UserDeletingRow += gcnew System::Windows::Forms::DataGridViewRowCancelEventHandler(this, &MainForm::dataGridViewCustomers_UserDeletingRow);
            this->dataGridViewCustomers->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridViewCustomers_KeyDown);
            this->dataGridViewCustomers->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridViewCustomers_CellDoubleClick);

            // contextMenuStrip
            this->contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->addRowToolStripMenuItem,
                    this->editRowToolStripMenuItem,
                    this->deleteRowToolStripMenuItem
            });
            this->contextMenuStrip->Name = L"contextMenuStrip";
            this->contextMenuStrip->Size = System::Drawing::Size(181, 70);

            // addRowToolStripMenuItem
            this->addRowToolStripMenuItem->Name = L"addRowToolStripMenuItem";
            this->addRowToolStripMenuItem->Size = System::Drawing::Size(180, 22);
            this->addRowToolStripMenuItem->Text = L"Добавить клиента";
            this->addRowToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::addRowToolStripMenuItem_Click);

            // editRowToolStripMenuItem
            this->editRowToolStripMenuItem->Name = L"editRowToolStripMenuItem";
            this->editRowToolStripMenuItem->Size = System::Drawing::Size(180, 22);
            this->editRowToolStripMenuItem->Text = L"Редактировать";
            this->editRowToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::editRowToolStripMenuItem_Click);

            // deleteRowToolStripMenuItem
            this->deleteRowToolStripMenuItem->Name = L"deleteRowToolStripMenuItem";
            this->deleteRowToolStripMenuItem->Size = System::Drawing::Size(180, 22);
            this->deleteRowToolStripMenuItem->Text = L"Удалить";
            this->deleteRowToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteRowToolStripMenuItem_Click);

            // btnAddCustomer
            this->btnAddCustomer->Location = System::Drawing::Point(20, 270);
            this->btnAddCustomer->Name = L"btnAddCustomer";
            this->btnAddCustomer->Size = System::Drawing::Size(120, 30);
            this->btnAddCustomer->TabIndex = 1;
            this->btnAddCustomer->Text = L"Добавить клиента";
            this->btnAddCustomer->UseVisualStyleBackColor = true;
            this->btnAddCustomer->Click += gcnew System::EventHandler(this, &MainForm::btnAddCustomer_Click);
            this->toolTip->SetToolTip(this->btnAddCustomer, L"Добавить нового клиента через форму");

            // btnEditCustomer
            this->btnEditCustomer->Location = System::Drawing::Point(150, 270);
            this->btnEditCustomer->Name = L"btnEditCustomer";
            this->btnEditCustomer->Size = System::Drawing::Size(80, 30);
            this->btnEditCustomer->TabIndex = 2;
            this->btnEditCustomer->Text = L"Изменить";
            this->btnEditCustomer->UseVisualStyleBackColor = true;
            this->btnEditCustomer->Click += gcnew System::EventHandler(this, &MainForm::btnEditCustomer_Click);
            this->toolTip->SetToolTip(this->btnEditCustomer, L"Редактировать выбранного клиента через форму");

            // btnDeleteCustomer
            this->btnDeleteCustomer->Location = System::Drawing::Point(240, 270);
            this->btnDeleteCustomer->Name = L"btnDeleteCustomer";
            this->btnDeleteCustomer->Size = System::Drawing::Size(80, 30);
            this->btnDeleteCustomer->TabIndex = 3;
            this->btnDeleteCustomer->Text = L"Удалить";
            this->btnDeleteCustomer->UseVisualStyleBackColor = true;
            this->btnDeleteCustomer->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteCustomer_Click);
            this->toolTip->SetToolTip(this->btnDeleteCustomer, L"Удалить выбранного клиента");

            // btnSave
            this->btnSave->Location = System::Drawing::Point(330, 270);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(120, 30);
            this->btnSave->TabIndex = 4;
            this->btnSave->Text = L"Сохранить в файл";
            this->btnSave->UseVisualStyleBackColor = true;
            this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
            this->toolTip->SetToolTip(this->btnSave, L"Сохранить данные всех клиентов в файл");

            // btnLoad
            this->btnLoad->Location = System::Drawing::Point(460, 270);
            this->btnLoad->Name = L"btnLoad";
            this->btnLoad->Size = System::Drawing::Size(120, 30);
            this->btnLoad->TabIndex = 5;
            this->btnLoad->Text = L"Загрузить из файла";
            this->btnLoad->UseVisualStyleBackColor = true;
            this->btnLoad->Click += gcnew System::EventHandler(this, &MainForm::btnLoad_Click);
            this->toolTip->SetToolTip(this->btnLoad, L"Загрузить данные клиентов из файла");

            // btnMakeOrder
            this->btnMakeOrder->Location = System::Drawing::Point(590, 270);
            this->btnMakeOrder->Name = L"btnMakeOrder";
            this->btnMakeOrder->Size = System::Drawing::Size(120, 30);
            this->btnMakeOrder->TabIndex = 6;
            this->btnMakeOrder->Text = L"Создать заказ";
            this->btnMakeOrder->UseVisualStyleBackColor = true;
            this->btnMakeOrder->Click += gcnew System::EventHandler(this, &MainForm::btnMakeOrder_Click);
            this->toolTip->SetToolTip(this->btnMakeOrder, L"Создать заказ для выбранного клиента");

            // btnSortByName
            this->btnSortByName->Location = System::Drawing::Point(20, 310);
            this->btnSortByName->Name = L"btnSortByName";
            this->btnSortByName->Size = System::Drawing::Size(120, 30);
            this->btnSortByName->TabIndex = 7;
            this->btnSortByName->Text = L"Сорт. по фамилии";
            this->btnSortByName->UseVisualStyleBackColor = true;
            this->btnSortByName->Click += gcnew System::EventHandler(this, &MainForm::btnSortByName_Click);
            this->toolTip->SetToolTip(this->btnSortByName, L"Сортировать клиентов по фамилии");

            // btnSortByPhone
            this->btnSortByPhone->Location = System::Drawing::Point(150, 310);
            this->btnSortByPhone->Name = L"btnSortByPhone";
            this->btnSortByPhone->Size = System::Drawing::Size(120, 30);
            this->btnSortByPhone->TabIndex = 8;
            this->btnSortByPhone->Text = L"Сорт. по телефону";
            this->btnSortByPhone->UseVisualStyleBackColor = true;
            this->btnSortByPhone->Click += gcnew System::EventHandler(this, &MainForm::btnSortByPhone_Click);
            this->toolTip->SetToolTip(this->btnSortByPhone, L"Сортировать клиентов по телефону");

            // btnSortByDiscount
            this->btnSortByDiscount->Location = System::Drawing::Point(280, 310);
            this->btnSortByDiscount->Name = L"btnSortByDiscount";
            this->btnSortByDiscount->Size = System::Drawing::Size(120, 30);
            this->btnSortByDiscount->TabIndex = 9;
            this->btnSortByDiscount->Text = L"Сорт. по скидке";
            this->btnSortByDiscount->UseVisualStyleBackColor = true;
            this->btnSortByDiscount->Click += gcnew System::EventHandler(this, &MainForm::btnSortByDiscount_Click);
            this->toolTip->SetToolTip(this->btnSortByDiscount, L"Сортировать клиентов по наличию скидки");

            // btnCalculateOrders
            this->btnCalculateOrders->Location = System::Drawing::Point(410, 310);
            this->btnCalculateOrders->Name = L"btnCalculateOrders";
            this->btnCalculateOrders->Size = System::Drawing::Size(140, 30);
            this->btnCalculateOrders->TabIndex = 10;
            this->btnCalculateOrders->Text = L"Рассчитать заказы";
            this->btnCalculateOrders->UseVisualStyleBackColor = true;
            this->btnCalculateOrders->Click += gcnew System::EventHandler(this, &MainForm::btnCalculateOrders_Click);
            this->toolTip->SetToolTip(this->btnCalculateOrders, L"Рассчитать стоимость заказов для всех клиентов");

            // btnManageProducts
            this->btnManageProducts->Location = System::Drawing::Point(560, 310);
            this->btnManageProducts->Name = L"btnManageProducts";
            this->btnManageProducts->Size = System::Drawing::Size(140, 30);
            this->btnManageProducts->TabIndex = 11;
            this->btnManageProducts->Text = L"Управление товарами";
            this->btnManageProducts->UseVisualStyleBackColor = true;
            this->btnManageProducts->Click += gcnew System::EventHandler(this, &MainForm::btnManageProducts_Click);
            this->toolTip->SetToolTip(this->btnManageProducts, L"Открыть управление товарами магазина");

            // btnReport
            this->btnReport->Location = System::Drawing::Point(20, 350);
            this->btnReport->Name = L"btnReport";
            this->btnReport->Size = System::Drawing::Size(120, 30);
            this->btnReport->TabIndex = 12;
            this->btnReport->Text = L"Создать отчет";
            this->btnReport->UseVisualStyleBackColor = true;
            this->btnReport->Click += gcnew System::EventHandler(this, &MainForm::btnReport_Click);
            this->toolTip->SetToolTip(this->btnReport, L"Создать отчет по клиентам и заказам");

            // btnQuickAdd
            this->btnQuickAdd->Location = System::Drawing::Point(150, 350);
            this->btnQuickAdd->Name = L"btnQuickAdd";
            this->btnQuickAdd->Size = System::Drawing::Size(120, 30);
            this->btnQuickAdd->TabIndex = 13;
            this->btnQuickAdd->Text = L"Быстро добавить";
            this->btnQuickAdd->UseVisualStyleBackColor = true;
            this->btnQuickAdd->Click += gcnew System::EventHandler(this, &MainForm::btnQuickAdd_Click);
            this->toolTip->SetToolTip(this->btnQuickAdd, L"Добавить нового клиента прямо в таблице");

            // txtSearch
            this->txtSearch->Location = System::Drawing::Point(120, 390);
            this->txtSearch->Name = L"txtSearch";
            this->txtSearch->Size = System::Drawing::Size(200, 20);
            this->txtSearch->TabIndex = 14;
            this->toolTip->SetToolTip(this->txtSearch, L"Введите фамилию для поиска клиента");

            // btnSearch
            this->btnSearch->Location = System::Drawing::Point(330, 390);
            this->btnSearch->Name = L"btnSearch";
            this->btnSearch->Size = System::Drawing::Size(80, 23);
            this->btnSearch->TabIndex = 15;
            this->btnSearch->Text = L"Найти";
            this->btnSearch->UseVisualStyleBackColor = true;
            this->btnSearch->Click += gcnew System::EventHandler(this, &MainForm::btnSearch_Click);
            this->toolTip->SetToolTip(this->btnSearch, L"Найти клиента по фамилии");

            // lblSearch
            this->lblSearch->AutoSize = true;
            this->lblSearch->Location = System::Drawing::Point(20, 393);
            this->lblSearch->Name = L"lblSearch";
            this->lblSearch->Size = System::Drawing::Size(94, 13);
            this->lblSearch->TabIndex = 16;
            this->lblSearch->Text = L"Поиск по фамилии:";

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(480, 24);
            this->lblTitle->TabIndex = 17;
            this->lblTitle->Text = L"Система управления интернет-магазином - Клиенты";

            // lblStats
            this->lblStats->AutoSize = true;
            this->lblStats->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblStats->Location = System::Drawing::Point(420, 390);
            this->lblStats->Name = L"lblStats";
            this->lblStats->Size = System::Drawing::Size(100, 15);
            this->lblStats->TabIndex = 18;
            this->lblStats->Text = L"Статистика:";

            // Настройка диалоговых окон
            this->saveFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
            this->saveFileDialog->Title = L"Сохранить данные клиентов";
            this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
            this->openFileDialog->Title = L"Загрузить данные клиентов";

            // MainForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(780, 450);
            this->Controls->Add(this->lblStats);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblSearch);
            this->Controls->Add(this->btnSearch);
            this->Controls->Add(this->txtSearch);
            this->Controls->Add(this->btnQuickAdd);
            this->Controls->Add(this->btnReport);
            this->Controls->Add(this->btnManageProducts);
            this->Controls->Add(this->btnCalculateOrders);
            this->Controls->Add(this->btnSortByDiscount);
            this->Controls->Add(this->btnSortByPhone);
            this->Controls->Add(this->btnSortByName);
            this->Controls->Add(this->btnMakeOrder);
            this->Controls->Add(this->btnLoad);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnDeleteCustomer);
            this->Controls->Add(this->btnEditCustomer);
            this->Controls->Add(this->btnAddCustomer);
            this->Controls->Add(this->dataGridViewCustomers);
            this->Name = L"MainForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Система управления интернет-магазином";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewCustomers))->EndInit();
            this->contextMenuStrip->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();

            isAddingNewRow = false;
            isEditingCell = false;
            UpdateStatistics();
        }

        void LoadTestData()
        {
            dataGridViewCustomers->Rows->Clear();

            // Тестовые данные для интернет-магазина
            dataGridViewCustomers->Rows->Add("Иванов", "Иван", "+7-999-123-45-67", "ivanov@mail.ru", "Нет", "0");
            dataGridViewCustomers->Rows->Add("Петрова", "Мария", "+7-987-654-32-10", "petrova@mail.ru", "Да", "15");
            dataGridViewCustomers->Rows->Add("Сидоров", "Алексей", "+7-912-345-67-89", "sidorov@gmail.com", "Нет", "0");
            dataGridViewCustomers->Rows->Add("Козлова", "Анна", "+7-901-234-56-78", "kozlova@yandex.ru", "Да", "10");

            UpdateStatistics();
        }

        void UpdateStatistics()
        {
            int total = 0;
            int withDiscount = 0;

            for (int i = 0; i < dataGridViewCustomers->Rows->Count; i++)
            {
                DataGridViewRow^ row = dataGridViewCustomers->Rows[i];
                if (!row->IsNewRow && row->Cells[0]->Value != nullptr &&
                    !String::IsNullOrWhiteSpace(safe_cast<String^>(row->Cells[0]->Value)))
                {
                    total++;
                    if (row->Cells[4]->Value != nullptr && safe_cast<String^>(row->Cells[4]->Value) == "Да")
                        withDiscount++;
                }
            }

            lblStats->Text = String::Format("Статистика: {0} клиента, {1} со скидкой", total, withDiscount);
        }

        void SortDataGridView(int columnIndex)
        {
            // Прекращаем редактирование перед сортировкой
            if (dataGridViewCustomers->IsCurrentCellInEditMode)
            {
                dataGridViewCustomers->EndEdit();
            }

            if (dataGridViewCustomers->Rows->Count <= 1)
                return;

            List<DataGridViewRow^>^ rows = gcnew List<DataGridViewRow^>();

            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow)
                    rows->Add(row);
            }

            if (columnIndex == 0) // Фамилия
            {
                rows->Sort(gcnew Comparison<DataGridViewRow^>(&MainForm::CompareByLastName));
            }
            else if (columnIndex == 2) // Телефон
            {
                rows->Sort(gcnew Comparison<DataGridViewRow^>(&MainForm::CompareByPhone));
            }
            else if (columnIndex == 4) // Скидка
            {
                rows->Sort(gcnew Comparison<DataGridViewRow^>(&MainForm::CompareByDiscount));
            }

            dataGridViewCustomers->Rows->Clear();
            for each (DataGridViewRow ^ row in rows)
            {
                dataGridViewCustomers->Rows->Add(row);
            }
        }

        // Метод для добавления новой строки
        void AddNewRow()
        {
            isAddingNewRow = true;

            try
            {
                // Добавляем новую строку
                int newRowIndex = dataGridViewCustomers->Rows->Add();
                DataGridViewRow^ newRow = dataGridViewCustomers->Rows[newRowIndex];

                // Устанавливаем значения по умолчанию
                newRow->Cells[0]->Value = "";
                newRow->Cells[1]->Value = "";
                newRow->Cells[2]->Value = "+7-XXX-XXX-XX-XX";
                newRow->Cells[3]->Value = "email@example.com";
                newRow->Cells[4]->Value = "Нет";
                newRow->Cells[5]->Value = "0";

                // Выделяем новую строку
                dataGridViewCustomers->ClearSelection();
                newRow->Selected = true;
                dataGridViewCustomers->CurrentCell = newRow->Cells[0];

                // Начинаем редактирование
                dataGridViewCustomers->BeginEdit(true);

                // Прокручиваем к новой строке
                dataGridViewCustomers->FirstDisplayedScrollingRowIndex = newRowIndex;

                UpdateStatistics();
            }
            finally
            {
                isAddingNewRow = false;
            }
        }

    private:
        // ============== ОБРАБОТЧИКИ СОБЫТИЙ ==============

        System::Void btnAddCustomer_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Старая форма добавления (оставлена для совместимости)
            AddCustomerForm^ form = gcnew AddCustomerForm();

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                if (String::IsNullOrEmpty(form->LastName) ||
                    String::IsNullOrEmpty(form->FirstName) ||
                    String::IsNullOrEmpty(form->Phone) ||
                    String::IsNullOrEmpty(form->Email))
                {
                    MessageBox::Show(L"Заполните все обязательные поля!",
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    return;
                }

                if (!ValidateName(form->LastName, "Фамилия") ||
                    !ValidateName(form->FirstName, "Имя") ||
                    !ValidatePhone(form->Phone) ||
                    !ValidateEmail(form->Email))
                {
                    return;
                }

                if (form->HasDiscount && (form->Discount < 0 || form->Discount > 100))
                {
                    MessageBox::Show(L"Скидка должна быть от 0 до 100%!",
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    return;
                }

                String^ discount = form->HasDiscount ? "Да" : "Нет";
                String^ discountPercent = form->Discount.ToString("F1");

                dataGridViewCustomers->Rows->Add(
                    form->LastName,
                    form->FirstName,
                    form->Phone,
                    form->Email,
                    discount,
                    discountPercent
                );

                MessageBox::Show(L"Клиент успешно добавлен!",
                    L"Успех",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information);
                UpdateStatistics();
            }
        }

        System::Void btnEditCustomer_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Старый метод редактирования через форму
            if (dataGridViewCustomers->SelectedRows->Count == 0)
            {
                MessageBox::Show(L"Выберите клиента для редактирования!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ selectedRow = dataGridViewCustomers->SelectedRows[0];

            if (selectedRow->Cells[0]->Value == nullptr || String::IsNullOrEmpty(safe_cast<String^>(selectedRow->Cells[0]->Value)))
            {
                // Если строка пустая, начинаем редактирование inline
                dataGridViewCustomers->BeginEdit(true);
                return;
            }

            String^ lastName = safe_cast<String^>(selectedRow->Cells[0]->Value);
            String^ firstName = safe_cast<String^>(selectedRow->Cells[1]->Value);
            String^ phone = safe_cast<String^>(selectedRow->Cells[2]->Value);
            String^ email = safe_cast<String^>(selectedRow->Cells[3]->Value);
            bool hasDiscount = (safe_cast<String^>(selectedRow->Cells[4]->Value) == "Да");
            double discount = Convert::ToDouble(selectedRow->Cells[5]->Value);

            AddCustomerForm^ form = gcnew AddCustomerForm(
                lastName, firstName, phone, email, hasDiscount, discount
            );

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                if (String::IsNullOrEmpty(form->LastName) ||
                    String::IsNullOrEmpty(form->FirstName) ||
                    String::IsNullOrEmpty(form->Phone) ||
                    String::IsNullOrEmpty(form->Email))
                {
                    MessageBox::Show(L"Заполните все обязательные поля!",
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    return;
                }

                if (!ValidateName(form->LastName, "Фамилия") ||
                    !ValidateName(form->FirstName, "Имя") ||
                    !ValidatePhone(form->Phone) ||
                    !ValidateEmail(form->Email))
                {
                    return;
                }

                if (form->HasDiscount && (form->Discount < 0 || form->Discount > 100))
                {
                    MessageBox::Show(L"Скидка должна быть от 0 до 100%!",
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    return;
                }

                selectedRow->Cells[0]->Value = form->LastName;
                selectedRow->Cells[1]->Value = form->FirstName;
                selectedRow->Cells[2]->Value = form->Phone;
                selectedRow->Cells[3]->Value = form->Email;
                selectedRow->Cells[4]->Value = form->HasDiscount ? "Да" : "Нет";
                selectedRow->Cells[5]->Value = form->Discount.ToString("F1");

                MessageBox::Show(L"Данные клиента обновлены!",
                    L"Успех",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information);
                UpdateStatistics();
            }
        }

        System::Void btnDeleteCustomer_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCustomers->SelectedRows->Count == 0)
            {
                MessageBox::Show(L"Выберите клиента для удаления!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ row = dataGridViewCustomers->SelectedRows[0];

            // Проверяем, не является ли строка пустой
            if (row->Cells[0]->Value == nullptr || String::IsNullOrEmpty(safe_cast<String^>(row->Cells[0]->Value)))
            {
                dataGridViewCustomers->Rows->Remove(row);
                UpdateStatistics();
                return;
            }

            System::Windows::Forms::DialogResult result = MessageBox::Show(
                L"Вы уверены, что хотите удалить выбранного клиента?",
                L"Подтверждение удаления",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::Yes)
            {
                dataGridViewCustomers->Rows->Remove(row);
                MessageBox::Show(L"Клиент удален!",
                    L"Успех",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information);
                UpdateStatistics();
            }
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Прекращаем редактирование перед сохранением
            if (dataGridViewCustomers->IsCurrentCellInEditMode)
            {
                dataGridViewCustomers->EndEdit();
            }

            // Проверяем все строки перед сохранением
            bool hasErrors = false;
            String^ errorRows = L"";
            int rowNum = 1;

            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow)
                {
                    if (!ValidateRow(row, false))
                    {
                        hasErrors = true;
                        String^ lastName = row->Cells[0]->Value != nullptr ? safe_cast<String^>(row->Cells[0]->Value) : L"<пусто>";
                        errorRows += String::Format(L"Строка {0}: {1}\n", rowNum, lastName);
                    }
                    rowNum++;
                }
            }

            if (hasErrors)
            {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    L"В данных есть ошибки. Сохранить только корректные строки?\n\nСтроки с ошибками:\n" + errorRows,
                    L"Предупреждение",
                    MessageBoxButtons::YesNoCancel,
                    MessageBoxIcon::Warning
                );

                if (result == System::Windows::Forms::DialogResult::Cancel)
                    return;
                if (result == System::Windows::Forms::DialogResult::No)
                {
                    MessageBox::Show(L"Исправьте ошибки перед сохранением.",
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                    return;
                }
            }

            if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    StreamWriter^ writer = gcnew StreamWriter(saveFileDialog->FileName);

                    writer->WriteLine("Фамилия;Имя;Телефон;Email;Скидка;Скидка%");

                    for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
                    {
                        if (!row->IsNewRow)
                        {
                            // Сохраняем только корректные строки
                            if (ValidateRow(row, false) || hasErrors)
                            {
                                writer->WriteLine(
                                    String::Format("{0};{1};{2};{3};{4};{5}",
                                        safe_cast<String^>(row->Cells[0]->Value),
                                        safe_cast<String^>(row->Cells[1]->Value),
                                        safe_cast<String^>(row->Cells[2]->Value),
                                        safe_cast<String^>(row->Cells[3]->Value),
                                        safe_cast<String^>(row->Cells[4]->Value),
                                        safe_cast<String^>(row->Cells[5]->Value)
                                    )
                                );
                            }
                        }
                    }

                    writer->Close();

                    MessageBox::Show(
                        String::Format(L"Данные сохранены в файл:\n{0}", saveFileDialog->FileName),
                        L"Успех",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show(
                        String::Format(L"Ошибка при сохранении:\n{0}", ex->Message),
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                }
            }
        }

        System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Прекращаем редактирование перед загрузкой
            if (dataGridViewCustomers->IsCurrentCellInEditMode)
            {
                dataGridViewCustomers->EndEdit();
            }

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    if (dataGridViewCustomers->Rows->Count > 0)
                    {
                        System::Windows::Forms::DialogResult dialogResult = MessageBox::Show(
                            L"Текущие данные будут потеряны. Продолжить?",
                            L"Подтверждение",
                            MessageBoxButtons::YesNo,
                            MessageBoxIcon::Question
                        );

                        if (dialogResult != System::Windows::Forms::DialogResult::Yes)
                            return;
                    }

                    dataGridViewCustomers->Rows->Clear();

                    StreamReader^ reader = gcnew StreamReader(openFileDialog->FileName);

                    String^ header = reader->ReadLine();
                    int loadedCount = 0;
                    int errorCount = 0;

                    while (!reader->EndOfStream)
                    {
                        String^ line = reader->ReadLine();
                        array<String^>^ fields = line->Split(';');

                        if (fields->Length >= 6)
                        {
                            // Проверяем данные перед добавлением
                            bool isValid = true;

                            // Проверка фамилии и имени
                            if (String::IsNullOrWhiteSpace(fields[0]) ||
                                String::IsNullOrWhiteSpace(fields[1]))
                            {
                                errorCount++;
                                continue;
                            }

                            // Проверка скидки
                            double discount = 0;
                            if (!Double::TryParse(fields[5], discount) || discount < 0 || discount > 100)
                            {
                                errorCount++;
                                continue;
                            }

                            dataGridViewCustomers->Rows->Add(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]);
                            loadedCount++;
                        }
                    }

                    reader->Close();

                    String^ message = String::Format(L"Данные загружены из файла:\n{0}\n\nЗагружено: {1} клиентов\nПропущено из-за ошибок: {2}",
                        openFileDialog->FileName, loadedCount, errorCount);

                    MessageBox::Show(message,
                        L"Успех",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);

                    UpdateStatistics();
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show(
                        String::Format(L"Ошибка при загрузке:\n{0}", ex->Message),
                        L"Ошибка",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                }
            }
        }

        System::Void btnSortByName_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SortDataGridView(0);
            MessageBox::Show(L"Данные отсортированы по фамилии",
                L"Сортировка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnSortByPhone_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SortDataGridView(2);
            MessageBox::Show(L"Данные отсортированы по телефону",
                L"Сортировка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnSortByDiscount_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SortDataGridView(4);
            MessageBox::Show(L"Данные отсортированы по наличию скидки",
                L"Сортировка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnCalculateOrders_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Прекращаем редактирование перед расчетом
            if (dataGridViewCustomers->IsCurrentCellInEditMode)
            {
                dataGridViewCustomers->EndEdit();
            }

            // Проверяем все строки перед расчетом
            int validRows = 0;
            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow && ValidateRow(row, false))
                {
                    validRows++;
                }
            }

            if (validRows == 0)
            {
                MessageBox::Show(L"Нет корректных данных для расчета! Проверьте заполнение полей.",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            array<double>^ productPrices = gcnew array<double> {
                25000.0, // Смартфон
                    50000.0, // Ноутбук
                    8000.0,  // Наушники
                    12000.0, // Планшет
                    1500.0,  // Футболка
                    4000.0   // Джинсы
            };

            double totalCost = 0.0;
            int customerCount = 0;
            String^ details = L"Детали расчета заказов:\n\n";

            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow && ValidateRow(row, false))
                {
                    customerCount++;
                    String^ lastName = safe_cast<String^>(row->Cells[0]->Value);
                    String^ firstName = safe_cast<String^>(row->Cells[1]->Value);
                    bool hasDiscount = (safe_cast<String^>(row->Cells[4]->Value) == "Да");
                    double discount = 0.0;

                    Double::TryParse(safe_cast<String^>(row->Cells[5]->Value), discount);

                    double customerTotal = 0.0;
                    for each (double productPrice in productPrices)
                    {
                        if (hasDiscount)
                            customerTotal += productPrice * (1 - discount / 100.0);
                        else
                            customerTotal += productPrice;
                    }

                    totalCost += customerTotal;

                    details += String::Format(L"{0} {1}: {2:F2} руб. {3}\n",
                        lastName, firstName, customerTotal,
                        hasDiscount ? String::Format(L"(со скидкой {0}%)", discount) : L"(без скидки)");
                }
            }

            String^ message = String::Format(
                L"=== РАСЧЕТ СТОИМОСТИ ЗАКАЗОВ ===\n\n" +
                L"Всего клиентов: {0}\n" +
                L"Общая стоимость всех товаров: {1:F2} руб.\n\n" +
                L"{2}\n" +
                L"Цены товаров:\n" +
                L"- Смартфон: 25000 руб.\n" +
                L"- Ноутбук: 50000 руб.\n" +
                L"- Наушники: 8000 руб.\n" +
                L"- Планшет: 12000 руб.\n" +
                L"- Футболка: 1500 руб.\n" +
                L"- Джинсы: 4000 руб.",
                customerCount, totalCost, details
            );

            MessageBox::Show(message,
                L"Расчет стоимости заказов",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnManageProducts_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ProductsForm^ productsForm = gcnew ProductsForm(false);
            productsForm->ShowDialog();
        }

        System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ searchText = txtSearch->Text->Trim();

            if (String::IsNullOrEmpty(searchText))
            {
                MessageBox::Show(L"Введите фамилию для поиска!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            dataGridViewCustomers->ClearSelection();

            bool found = false;
            for (int i = 0; i < dataGridViewCustomers->Rows->Count; i++)
            {
                DataGridViewRow^ row = dataGridViewCustomers->Rows[i];
                if (!row->IsNewRow && row->Cells[0]->Value != nullptr)
                {
                    String^ lastName = safe_cast<String^>(row->Cells[0]->Value);
                    if (lastName->ToLower()->Contains(searchText->ToLower()))
                    {
                        row->Selected = true;
                        dataGridViewCustomers->FirstDisplayedScrollingRowIndex = i;
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                MessageBox::Show(
                    String::Format(L"Клиент с фамилией '{0}' не найден!", searchText),
                    L"Результат поиска",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );
            }
        }

        System::Void btnMakeOrder_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCustomers->SelectedRows->Count == 0)
            {
                MessageBox::Show(L"Выберите клиента для создания заказа!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ selectedRow = dataGridViewCustomers->SelectedRows[0];

            if (selectedRow->Cells[0]->Value == nullptr || String::IsNullOrEmpty(safe_cast<String^>(selectedRow->Cells[0]->Value)))
            {
                MessageBox::Show(L"Выберите клиента с заполненными данными!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            // Проверяем корректность данных клиента
            if (!ValidateRow(selectedRow, true))
            {
                MessageBox::Show(L"Исправьте ошибки в данных клиента перед созданием заказа!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            String^ customerName = safe_cast<String^>(selectedRow->Cells[0]->Value) + " " +
                safe_cast<String^>(selectedRow->Cells[1]->Value);

            MessageBox::Show(
                String::Format(L"Создание заказа для клиента: {0}\n\nДля полноценной системы заказов необходимо добавить функционал выбора товаров и корзины.", customerName),
                L"Создание заказа",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
        }

        System::Void btnReport_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Прекращаем редактирование перед созданием отчета
            if (dataGridViewCustomers->IsCurrentCellInEditMode)
            {
                dataGridViewCustomers->EndEdit();
            }

            int validRows = 0;
            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow && ValidateRow(row, false))
                {
                    validRows++;
                }
            }

            if (validRows == 0)
            {
                MessageBox::Show(L"Нет корректных данных для отчета! Проверьте заполнение полей.",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            String^ report = L"=== ОТЧЕТ ИНТЕРНЕТ-МАГАЗИНА ===\n\n";
            report += L"Дата формирования: " + DateTime::Now.ToString("dd.MM.yyyy HH:mm") + L"\n\n";
            report += L"СПИСОК КЛИЕНТОВ:\n";
            report += L"--------------------------------------------------\n";

            int total = 0;
            int withDiscount = 0;
            double totalValue = 0.0;

            array<double>^ productPrices = gcnew array<double> {25000.0, 50000.0, 8000.0, 12000.0, 1500.0, 4000.0};

            for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
            {
                if (!row->IsNewRow && ValidateRow(row, false))
                {
                    total++;
                    String^ lastName = safe_cast<String^>(row->Cells[0]->Value);
                    String^ firstName = safe_cast<String^>(row->Cells[1]->Value);
                    String^ phone = safe_cast<String^>(row->Cells[2]->Value);
                    String^ email = safe_cast<String^>(row->Cells[3]->Value);
                    bool hasDiscount = (safe_cast<String^>(row->Cells[4]->Value) == "Да");
                    double discount = 0.0;

                    Double::TryParse(safe_cast<String^>(row->Cells[5]->Value), discount);

                    if (hasDiscount) withDiscount++;

                    double customerValue = 0.0;
                    for each (double productPrice in productPrices)
                    {
                        if (hasDiscount)
                            customerValue += productPrice * (1 - discount / 100.0);
                        else
                            customerValue += productPrice;
                    }
                    totalValue += customerValue;

                    report += String::Format(L"{0} {1}\n", lastName, firstName);
                    report += String::Format(L"  Телефон: {0}\n", phone);
                    report += String::Format(L"  Email: {0}\n", email);
                    report += String::Format(L"  Скидка: {0}", hasDiscount ? "Да" : "Нет");
                    if (hasDiscount)
                        report += String::Format(L" ({0}%)", discount);
                    report += String::Format(L"\n  Потенциальная стоимость: {0:F2} руб.\n", customerValue);
                    report += L"--------------------------------------------------\n";
                }
            }

            report += L"\nСТАТИСТИКА МАГАЗИНА:\n";
            report += String::Format(L"Всего клиентов: {0}\n", total);
            report += String::Format(L"Клиентов со скидкой: {0}\n", withDiscount);
            report += String::Format(L"Клиентов без скидки: {0}\n", total - withDiscount);
            report += String::Format(L"Общая потенциальная стоимость: {0:F2} руб.\n", totalValue);
            report += String::Format(L"Средняя стоимость на клиента: {0:F2} руб.\n",
                total > 0 ? totalValue / total : 0);

            report += L"\nДОСТУПНЫЕ ТОВАРЫ:\n";
            report += L"1. Смартфон - 25000 руб.\n";
            report += L"2. Ноутбук - 50000 руб.\n";
            report += L"3. Наушники - 8000 руб.\n";
            report += L"4. Планшет - 12000 руб.\n";
            report += L"5. Футболка - 1500 руб.\n";
            report += L"6. Джинсы - 4000 руб.\n";

            ReportForm^ reportForm = gcnew ReportForm(report, true);
            reportForm->ShowDialog();
        }

        System::Void btnQuickAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            AddNewRow();
        }

        // ============== КОНТЕКСТНОЕ МЕНЮ ==============

        System::Void addRowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            AddNewRow();
        }

        System::Void editRowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCustomers->SelectedRows->Count > 0)
            {
                dataGridViewCustomers->BeginEdit(true);
            }
            else
            {
                MessageBox::Show(L"Выберите строку для редактирования!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
            }
        }

        System::Void deleteRowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCustomers->SelectedRows->Count > 0)
            {
                DataGridViewRow^ row = dataGridViewCustomers->SelectedRows[0];

                if (row->IsNewRow)
                    return;

                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    L"Удалить выбранного клиента?",
                    L"Подтверждение удаления",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (result == System::Windows::Forms::DialogResult::Yes)
                {
                    dataGridViewCustomers->Rows->Remove(row);
                    UpdateStatistics();
                }
            }
        }

        // ============== СОБЫТИЯ DATAGRIDVIEW ==============

        System::Void dataGridViewCustomers_CellBeginEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^ e)
        {
            isEditingCell = true;
        }

        System::Void dataGridViewCustomers_CellValidating(System::Object^ sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^ e)
        {
            if (!isEditingCell || e->RowIndex < 0 || e->RowIndex >= dataGridViewCustomers->Rows->Count)
                return;

            DataGridViewRow^ row = dataGridViewCustomers->Rows[e->RowIndex];
            String^ newValue = safe_cast<String^>(e->FormattedValue);

            // Валидация в зависимости от столбца
            switch (e->ColumnIndex)
            {
            case 0: // Фамилия
                if (!ValidateName(newValue, "Фамилия"))
                {
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;

            case 1: // Имя
                if (!ValidateName(newValue, "Имя"))
                {
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;

            case 2: // Телефон
                if (!ValidatePhone(newValue))
                {
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;

            case 3: // Email
                if (!ValidateEmail(newValue))
                {
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;

            case 4: // Скидка (Да/Нет)
                if (newValue != "Да" && newValue != "Нет")
                {
                    MessageBox::Show(L"Поле 'Скидка' должно содержать 'Да' или 'Нет'!",
                        L"Ошибка ввода",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;

            case 5: // Скидка %
                if (!ValidateDiscount(newValue))
                {
                    e->Cancel = true;
                    dataGridViewCustomers->CancelEdit();
                }
                break;
            }
        }

        System::Void dataGridViewCustomers_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            isEditingCell = false;

            if (e->RowIndex >= 0 && e->RowIndex < dataGridViewCustomers->Rows->Count)
            {
                DataGridViewRow^ row = dataGridViewCustomers->Rows[e->RowIndex];

                // Автоматически обновляем поле "Скидка" если меняем "Скидка %"
                if (e->ColumnIndex == 5 && row->Cells[5]->Value != nullptr) // Скидка %
                {
                    String^ discountPercent = safe_cast<String^>(row->Cells[5]->Value);
                    double discountValue = 0.0;

                    if (Double::TryParse(discountPercent, discountValue))
                    {
                        if (discountValue > 0)
                            row->Cells[4]->Value = "Да";
                        else
                            row->Cells[4]->Value = "Нет";
                    }
                }

                // Автоматически обновляем поле "Скидка %" если меняем "Скидка"
                if (e->ColumnIndex == 4 && row->Cells[4]->Value != nullptr) // Скидка (Да/Нет)
                {
                    String^ hasDiscount = safe_cast<String^>(row->Cells[4]->Value);
                    if (hasDiscount == "Нет")
                        row->Cells[5]->Value = "0";
                    else if (hasDiscount == "Да" && row->Cells[5]->Value != nullptr)
                    {
                        String^ currentDiscount = safe_cast<String^>(row->Cells[5]->Value);
                        double discountValue = 0.0;
                        if (Double::TryParse(currentDiscount, discountValue) && discountValue == 0)
                            row->Cells[5]->Value = "10"; // Стандартная скидка
                    }
                }

                // Подсвечиваем строку с ошибками
                if (ValidateRow(row, false))
                {
                    row->DefaultCellStyle->BackColor = Color::White;
                }
                else
                {
                    row->DefaultCellStyle->BackColor = Color::LightPink;
                }

                UpdateStatistics();
            }
        }

        System::Void dataGridViewCustomers_UserDeletingRow(System::Object^ sender, System::Windows::Forms::DataGridViewRowCancelEventArgs^ e)
        {
            if (!isAddingNewRow && !e->Row->IsNewRow)
            {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    L"Удалить этого клиента?",
                    L"Подтверждение удаления",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (result == System::Windows::Forms::DialogResult::No)
                {
                    e->Cancel = true;
                }
            }
        }

        System::Void dataGridViewCustomers_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            // Добавление новой строки по Ctrl+N
            if (e->Control && e->KeyCode == Keys::N)
            {
                AddNewRow();
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            // Удаление строки по Delete
            else if (e->KeyCode == Keys::Delete && dataGridViewCustomers->SelectedRows->Count > 0)
            {
                deleteRowToolStripMenuItem_Click(sender, e);
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            // Редактирование по F2
            else if (e->KeyCode == Keys::F2 && dataGridViewCustomers->SelectedRows->Count > 0)
            {
                dataGridViewCustomers->BeginEdit(true);
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            // Сохранение по Ctrl+S
            else if (e->Control && e->KeyCode == Keys::S)
            {
                btnSave_Click(sender, e);
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            // Проверка данных по Ctrl+V (validate)
            else if (e->Control && e->KeyCode == Keys::V)
            {
                // Проверяем все строки
                int errorCount = 0;
                for each (DataGridViewRow ^ row in dataGridViewCustomers->Rows)
                {
                    if (!row->IsNewRow && !ValidateRow(row, false))
                    {
                        errorCount++;
                        row->DefaultCellStyle->BackColor = Color::LightPink;
                    }
                    else if (!row->IsNewRow)
                    {
                        row->DefaultCellStyle->BackColor = Color::White;
                    }
                }

                if (errorCount > 0)
                {
                    MessageBox::Show(String::Format(L"Найдено {0} строк с ошибками!", errorCount),
                        L"Результат проверки",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Warning);
                }
                else
                {
                    MessageBox::Show(L"Все данные корректны!",
                        L"Результат проверки",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);
                }

                e->Handled = true;
                e->SuppressKeyPress = true;
            }
        }

        System::Void dataGridViewCustomers_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->ColumnIndex >= 0)
            {
                dataGridViewCustomers->BeginEdit(true);
            }
        }
    };
}