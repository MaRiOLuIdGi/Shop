#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

namespace OnlineShopApp {

    public ref class ProductsForm : public Form
    {
    public:
        ProductsForm(void)
        {
            InitializeComponent();
            this->Text = L"Управление товарами магазина";
            LoadDefaultProducts();
        }

        ProductsForm(bool showInStockOnly)
        {
            InitializeComponent();
            if (showInStockOnly)
            {
                this->Text = L"Товары в наличии";
                checkBoxInStockOnly->Checked = true;
                checkBoxInStockOnly->Enabled = false;
                LoadDefaultProducts();
                for (int i = dataGridViewProducts->Rows->Count - 1; i >= 0; i--)
                {
                    DataGridViewRow^ row = dataGridViewProducts->Rows[i];
                    if (!row->IsNewRow && Convert::ToInt32(row->Cells[3]->Value) <= 0)
                    {
                        dataGridViewProducts->Rows->RemoveAt(i);
                    }
                }
            }
            else
            {
                this->Text = L"Все товары магазина";
                LoadDefaultProducts();
            }
        }

    private:
        System::Windows::Forms::DataGridView^ dataGridViewProducts;
        System::Windows::Forms::Button^ btnAddProduct;
        System::Windows::Forms::Button^ btnRemoveProduct;
        System::Windows::Forms::Button^ btnSaveProducts;
        System::Windows::Forms::Button^ btnClose;
        System::Windows::Forms::CheckBox^ checkBoxInStockOnly;
        System::Windows::Forms::TextBox^ textBoxProductName;
        System::Windows::Forms::TextBox^ textBoxProductPrice;
        System::Windows::Forms::TextBox^ textBoxProductCategory;
        System::Windows::Forms::TextBox^ textBoxProductStock;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;

        void InitializeComponent(void)
        {
            this->dataGridViewProducts = (gcnew System::Windows::Forms::DataGridView());
            this->btnAddProduct = (gcnew System::Windows::Forms::Button());
            this->btnRemoveProduct = (gcnew System::Windows::Forms::Button());
            this->btnSaveProducts = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            this->checkBoxInStockOnly = (gcnew System::Windows::Forms::CheckBox());
            this->textBoxProductName = (gcnew System::Windows::Forms::TextBox());
            this->textBoxProductPrice = (gcnew System::Windows::Forms::TextBox());
            this->textBoxProductCategory = (gcnew System::Windows::Forms::TextBox());
            this->textBoxProductStock = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewProducts))->BeginInit();
            this->SuspendLayout();

            // dataGridViewProducts
            this->dataGridViewProducts->AllowUserToAddRows = false;
            this->dataGridViewProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewProducts->Location = System::Drawing::Point(20, 60);
            this->dataGridViewProducts->Name = L"dataGridViewProducts";
            this->dataGridViewProducts->ReadOnly = true;
            this->dataGridViewProducts->Size = System::Drawing::Size(650, 200);
            this->dataGridViewProducts->TabIndex = 0;

            // Колонки для товаров
            this->dataGridViewProducts->Columns->Add("Name", "Название товара");
            this->dataGridViewProducts->Columns->Add("Price", "Цена (руб.)");
            this->dataGridViewProducts->Columns->Add("Category", "Категория");
            this->dataGridViewProducts->Columns->Add("Stock", "На складе");
            this->dataGridViewProducts->Columns->Add("Status", "Статус");

            // btnAddProduct
            this->btnAddProduct->Location = System::Drawing::Point(20, 270);
            this->btnAddProduct->Name = L"btnAddProduct";
            this->btnAddProduct->Size = System::Drawing::Size(120, 30);
            this->btnAddProduct->TabIndex = 1;
            this->btnAddProduct->Text = L"Добавить товар";
            this->btnAddProduct->UseVisualStyleBackColor = true;
            this->btnAddProduct->Click += gcnew System::EventHandler(this, &ProductsForm::btnAddProduct_Click);

            // btnRemoveProduct
            this->btnRemoveProduct->Location = System::Drawing::Point(150, 270);
            this->btnRemoveProduct->Name = L"btnRemoveProduct";
            this->btnRemoveProduct->Size = System::Drawing::Size(120, 30);
            this->btnRemoveProduct->TabIndex = 2;
            this->btnRemoveProduct->Text = L"Удалить товар";
            this->btnRemoveProduct->UseVisualStyleBackColor = true;
            this->btnRemoveProduct->Click += gcnew System::EventHandler(this, &ProductsForm::btnRemoveProduct_Click);

            // btnSaveProducts
            this->btnSaveProducts->Location = System::Drawing::Point(280, 270);
            this->btnSaveProducts->Name = L"btnSaveProducts";
            this->btnSaveProducts->Size = System::Drawing::Size(120, 30);
            this->btnSaveProducts->TabIndex = 3;
            this->btnSaveProducts->Text = L"Сохранить в файл";
            this->btnSaveProducts->UseVisualStyleBackColor = true;
            this->btnSaveProducts->Click += gcnew System::EventHandler(this, &ProductsForm::btnSaveProducts_Click);

            // btnClose
            this->btnClose->Location = System::Drawing::Point(410, 270);
            this->btnClose->Name = L"btnClose";
            this->btnClose->Size = System::Drawing::Size(120, 30);
            this->btnClose->TabIndex = 4;
            this->btnClose->Text = L"Закрыть";
            this->btnClose->UseVisualStyleBackColor = true;
            this->btnClose->Click += gcnew System::EventHandler(this, &ProductsForm::btnClose_Click);

            // checkBoxInStockOnly
            this->checkBoxInStockOnly->AutoSize = true;
            this->checkBoxInStockOnly->Location = System::Drawing::Point(550, 320);
            this->checkBoxInStockOnly->Name = L"checkBoxInStockOnly";
            this->checkBoxInStockOnly->Size = System::Drawing::Size(120, 17);
            this->checkBoxInStockOnly->TabIndex = 5;
            this->checkBoxInStockOnly->Text = L"Только в наличии";
            this->checkBoxInStockOnly->UseVisualStyleBackColor = true;
            this->checkBoxInStockOnly->CheckedChanged += gcnew System::EventHandler(this, &ProductsForm::checkBoxInStockOnly_CheckedChanged);

            // textBoxProductName
            this->textBoxProductName->Location = System::Drawing::Point(100, 320);
            this->textBoxProductName->Name = L"textBoxProductName";
            this->textBoxProductName->Size = System::Drawing::Size(150, 20);
            this->textBoxProductName->TabIndex = 6;

            // textBoxProductPrice
            this->textBoxProductPrice->Location = System::Drawing::Point(100, 350);
            this->textBoxProductPrice->Name = L"textBoxProductPrice";
            this->textBoxProductPrice->Size = System::Drawing::Size(100, 20);
            this->textBoxProductPrice->TabIndex = 7;

            // textBoxProductCategory
            this->textBoxProductCategory->Location = System::Drawing::Point(100, 380);
            this->textBoxProductCategory->Name = L"textBoxProductCategory";
            this->textBoxProductCategory->Size = System::Drawing::Size(150, 20);
            this->textBoxProductCategory->TabIndex = 8;

            // textBoxProductStock
            this->textBoxProductStock->Location = System::Drawing::Point(100, 410);
            this->textBoxProductStock->Name = L"textBoxProductStock";
            this->textBoxProductStock->Size = System::Drawing::Size(100, 20);
            this->textBoxProductStock->TabIndex = 9;

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(20, 323);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(60, 13);
            this->label1->TabIndex = 10;
            this->label1->Text = L"Название:";

            // label2
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(20, 353);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(36, 13);
            this->label2->TabIndex = 11;
            this->label2->Text = L"Цена:";

            // label3
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(20, 383);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(63, 13);
            this->label3->TabIndex = 12;
            this->label3->Text = L"Категория:";

            // label4
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(20, 413);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(72, 13);
            this->label4->TabIndex = 13;
            this->label4->Text = L"На складе:";

            // label5
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(20, 20);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(318, 20);
            this->label5->TabIndex = 14;
            this->label5->Text = L"Управление товарами интернет-магазина";

            // ProductsForm
            this->AcceptButton = this->btnAddProduct;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(700, 450);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->textBoxProductStock);
            this->Controls->Add(this->textBoxProductCategory);
            this->Controls->Add(this->textBoxProductPrice);
            this->Controls->Add(this->textBoxProductName);
            this->Controls->Add(this->checkBoxInStockOnly);
            this->Controls->Add(this->btnClose);
            this->Controls->Add(this->btnSaveProducts);
            this->Controls->Add(this->btnRemoveProduct);
            this->Controls->Add(this->btnAddProduct);
            this->Controls->Add(this->dataGridViewProducts);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"ProductsForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Управление товарами";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewProducts))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadDefaultProducts()
        {
            dataGridViewProducts->Rows->Clear();
            dataGridViewProducts->Rows->Add("Смартфон", "25000.00", "Электроника", "50", "В наличии");
            dataGridViewProducts->Rows->Add("Ноутбук", "50000.00", "Электроника", "30", "В наличии");
            dataGridViewProducts->Rows->Add("Наушники", "8000.00", "Электроника", "100", "В наличии");
            dataGridViewProducts->Rows->Add("Планшет", "12000.00", "Электроника", "40", "В наличии");
            dataGridViewProducts->Rows->Add("Футболка", "1500.00", "Одежда", "200", "В наличии");
            dataGridViewProducts->Rows->Add("Джинсы", "4000.00", "Одежда", "0", "Нет в наличии");
        }

    private:
        System::Void btnAddProduct_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ name = textBoxProductName->Text->Trim();
            String^ priceText = textBoxProductPrice->Text->Trim();
            String^ category = textBoxProductCategory->Text->Trim();
            String^ stockText = textBoxProductStock->Text->Trim();

            if (String::IsNullOrEmpty(name))
            {
                MessageBox::Show(L"Введите название товара!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (String::IsNullOrEmpty(priceText))
            {
                MessageBox::Show(L"Введите цену товара!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (String::IsNullOrEmpty(category))
            {
                MessageBox::Show(L"Введите категорию товара!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (String::IsNullOrEmpty(stockText))
            {
                MessageBox::Show(L"Введите количество на складе!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            double price;
            if (!Double::TryParse(priceText, price) || price < 0)
            {
                MessageBox::Show(L"Введите корректную цену (положительное число)!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            int stock;
            if (!Int32::TryParse(stockText, stock) || stock < 0)
            {
                MessageBox::Show(L"Введите корректное количество (целое положительное число)!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ status = stock > 0 ? "В наличии" : "Нет в наличии";

            dataGridViewProducts->Rows->Add(name, price.ToString("F2"), category, stock.ToString(), status);

            textBoxProductName->Clear();
            textBoxProductPrice->Clear();
            textBoxProductCategory->Clear();
            textBoxProductStock->Clear();

            MessageBox::Show(L"Товар успешно добавлен!", L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void btnRemoveProduct_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewProducts->SelectedRows->Count > 0)
            {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    L"Удалить выбранный товар?", L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

                if (result == System::Windows::Forms::DialogResult::Yes)
                {
                    dataGridViewProducts->Rows->Remove(dataGridViewProducts->SelectedRows[0]);
                }
            }
            else
            {
                MessageBox::Show(L"Выберите товар для удаления", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        System::Void btnSaveProducts_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|CSV файлы (*.csv)|*.csv|Все файлы (*.*)|*.*";
            saveDialog->Title = L"Сохранить товары в файл";

            if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    StreamWriter^ writer = gcnew StreamWriter(saveDialog->FileName);
                    writer->WriteLine("Название товара;Цена;Категория;На складе;Статус");

                    for each (DataGridViewRow ^ row in dataGridViewProducts->Rows)
                    {
                        if (!row->IsNewRow)
                        {
                            writer->WriteLine(
                                row->Cells[0]->Value->ToString() + ";" +
                                row->Cells[1]->Value->ToString() + ";" +
                                row->Cells[2]->Value->ToString() + ";" +
                                row->Cells[3]->Value->ToString() + ";" +
                                row->Cells[4]->Value->ToString()
                            );
                        }
                    }

                    writer->Close();
                    MessageBox::Show(L"Товары сохранены в файл: " + saveDialog->FileName, L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show(L"Ошибка сохранения: " + ex->Message, L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        System::Void checkBoxInStockOnly_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
        {
            LoadDefaultProducts();

            if (checkBoxInStockOnly->Checked)
            {
                for (int i = dataGridViewProducts->Rows->Count - 1; i >= 0; i--)
                {
                    DataGridViewRow^ row = dataGridViewProducts->Rows[i];
                    if (!row->IsNewRow && safe_cast<String^>(row->Cells[4]->Value) == "Нет в наличии")
                    {
                        dataGridViewProducts->Rows->RemoveAt(i);
                    }
                }
            }
        }
    };
}