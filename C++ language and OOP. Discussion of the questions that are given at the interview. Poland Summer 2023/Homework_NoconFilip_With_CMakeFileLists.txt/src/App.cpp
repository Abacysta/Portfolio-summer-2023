#include "App.h"
#include <iostream>
#include <limits>

void App::Run() {
	CollectFiles();
	while (true) {
		int choice = GetUserChoice();
		HandleUserChoice(choice);
		if (choice == 3) { break; }
	}
}

void App::CollectFiles() {
    std::string path;
    while (true) {
        try {
            std::cout << "Give me a path to directory: \n";
            std::cin >> path;
            files = collector.CollectFiles(path);
            break;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cout << "Please enter a valid path.\n";
        }
    }
}

int App::GetUserChoice() {
    std::cout << "\nSelect report type:\n";
    std::cout << "1. TXT Report\n";
    std::cout << "2. JSON Report\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    while (std::cin.fail()) {
        std::cerr << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter choice: ";
        std::cin >> choice;
    }

    return choice;
}

void App::HandleUserChoice(int choice) {
    switch (choice) {
    case 1:
        GenerateReport(TXT, "ReportTxt");
        break;
    case 2:
        GenerateReport(JSON, "ReportJSON");
        break;
    case 3:
        std::cout << "Exiting...\n";
        break;
    default:
        std::cerr << "Invalid choice. Please select a valid option.\n";
    }
}

void App::GenerateReport(Type type, const std::string& reportName) {
    try {
        auto report = Factory::generateReport(type, files);
        std::cout << reportName << " has been generated successfully!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Failed to generate " << reportName << ": " << e.what() << std::endl;
    }
}