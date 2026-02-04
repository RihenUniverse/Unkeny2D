// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Linux/WindowXCB.cpp
// DESCRIPTION: Implémentation Linux XCB de l'interface Window.
//              Utilise XCB (X Protocol C Binding) pour la gestion des fenêtres.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "WindowXCB.h"

// Compilation conditionnelle pour Linux uniquement
#ifdef NK_PLATFORM_LINUX

#include "Unkeny2D/Events/EventManager.h"
#include "Unkeny2D/Window/WindowManager.h"

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // VARIABLE GLOBALE PRIVÉE
    // -------------------------------------------------------------------------
    
    /// Compteur pour générer des IDs uniques de fenêtres XCB
    static uint32 g_NextWindowID = 1;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DE WindowXCB
    // -------------------------------------------------------------------------
    
    /**
     * @brief Constructeur de fenêtre XCB
     * @param title Titre de la fenêtre
     * @param width Largeur initiale
     * @param height Hauteur initiale
     */
    WindowXCB::WindowXCB(const char* title, uint32 width, uint32 height)
        : m_ID(g_NextWindowID++)
        , m_Title(title)
        , m_Width(width)
        , m_Height(height)
        , m_IsOpen(false)
        , m_Connection(nullptr)
        , m_Window(0)
        , m_Screen(nullptr)
        , m_GC(0)
    {
    }
    
    /**
     * @brief Destructeur de fenêtre XCB
     */
    WindowXCB::~WindowXCB() {
        Shutdown();
    }
    
    /**
     * @brief Initialise la fenêtre XCB
     * @return true si réussite, false sinon
     */
    bool WindowXCB::Initialize() {
        // Connexion au serveur X
        m_Connection = xcb_connect(nullptr, nullptr);
        if (xcb_connection_has_error(m_Connection)) return false;
        
        // Récupération de l'écran par défaut
        const xcb_setup_t* setup = xcb_get_setup(m_Connection);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
        m_Screen = iter.data;
        
        // Création de la fenêtre XCB
        m_Window = xcb_generate_id(m_Connection);
        
        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t values[2] = {
            m_Screen->white_pixel,
            XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | 
            XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_POINTER_MOTION |
            XCB_EVENT_MASK_STRUCTURE_NOTIFY
        };
        
        xcb_create_window(m_Connection, XCB_COPY_FROM_PARENT, m_Window, m_Screen->root,
                          0, 0, m_Width, m_Height, 1,
                          XCB_WINDOW_CLASS_INPUT_OUTPUT, m_Screen->root_visual,
                          mask, values);
        
        // Définition du titre de la fenêtre
        xcb_change_property(m_Connection, XCB_PROP_MODE_REPLACE, m_Window,
                           XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                           m_Title.length(), m_Title.c_str());
        
        // Création du contexte graphique (GC)
        m_GC = xcb_generate_id(m_Connection);
        xcb_create_gc(m_Connection, m_GC, m_Window, 0, nullptr);
        
        // Affichage de la fenêtre
        xcb_map_window(m_Connection, m_Window);
        xcb_flush(m_Connection);
        
        m_IsOpen = true;
        WindowManager::RegisterWindow(this);
        return true;
    }
    
    /**
     * @brief Libère les ressources de la fenêtre XCB
     */
    void WindowXCB::Shutdown() {
        if (m_Connection) {
            xcb_destroy_window(m_Connection, m_Window);
            xcb_disconnect(m_Connection);
            m_Connection = nullptr;
        }
        m_IsOpen = false;
        WindowManager::UnregisterWindow(this);
    }
    
    /**
     * @brief Affiche la fenêtre XCB
     */
    void WindowXCB::Show() {
        if (m_Connection) {
            xcb_map_window(m_Connection, m_Window);
            xcb_flush(m_Connection);
        }
    }
    
    /**
     * @brief Cache la fenêtre XCB
     */
    void WindowXCB::Hide() {
        if (m_Connection) {
            xcb_unmap_window(m_Connection, m_Window);
            xcb_flush(m_Connection);
        }
    }
    
    /**
     * @brief Traite les événements XCB
     */
    void WindowXCB::ProcessEvents() {
        xcb_generic_event_t* event;
        while ((event = xcb_poll_for_event(m_Connection))) {
            switch (event->response_type & ~0x80) {
                case XCB_KEY_PRESS: {
                    auto* kp = (xcb_key_press_event_t*)event;
                    EventManager::PushEvent(new KeyPressedEvent(m_ID, KeyCode::Unknown));
                    break;
                }
                case XCB_MOTION_NOTIFY: {
                    auto* mn = (xcb_motion_notify_event_t*)event;
                    EventManager::PushEvent(new MouseMovedEvent(m_ID, mn->event_x, mn->event_y));
                    break;
                }
                case XCB_CONFIGURE_NOTIFY: {
                    auto* cfg = (xcb_configure_notify_event_t*)event;
                    if (cfg->width != m_Width || cfg->height != m_Height) {
                        m_Width = cfg->width;
                        m_Height = cfg->height;
                        EventManager::PushEvent(new WindowResizedEvent(m_ID, m_Width, m_Height));
                    }
                    break;
                }
            }
            free(event);
        }
    }
    
    /**
     * @brief Efface la fenêtre avec une couleur (rendu software XCB)
     * @param color Couleur de fond
     */
    void WindowXCB::Clear(const Color& color) {
        if (!m_Connection) return;
        
        // Conversion de la couleur RGBA vers pixel XCB
        uint32_t pixel = ((uint32_t)(color.r * 255) << 16) |
                         ((uint32_t)(color.g * 255) << 8) |
                         ((uint32_t)(color.b * 255));
        
        xcb_change_gc(m_Connection, m_GC, XCB_GC_FOREGROUND, &pixel);
        
        // Remplissage du rectangle
        xcb_rectangle_t rect = { 0, 0, (uint16_t)m_Width, (uint16_t)m_Height };
        xcb_poly_fill_rectangle(m_Connection, m_Window, m_GC, 1, &rect);
        xcb_flush(m_Connection);
    }
    
    /**
     * @brief Échange les buffers (rendu software - no-op)
     */
    void WindowXCB::SwapBuffers() {
        // Rend software - pas d'échange de buffers nécessaire
    }

} // namespace nkentseu

#endif // NK_PLATFORM_LINUX