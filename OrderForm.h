#pragma once
#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;

namespace OnlineShopApp {

    public ref class OrderForm : public Form
    {
    public:
        OrderForm(String^ customerName)
        {
            InitializeComponent();
            this->Text = L"Создание заказа для: " + customerName;
            lblCustomer->Text = L"Клиент: " + customerName;
            LoadProducts();
            UpdateTotal();
        }

        // Свойства для получения данных заказа
        property List<String^>^ SelectedProducts
        {
            List<String^>^ get() { return selectedProducts; }
        }

        property double TotalAmount
        {
            double get() { return totalAmount; }
        }

    protected:
        ~OrderForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblCustomer;
        System::Windows::Forms::DataGridView^ dataGridViewProducts;
        System::Windows::Forms::NumericUpDown^ numericQuantity;
        System::Windows::Forms::Button^ btnAddToCart;
        System::Windows::Forms::DataGridView^ dataGridViewCart;
        System::Windows::Forms::Button^ btnRemoveFromCart;
        System::Windows::Forms::Button^ btnCompleteOrder;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ lblTotal;
        System::ComponentModel::Container^ components;

        List<String^>^ selectedProducts;
        double totalAmount;
        Dictionary<String^, double>^ productPrices;

        void InitializeComponent(void)
        {
            this->lblCustomer = (gcnew System::Windows::Forms::Label());
            this->dataGridViewProducts = (gcnew System::Windows::Forms::DataGridView());
            this->numericQuantity = (gcnew System::Windows::Forms::NumericUpDown());
            this->btnAddToCart = (gcnew System::Windows::Forms::Button());
            this->dataGridViewCart = (gcnew System::Windows::Forms::DataGridView());
            this->btnRemoveFromCart = (gcnew System::Windows::Forms::Button());
            this->btnCompleteOrder = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->lblTotal = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewProducts))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericQuantity))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewCart))->BeginInit();
            this->SuspendLayout();

            // lblCustomer
            this->lblCustomer->AutoSize = true;
            this->lblCustomer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblCustomer->Location = System::Drawing::Point(20, 20);
            this->lblCustomer->Name = L"lblCustomer";
            this->lblCustomer->Size = System::Drawing::Size(140, 17);
            this->lblCustomer->TabIndex = 0;
            this->lblCustomer->Text = L"Клиент: ";

            // dataGridViewProducts (список товаров)
            this->dataGridViewProducts->AllowUserToAddRows = false;
            this->dataGridViewProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewProducts->Location = System::Drawing::Point(20, 60);
            this->dataGridViewProducts->Name = L"dataGridViewProducts";
            this->dataGridViewProducts->ReadOnly = true;
            this->dataGridViewProducts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dataGridViewProducts->Size = System::Drawing::Size(350, 200);
            this->dataGridViewProducts->TabIndex = 1;

            // Добавляем колонки для товаров
            this->dataGridViewProducts->Columns->Add("Name", "Название товара");
            this->dataGridViewProducts->Columns->Add("Price", "Цена (руб.)");
            this->dataGridViewProducts->Columns->Add("Category", "Категория");
            this->dataGridViewProducts->Columns->Add("InStock", "В наличии");

            // numericQuantity
            this->numericQuantity->Location = System::Drawing::Point(400, 60);
            this->numericQuantity->Name = L"numericQuantity";
            this->numericQuantity->Size = System::Drawing::Size(80, 20);
            this->numericQuantity->TabIndex = 2;
            this->numericQuantity->Minimum = Decimal(1);
            this->numericQuantity->Maximum = Decimal(100);
            this->numericQuantity->Value = Decimal(1);

            // btnAddToCart
            this->btnAddToCart->Location = System::Drawing::Point(400, 90);
            this->btnAddToCart->Name = L"btnAddToCart";
            this->btnAddToCart->Size = System::Drawing::Size(120, 30);
            this->btnAddToCart->TabIndex = 3;
            this->btnAddToCart->Text = L"Добавить в корзину";
            this->btnAddToCart->UseVisualStyleBackColor = true;
            this->btnAddToCart->Click += gcnew System::EventHandler(this, &OrderForm::btnAddToCart_Click);

            // dataGridViewCart (корзина)
            this->dataGridViewCart->AllowUserToAddRows = false;
            this->dataGridViewCart->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewCart->Location = System::Drawing::Point(20, 280);
            this->dataGridViewCart->Name = L"dataGridViewCart";
            this->dataGridViewCart->ReadOnly = true;
            this->dataGridViewCart->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dataGridViewCart->Size = System::Drawing::Size(350, 150);
            this->dataGridViewCart->TabIndex = 4;

            // Колонки для корзины
            this->dataGridViewCart->Columns->Add("Name", "Товар");
            this->dataGridViewCart->Columns->Add("Quantity", "Кол-во");
            this->dataGridViewCart->Columns->Add("Price", "Цена за шт.");
            this->dataGridViewCart->Columns->Add("Total", "Сумма");

            // btnRemoveFromCart
            this->btnRemoveFromCart->Location = System::Drawing::Point(400, 320);
            this->btnRemoveFromCart->Name = L"btnRemoveFromCart";
            this->btnRemoveFromCart->Size = System::Drawing::Size(120, 30);
            this->btnRemoveFromCart->TabIndex = 5;
            this->btnRemoveFromCart->Text = L"Удалить из корзины";
            this->btnRemoveFromCart->UseVisualStyleBackColor = true;
            this->btnRemoveFromCart->Click += gcnew System::EventHandler(this, &OrderForm::btnRemoveFromCart_Click);

            // btnCompleteOrder
            this->btnCompleteOrder->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->btnCompleteOrder->Location = System::Drawing::Point(300, 450);
            this->btnCompleteOrder->Name = L"btnCompleteOrder";
            this->btnCompleteOrder->Size = System::Drawing::Size(120, 30);
            this->btnCompleteOrder->TabIndex = 6;
            this->btnCompleteOrder->Text = L"Оформить заказ";
            this->btnCompleteOrder->UseVisualStyleBackColor = true;
            this->btnCompleteOrder->Click += gcnew System::EventHandler(this, &OrderForm::btnCompleteOrder_Click);

            // btnCancel
            this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->btnCancel->Location = System::Drawing::Point(430, 450);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(120, 30);
            this->btnCancel->TabIndex = 7;
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->UseVisualStyleBackColor = true;

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(20, 40);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(95, 13);
            this->label1->TabIndex = 8;
            this->label1->Text = L"Доступные товары:";

            // label2
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(400, 40);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(66, 13);
            this->label2->TabIndex = 9;
            this->label2->Text = L"Количество:";

            // label3
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(20, 260);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(53, 13);
            this->label3->TabIndex = 10;
            this->label3->Text = L"Корзина:";

            // lblTotal
            this->lblTotal->AutoSize = true;
            this->lblTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblTotal->Location = System::Drawing::Point(20, 455);
            this->lblTotal->Name = L"lblTotal";
            this->lblTotal->Size = System::Drawing::Size(123, 17);
            this->lblTotal->TabIndex = 11;
            this->lblTotal->Text = L"Общая сумма: 0 руб.";

            // OrderForm
            this->AcceptButton = this->btnCompleteOrder;
            this->CancelButton = this->btnCancel;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(570, 500);
            this->Controls->Add(this->lblTotal);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnCompleteOrder);
            this->Controls->Add(this->btnRemoveFromCart);
            this->Controls->Add(this->dataGridViewCart);
            this->Controls->Add(this->btnAddToCart);
            this->Controls->Add(this->numericQuantity);
            this->Controls->Add(this->dataGridViewProducts);
            this->Controls->Add(this->lblCustomer);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"OrderForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewProducts))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericQuantity))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewCart))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

            selectedProducts = gcnew List<String^>();
            productPrices = gcnew Dictionary<String^, double>();
        }

        void LoadProducts()
        {
            dataGridViewProducts->Rows->Clear();

            // Загружаем товары из магазина
            dataGridViewProducts->Rows->Add("Смартфон", "25000.00", "Электроника", "50");
            dataGridViewProducts->Rows->Add("Ноутбук", "50000.00", "Электроника", "30");
            dataGridViewProducts->Rows->Add("Наушники", "8000.00", "Электроника", "100");
            dataGridViewProducts->Rows->Add("Планшет", "12000.00", "Электроника", "40");
            dataGridViewProducts->Rows->Add("Футболка", "1500.00", "Одежда", "200");
            dataGridViewProducts->Rows->Add("Джинсы", "4000.00", "Одежда", "150");

            // Сохраняем цены для быстрого доступа
            productPrices["Смартфон"] = 25000.0;
            productPrices["Ноутбук"] = 50000.0;
            productPrices["Наушники"] = 8000.0;
            productPrices["Планшет"] = 12000.0;
            productPrices["Футболка"] = 1500.0;
            productPrices["Джинсы"] = 4000.0;
        }

        void UpdateTotal()
        {
            totalAmount = 0.0;

            for each (DataGridViewRow ^ row in dataGridViewCart->Rows)
            {
                if (!row->IsNewRow)
                {
                    double rowTotal = Convert::ToDouble(row->Cells[3]->Value);
                    totalAmount += rowTotal;
                }
            }

            lblTotal->Text = String::Format(L"Общая сумма: {0:F2} руб.", totalAmount);
        }

    private:
        System::Void btnAddToCart_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewProducts->SelectedRows->Count == 0)
            {
                MessageBox::Show(L"Выберите товар из списка!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ selectedRow = dataGridViewProducts->SelectedRows[0];
            String^ productName = safe_cast<String^>(selectedRow->Cells[0]->Value);
            double price = Convert::ToDouble(selectedRow->Cells[1]->Value);
            int quantity = (int)numericQuantity->Value;
            double total = price * quantity;

            // Проверяем наличие товара
            int inStock = Convert::ToInt32(selectedRow->Cells[3]->Value);
            if (quantity > inStock)
            {
                MessageBox::Show(L"Недостаточно товара на складе!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            // Добавляем в корзину
            dataGridViewCart->Rows->Add(
                productName,
                quantity.ToString(),
                price.ToString("F2"),
                total.ToString("F2")
            );

            // Добавляем в список выбранных товаров
            selectedProducts->Add(String::Format("{0} x{1} = {2:F2} руб.", productName, quantity, total));

            // Обновляем общую сумму
            UpdateTotal();

            MessageBox::Show(L"Товар добавлен в корзину!",
                L"Успех",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnRemoveFromCart_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCart->SelectedRows->Count == 0)
            {
                MessageBox::Show(L"Выберите товар из корзины для удаления!",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            DataGridViewRow^ selectedRow = dataGridViewCart->SelectedRows[0];
            int rowIndex = selectedRow->Index;

            // Удаляем из списка выбранных товаров
            if (rowIndex < selectedProducts->Count)
            {
                selectedProducts->RemoveAt(rowIndex);
            }

            // Удаляем из корзины
            dataGridViewCart->Rows->Remove(selectedRow);

            // Обновляем общую сумму
            UpdateTotal();

            MessageBox::Show(L"Товар удален из корзины!",
                L"Успех",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        System::Void btnCompleteOrder_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridViewCart->Rows->Count == 0 ||
                (dataGridViewCart->Rows->Count == 1 && dataGridViewCart->Rows[0]->IsNewRow))
            {
                MessageBox::Show(L"Корзина пуста! Добавьте товары перед оформлением заказа.",
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                this->DialogResult = System::Windows::Forms::DialogResult::None;
                return;
            }

            System::Windows::Forms::DialogResult result = MessageBox::Show(
                String::Format(L"Оформить заказ на сумму {0:F2} руб.?", totalAmount),
                L"Подтверждение заказа",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::No)
            {
                this->DialogResult = System::Windows::Forms::DialogResult::None;
            }
        }
    };
}