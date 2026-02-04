// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Win32/WindowWin32.cpp
// DESCRIPTION: Implémentation Win32 de l'interface Window.
//              Utilise l'API Windows native (Win32) pour la gestion des fenêtres.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "WindowWin32.h"

// Compilation conditionnelle pour Windows uniquement
#ifdef NK_PLATFORM_WINDOWS

#include "Unkeny2D/Events/EventManager.h"
#include "Unkeny2D/Window/WindowManager.h"
#include <windowsx.h>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // VARIABLES GLOBALES PRIVÉES
    // -------------------------------------------------------------------------
    
    /// Compteur pour générer des IDs uniques de fenêtres Win32
    static uint32 g_NextWindowID = 1;
    
    /// Nom de la classe de fenêtre Win32
    static const wchar_t* WINDOW_CLASS_NAME = L"NkentseuWindowClass";
    
    /// Indicateur d'enregistrement de classe
    static bool g_ClassRegistered = false;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DE WindowWin32
    // -------------------------------------------------------------------------
    
    /**
     * @brief Constructeur de fenêtre Win32
     * @param title Titre de la fenêtre
     * @param width Largeur initiale
     * @param height Hauteur initiale
     */
    WindowWin32::WindowWin32(const char* title, uint32 width, uint32 height)
        : m_ID(g_NextWindowID++)
        , m_Title(title)
        , m_Width(width)
        , m_Height(height)
        , m_IsOpen(false)
        , m_Hwnd(nullptr)
        , m_Hdc(nullptr)
    {
        m_Hinstance = GetModuleHandle(nullptr);
    }
    
    /**
     * @brief Destructeur de fenêtre Win32
     */
    WindowWin32::~WindowWin32() {
        Shutdown();
    }
    
    /**
     * @brief Initialise la fenêtre Win32
     * @return true si réussite, false sinon
     */
    bool WindowWin32::Initialize() {
        // Enregistrement de la classe de fenêtre (une seule fois)
        if (!g_ClassRegistered) {
            WNDCLASSEXW wc = {};
            wc.cbSize = sizeof(WNDCLASSEXW);
            wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = m_Hinstance;
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.lpszClassName = WINDOW_CLASS_NAME;
            
            if (!RegisterClassExW(&wc)) return false;
            g_ClassRegistered = true;
        }
        
        // Calcul du rectangle client avec ajustement pour les bordures
        RECT rect = { 0, 0, (LONG)m_Width, (LONG)m_Height };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        
        // Conversion du titre UTF-8 vers UTF-16
        int titleLen = MultiByteToWideChar(CP_UTF8, 0, m_Title.c_str(), -1, nullptr, 0);
        wchar_t* wTitle = new wchar_t[titleLen];
        MultiByteToWideChar(CP_UTF8, 0, m_Title.c_str(), -1, wTitle, titleLen);
        
        // Création de la fenêtre
        m_Hwnd = CreateWindowExW(
            0, WINDOW_CLASS_NAME, wTitle, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            rect.right - rect.left, rect.bottom - rect.top,
            nullptr, nullptr, m_Hinstance, this
        );
        
        delete[] wTitle;
        
        if (!m_Hwnd) return false;
        
        // Obtention du contexte de périphérique
        m_Hdc = GetDC(m_Hwnd);
        m_IsOpen = true;
        
        WindowManager::RegisterWindow(this);
        return true;
    }
    
    /**
     * @brief Libère les ressources de la fenêtre Win32
     */
    void WindowWin32::Shutdown() {
        if (m_Hdc) {
            ReleaseDC(m_Hwnd, m_Hdc);
            m_Hdc = nullptr;
        }
        if (m_Hwnd) {
            DestroyWindow(m_Hwnd);
            m_Hwnd = nullptr;
        }
        m_IsOpen = false;
        WindowManager::UnregisterWindow(this);
    }
    
    /**
     * @brief Affiche la fenêtre Win32
     */
    void WindowWin32::Show() {
        if (m_Hwnd) {
            ShowWindow(m_Hwnd, SW_SHOW);
            UpdateWindow(m_Hwnd);
        }
    }
    
    /**
     * @brief Cache la fenêtre Win32
     */
    void WindowWin32::Hide() {
        if (m_Hwnd) ShowWindow(m_Hwnd, SW_HIDE);
    }
    
    /**
     * @brief Traite les messages Windows
     */
    void WindowWin32::ProcessEvents() {
        MSG msg;
        while (PeekMessageW(&msg, m_Hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    
    /**
     * @brief Efface la fenêtre avec une couleur (GDI)
     * @param color Couleur de fond
     */
    void WindowWin32::Clear(const Color& color) {
        if (!m_Hdc) return;
        
        RECT rect;
        GetClientRect(m_Hwnd, &rect);
        
        // Création d'un brush GDI avec la couleur spécifiée
        HBRUSH brush = CreateSolidBrush(RGB(
            (BYTE)(color.r * 255),
            (BYTE)(color.g * 255),
            (BYTE)(color.b * 255)
        ));
        
        FillRect(m_Hdc, &rect, brush);
        DeleteObject(brush);
    }
    
    /**
     * @brief Échange les buffers (rendu software - no-op)
     */
    void WindowWin32::SwapBuffers() {
        // Rend software - pas d'échange de buffers nécessaire
    }
    
    /**
     * @brief Procédure de fenêtre Win32 (callback système)
     * @param hwnd Handle de fenêtre
     * @param msg Message Windows
     * @param wParam Paramètre W
     * @param lParam Paramètre L
     * @return Résultat du traitement
     */
    LRESULT CALLBACK WindowWin32::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        WindowWin32* window = nullptr;
        
        // Récupération de l'instance WindowWin32 depuis les données utilisateur
        if (msg == WM_CREATE) {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = reinterpret_cast<WindowWin32*>(cs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        } else {
            window = reinterpret_cast<WindowWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }
        
        if (!window) return DefWindowProcW(hwnd, msg, wParam, lParam);
        
        // Traitement des messages Windows
        switch (msg) {
            case WM_CLOSE:
                EventManager::PushEvent(new WindowClosedEvent(window->m_ID));
                window->m_IsOpen = false;
                return 0;
            
            case WM_SIZE: {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                window->m_Width = width;
                window->m_Height = height;
                EventManager::PushEvent(new WindowResizedEvent(window->m_ID, width, height));
                return 0;
            }
            
            case WM_KEYDOWN: {
                KeyCode key = KeyCode::Unknown;
                if (wParam >= 'A' && wParam <= 'Z') {
                    key = (KeyCode)((int)KeyCode::A + (wParam - 'A'));
                } else if (wParam == VK_ESCAPE) {
                    key = KeyCode::Escape;
                } else if (wParam == VK_RETURN) {
                    key = KeyCode::Enter;
                }
                EventManager::PushEvent(new KeyPressedEvent(window->m_ID, key));
                return 0;
            }
            
            case WM_MOUSEMOVE: {
                float x = (float)GET_X_LPARAM(lParam);
                float y = (float)GET_Y_LPARAM(lParam);
                EventManager::PushEvent(new MouseMovedEvent(window->m_ID, x, y));
                return 0;
            }
        }
        
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

} // namespace nkentseu

#endif // NK_PLATFORM_WINDOWS