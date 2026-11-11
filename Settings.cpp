#include "Settings.hpp"
#include <filesystem>

Settings::Settings(const std::wstring& filename) {
    // Get the absolute path to the executable's directory so the .ini file saves next to it
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::filesystem::path appPath(buffer);
    m_filePath = appPath.parent_path() / filename;
}

void Settings::SaveComboIndex(int index) {
    // Convert int to wstring, then write to the INI file
    std::wstring indexStr = std::to_wstring(index);
    WritePrivateProfileString(
        L"UI_Settings",       // Section name like [UI_Settings]
        L"LastComboIndex",    // Key name
        indexStr.c_str(),     // Value to save
        m_filePath.c_str()    // File path
    );
}

int Settings::LoadComboIndex() {
    // Read the integer from the INI file, defaulting to 0 if it doesn't exist yet
    return GetPrivateProfileInt(
        L"UI_Settings",       // Section name
        L"LastComboIndex",    // Key name
        0,                    // Default value
        m_filePath.c_str()    // File path
    );
}