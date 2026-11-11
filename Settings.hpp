#pragma once
#include <string>
#include <windows.h>

class Settings {
public:
    // Pass the name of your settings file (e.g., "config.ini")
    Settings(const std::wstring& filename);

    // Save the combobox index
    void SaveComboIndex(int index);

    // Load the combobox index (returns 0 as a default if not found)
    int LoadComboIndex();

private:
    std::wstring m_filePath;
};