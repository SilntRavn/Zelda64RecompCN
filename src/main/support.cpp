#include "zelda_support.h"
#include <SDL.h>
#include "nfd.h"
#include "RmlUi/Core.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <array>
#include <spawn.h>
#include <unistd.h>
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
extern char** environ;
#endif

namespace zelda64 {
    // MARK: - Internal Helpers
    void perform_file_dialog_operation(const std::function<void(bool, const std::filesystem::path&)>& callback) {
        nfdnchar_t* native_path = nullptr;
        nfdresult_t result = NFD_OpenDialogN(&native_path, nullptr, 0, nullptr);

        bool success = (result == NFD_OKAY);
        std::filesystem::path path;

        if (success) {
            path = std::filesystem::path{native_path};
            NFD_FreePathN(native_path);
        }

        callback(success, path);
    }

    void perform_file_dialog_operation_multiple(const std::function<void(bool, const std::list<std::filesystem::path>&)>& callback) {
        const nfdpathset_t* native_paths = nullptr;
        nfdresult_t result = NFD_OpenDialogMultipleN(&native_paths, nullptr, 0, nullptr);

        bool success = (result == NFD_OKAY);
        std::list<std::filesystem::path> paths;
        nfdpathsetsize_t count = 0;

        if (success) {
            NFD_PathSet_GetCount(native_paths, &count);
            for (nfdpathsetsize_t i = 0; i < count; i++) {
                nfdnchar_t* cur_path = nullptr;
                nfdresult_t cur_result = NFD_PathSet_GetPathN(native_paths, i, &cur_path);
                if (cur_result == NFD_OKAY) {
                    paths.emplace_back(std::filesystem::path{cur_path});
                }
            }
            NFD_PathSet_Free(native_paths);
        }

        callback(success, paths);
    }

    // MARK: - Public API

    std::filesystem::path get_program_path() {
#if defined(__APPLE__)
        return get_bundle_resource_directory();
#elif defined(__linux__) && defined(RECOMP_FLATPAK)
        return "/app/bin";
#else
        return "";
#endif
    }

    std::filesystem::path get_asset_path(const char* asset) {
        return get_program_path() / "assets" / asset;
    }

    bool relaunch_application() {
#if defined(_WIN32)
        std::wstring executable_path(32768, L'\0');
        DWORD path_length = GetModuleFileNameW(nullptr, executable_path.data(), static_cast<DWORD>(executable_path.size()));
        if (path_length == 0 || path_length >= executable_path.size()) {
            return false;
        }
        executable_path.resize(path_length);

        std::wstring command_line = L"\"" + executable_path + L"\"";
        STARTUPINFOW startup_info{};
        startup_info.cb = sizeof(startup_info);
        PROCESS_INFORMATION process_info{};
        if (!CreateProcessW(
                executable_path.c_str(),
                command_line.data(),
                nullptr,
                nullptr,
                FALSE,
                0,
                nullptr,
                nullptr,
                &startup_info,
                &process_info)) {
            return false;
        }

        CloseHandle(process_info.hThread);
        CloseHandle(process_info.hProcess);
        return true;
#elif defined(__linux__) || defined(__APPLE__)
        std::filesystem::path executable_path;
#if defined(__linux__)
        std::array<char, 4096> path_buffer{};
        ssize_t path_length = readlink("/proc/self/exe", path_buffer.data(), path_buffer.size() - 1);
        if (path_length <= 0) {
            return false;
        }
        path_buffer[path_length] = '\0';
        executable_path = path_buffer.data();
#else
        uint32_t path_size = 0;
        _NSGetExecutablePath(nullptr, &path_size);
        std::vector<char> path_buffer(path_size);
        if (_NSGetExecutablePath(path_buffer.data(), &path_size) != 0) {
            return false;
        }
        executable_path = path_buffer.data();
#endif

        std::string executable_string = executable_path.string();
        char* child_argv[] = { executable_string.data(), nullptr };
        pid_t child_pid{};
        return posix_spawn(
            &child_pid,
            executable_string.c_str(),
            nullptr,
            nullptr,
            child_argv,
            environ
        ) == 0;
#else
        return false;
#endif
    }

    void open_file_dialog(std::function<void(bool success, const std::filesystem::path& path)> callback) {
#ifdef __APPLE__
        dispatch_on_ui_thread([callback]() {
            perform_file_dialog_operation(callback);
        });
#else
        perform_file_dialog_operation(callback);
#endif
    }

    void open_file_dialog_multiple(std::function<void(bool success, const std::list<std::filesystem::path>& paths)> callback) {
#ifdef __APPLE__
        dispatch_on_ui_thread([callback]() {
            perform_file_dialog_operation_multiple(callback);
        });
#else
        perform_file_dialog_operation_multiple(callback);
#endif
    }

    void show_error_message_box(const char *title, const char *message) {
#ifdef __APPLE__
    std::string title_copy(title);
    std::string message_copy(message);

    dispatch_on_ui_thread([title_copy, message_copy] {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title_copy.c_str(), message_copy.c_str(), nullptr);
    });
#else
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
#endif
    }
}
