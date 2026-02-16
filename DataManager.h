#pragma once
// DataManager.h - Менеджер данных для связи Windows Forms с C++ классами
#pragma once

#include <msclr/marshal_cppstd.h>
#include <string>

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

// Включим ваши C++ классы
#include "ZhESManager.h"

namespace ZhESApp {

    public ref class DataManager
    {
    private:
        static DataManager^ instance = nullptr;
        static Object^ lockObject = gcnew Object();

        DataManager() {}

    public:
        static property DataManager^ Instance
        {
            DataManager^ get()
            {
                lock(lockObject)
                {
                    if (instance == nullptr)
                        instance = gcnew DataManager();
                    return instance;
                }
            }
        }

        // Добавить жильца
        bool AddResident(String^ lastName, String^ firstName, String^ address, bool hasBenefits, double discount)
        {
            try
            {
                // Преобразуем String^ в std::string
                std::string stdLastName = marshal_as<std::string>(lastName);
                std::string stdFirstName = marshal_as<std::string>(firstName);
                std::string stdAddress = marshal_as<std::string>(address);

                // Создаем стратегию
                CostCalculationStrategy* strategy;
                if (hasBenefits)
                    strategy = new WithBenefitsStrategy(discount);
                else
                    strategy = new NoBenefitsStrategy();

                // Создаем жильца
                Resident resident(stdLastName, stdFirstName, stdAddress, strategy);

                // Добавляем через менеджер
                ZhESManager& manager = ZhESManager::getInstance();
                return manager.addResident(resident);
            }
            catch (const std::exception& ex)
            {
                // Логирование ошибки (можно добавить)
                return false;
            }
        }

        // Получить всех жильцов
        List<array<String^>^>^ GetAllResidents()
        {
            List<array<String^>^>^ result = gcnew List<array<String^>^>();

            try
            {
                ZhESManager& manager = ZhESManager::getInstance();
                std::vector<Resident*> residents = manager.getAllResidents();

                for each (Resident * resident in residents)
                {
                    array<String^>^ row = gcnew array<String^>(5);
                    row[0] = gcnew String(resident->getLastName().c_str());
                    row[1] = gcnew String(resident->getFirstName().c_str());
                    row[2] = gcnew String(resident->getAddress().c_str());
                    row[3] = resident->hasBenefits() ? "Да" : "Нет";
                    row[4] = resident->getDiscountPercent().ToString("F1");

                    result->Add(row);
                }
            }
            catch (const std::exception&)
            {
                // Возвращаем пустой список при ошибке
            }

            return result;
        }

        // Удалить жильца
        bool RemoveResident(String^ lastName)
        {
            try
            {
                std::string stdLastName = marshal_as<std::string>(lastName);
                ZhESManager& manager = ZhESManager::getInstance();
                return manager.removeResident(stdLastName);
            }
            catch (const std::exception&)
            {
                return false;
            }
        }

        // Найти жильца
        array<String^>^ FindResident(String^ lastName)
        {
            try
            {
                std::string stdLastName = marshal_as<std::string>(lastName);
                ZhESManager& manager = ZhESManager::getInstance();
                Resident* resident = manager.findResidentByLastName(stdLastName);

                if (resident != nullptr)
                {
                    array<String^>^ result = gcnew array<String^>(5);
                    result[0] = gcnew String(resident->getLastName().c_str());
                    result[1] = gcnew String(resident->getFirstName().c_str());
                    result[2] = gcnew String(resident->getAddress().c_str());
                    result[3] = resident->hasBenefits() ? "Да" : "Нет";
                    result[4] = resident->getDiscountPercent().ToString("F1");

                    return result;
                }
            }
            catch (const std::exception&) {}

            return nullptr;
        }

        // Сохранить в файл
        bool SaveToFile(String^ filePath)
        {
            try
            {
                std::string stdPath = marshal_as<std::string>(filePath);
                ZhESManager& manager = ZhESManager::getInstance();
                manager.saveToFile(stdPath);
                return true;
            }
            catch (const std::exception&)
            {
                return false;
            }
        }

        // Загрузить из файла
        bool LoadFromFile(String^ filePath)
        {
            try
            {
                std::string stdPath = marshal_as<std::string>(filePath);
                ZhESManager& manager = ZhESManager::getInstance();
                manager.loadFromFile(stdPath);
                return true;
            }
            catch (const std::exception&)
            {
                return false;
            }
        }

        // Подсчитать общую стоимость
        double CalculateTotalCost()
        {
            try
            {
                ZhESManager& manager = ZhESManager::getInstance();
                return manager.calculateTotalServicesCost();
            }
            catch (const std::exception&)
            {
                return 0.0;
            }
        }

        // Получить статистику
        String^ GetStatistics()
        {
            try
            {
                ZhESManager& manager = ZhESManager::getInstance();
                int residentCount = manager.getResidentCount();
                int serviceCount = manager.getServiceCount();
                double totalCost = manager.calculateTotalServicesCost();

                // Подсчет жильцов со льготами
                auto residents = manager.getAllResidents();
                int withBenefits = 0;
                int withoutBenefits = 0;

                for each (Resident * resident in residents)
                {
                    if (resident->hasBenefits())
                        withBenefits++;
                    else
                        withoutBenefits++;
                }

                String^ stats = "=== СТАТИСТИКА ЖЭС ===\n\n";
                stats += "Количество жильцов: " + residentCount.ToString() + "\n";
                stats += "Жильцов со льготами: " + withBenefits.ToString() + "\n";
                stats += "Жильцов без льгот: " + withoutBenefits.ToString() + "\n";
                stats += "Количество услуг: " + serviceCount.ToString() + "\n";
                stats += "Общая стоимость услуг: " + totalCost.ToString("F2") + " руб.\n";

                return stats;
            }
            catch (const std::exception&)
            {
                return "Ошибка при получении статистики";
            }
        }
    };
}