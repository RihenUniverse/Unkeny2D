// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Android/WindowAndroid.cpp
// DESCRIPTION: Implémentation spécifique Android de l'interface Window.
//              Utilise Android Native App Glue pour la gestion des fenêtres.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "WindowAndroid.h"

// Compilation conditionnelle pour Android uniquement
#ifdef NK_PLATFORM_ANDROID

#include "Unkeny2D/Events/EventManager.h"
#include "Unkeny2D/Window/WindowManager.h"
#include <android/log.h>

// Macro pour le logging Android
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "nkentseu", __VA_ARGS__)

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // VARIABLE GLOBALE PRIVÉE
    // -------------------------------------------------------------------------
    
    /// Compteur pour générer des IDs uniques de fenêtres Android
    static uint32 g_NextWindowID = 1;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DE WindowAndroid
    // -------------------------------------------------------------------------
    
    /**
     * @brief Constructeur de fenêtre Android
     * @param title Titre de la fenêtre
     * @param width Largeur initiale
     * @param height Hauteur initiale
     */
    WindowAndroid::WindowAndroid(const char* title, uint32 width, uint32 height)
        : m_ID(g_NextWindowID++)
        , m_Title(title)
        , m_Width(width)
        , m_Height(height)
        , m_IsOpen(false)
        , m_App(nullptr)
    {
    }
    
    /**
     * @brief Destructeur de fenêtre Android
     */
    WindowAndroid::~WindowAndroid() {
        Shutdown();
    }
    
    /**
     * @brief Initialise la fenêtre Android
     * @return true si réussite, false sinon
     */
    bool WindowAndroid::Initialize() {
        if (!m_App) return false;
        
        // Configuration des callbacks Android
        m_App->userData = this;
        m_App->onAppCmd = HandleCmd;
        m_App->onInputEvent = HandleInput;
        
        m_IsOpen = true;
        WindowManager::RegisterWindow(this);
        LOGI("Android window initialized");
        return true;
    }
    
    /**
     * @brief Libère les ressources de la fenêtre Android
     */
    void WindowAndroid::Shutdown() {
        m_IsOpen = false;
        WindowManager::UnregisterWindow(this);
    }
    
    /**
     * @brief Traite les événements Android
     */
    void WindowAndroid::ProcessEvents() {
        if (!m_App) return;
        
        int events;
        struct android_poll_source* source;
        
        // Boucle de traitement des événements Android
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0) {
            if (source) {
                source->process(m_App, source);
            }
            
            // Gestion de la fermeture demandée
            if (m_App->destroyRequested) {
                EventManager::PushEvent(new WindowClosedEvent(m_ID));
                m_IsOpen = false;
            }
        }
    }
    
    /**
     * @brief Efface la fenêtre avec une couleur (stub pour Android)
     * @param color Couleur de fond
     */
    void WindowAndroid::Clear(const Color& color) {
        // TODO: Implémenter le rendu software pour Android
    }
    
    /**
     * @brief Échange les buffers (stub pour Android)
     */
    void WindowAndroid::SwapBuffers() {
        // TODO: Implémenter l'échange de buffers pour Android
    }
    
    /**
     * @brief Callback de commande Android
     * @param app Structure d'application Android
     * @param cmd Commande reçue
     */
    void WindowAndroid::HandleCmd(struct android_app* app, int32_t cmd) {
        auto* window = (WindowAndroid*)app->userData;
        
        switch (cmd) {
            case APP_CMD_INIT_WINDOW:
                if (app->window) {
                    window->m_Width = ANativeWindow_getWidth(app->window);
                    window->m_Height = ANativeWindow_getHeight(app->window);
                    EventManager::PushEvent(new WindowResizedEvent(window->m_ID, window->m_Width, window->m_Height));
                }
                break;
            case APP_CMD_TERM_WINDOW:
                EventManager::PushEvent(new WindowClosedEvent(window->m_ID));
                break;
        }
    }
    
    /**
     * @brief Callback d'entrée Android
     * @param app Structure d'application Android
     * @param event Événement d'entrée
     * @return 1 si événement traité, 0 sinon
     */
    int32_t WindowAndroid::HandleInput(struct android_app* app, AInputEvent* event) {
        auto* window = (WindowAndroid*)app->userData;
        
        if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
            float x = AMotionEvent_getX(event, 0);
            float y = AMotionEvent_getY(event, 0);
            int32_t id = AMotionEvent_getPointerId(event, 0);
            
            int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
            
            if (action == AMOTION_EVENT_ACTION_DOWN) {
                EventManager::PushEvent(new TouchBeganEvent(window->m_ID, id, x, y));
            }
            
            return 1;
        }
        
        return 0;
    }

} // namespace nkentseu

#endif // NK_PLATFORM_ANDROID