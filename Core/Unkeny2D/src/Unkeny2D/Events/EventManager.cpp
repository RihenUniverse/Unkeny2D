// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Events/EventManager.cpp
// DESCRIPTION: Implémentation complète du gestionnaire d'événements avec
//              EventTracker RAII, file thread-safe et système de callbacks.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "Unkeny2D/Events/EventManager.h"
#include "Unkeny2D/Window/WindowManager.h"
#include <iostream>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // INITIALISATION DES VARIABLES STATIQUES
    // -------------------------------------------------------------------------
    
    /// File d'attente des événements
    std::queue<std::unique_ptr<Event>> EventManager::s_EventQueue;
    
    /// Mutex pour la synchronisation
    std::mutex EventManager::s_Mutex;
    
    /// Événement courant en traitement
    std::unique_ptr<Event> EventManager::s_CurrentEvent;
    
    /// Registre des callbacks par type d'événement
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<ICallbackWrapper>>> EventManager::s_Callbacks;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DE LA CLASSE EventTracker
    // -------------------------------------------------------------------------
    
    /**
     * @brief Constructeur de EventTracker
     * @details Récupère le premier événement disponible
     */
    EventTracker::EventTracker() {
        m_CurrentEvent = EventManager::GetNextEvent();
    }
    
    /**
     * @brief Opérateur de pré-incrémentation pour EventTracker
     * @return Référence à l'EventTracker après passage à l'événement suivant
     */
    EventTracker& EventTracker::operator++() {
        m_CurrentEvent = EventManager::GetNextEvent();
        return *this;
    }

    // =========================================================================
    // IMPLÉMENTATION DE L'API RAII D'EventManager
    // =========================================================================

    /**
     * @brief Commence le tracking des événements disponibles
     * @return EventTracker pour itération RAII
     */
    EventTracker EventManager::PollEvent() {
        return EventTracker();
    }
    
    /**
     * @brief Récupère le prochain événement de la file
     * @return Pointeur vers l'événement ou nullptr si file vide
     */
    Event* EventManager::GetNextEvent() {
        // Traiter d'abord les événements des fenêtres
        WindowManager::ProcessAllEvents();
        
        Event* result = nullptr;
        
        // Récupérer un événement de la file avec protection thread-safe
        {
            std::lock_guard<std::mutex> lock(s_Mutex);
            if (!s_EventQueue.empty()) {
                s_CurrentEvent = std::move(s_EventQueue.front());
                s_EventQueue.pop();
                result = s_CurrentEvent.get();
            }
        }
        
        return result;
    }

    // =========================================================================
    // IMPLÉMENTATION DE L'API TRADITIONNELLE D'EventManager
    // =========================================================================

    /**
     * @brief Ajoute un événement à la file de traitement
     * @param event Événement à ajouter (propriété transférée)
     */
    void EventManager::PushEvent(Event* event) {
        std::lock_guard<std::mutex> lock(s_Mutex);
        s_EventQueue.push(std::unique_ptr<Event>(event));
    }
    
    /**
     * @brief Récupère le prochain événement de la file
     * @param outEvent Référence pour recevoir le pointeur d'événement
     * @return true si un événement a été récupéré, false si file vide
     */
    bool EventManager::PollEvent(Event*& outEvent) {
        // 1. Traiter les événements des fenêtres (sans lock)
        WindowManager::ProcessAllEvents();
        
        // 2. Récupérer un événement de la file (avec lock)
        {
            std::lock_guard<std::mutex> lock(s_Mutex);
            if (s_EventQueue.empty()) {
                outEvent = nullptr;
                return false;
            }
            
            s_CurrentEvent = std::move(s_EventQueue.front());
            s_EventQueue.pop();
            outEvent = s_CurrentEvent.get();
        }
        
        return true;
    }
    
    /**
     * @brief Vide complètement la file d'événements
     */
    void EventManager::ClearEvents() {
        std::lock_guard<std::mutex> lock(s_Mutex);
        while (!s_EventQueue.empty()) {
            s_EventQueue.pop();
        }
    }
    
    /**
     * @brief Obtient le nombre d'événements en attente
     * @return Nombre d'événements dans la file
     */
    size_t EventManager::GetEventCount() {
        std::lock_guard<std::mutex> lock(s_Mutex);
        return s_EventQueue.size();
    }

    // =========================================================================
    // IMPLÉMENTATION DE L'API DE TRAITEMENT D'EventManager
    // =========================================================================

    /**
     * @brief Traite tous les événements avec les callbacks globaux
     */
    void EventManager::ProcessAllEvents() {
        Event* event = nullptr;
        while (PollEvent(event)) {
            if (event) {
                ProcessEvent(event);
            }
        }
    }
    
    /**
     * @brief Traite un seul événement avec les callbacks appropriés
     * @param event Événement à traiter
     */
    void EventManager::ProcessEvent(Event* event) {
        if (!event) return;
        
        // Appeler les callbacks appropriés selon le type d'événement
        switch (event->GetType()) {
            case EventType::WindowClosed:
                if (const auto* e = event->GetIf<WindowClosedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::WindowResized:
                if (const auto* e = event->GetIf<WindowResizedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::WindowFocused:
                if (const auto* e = event->GetIf<WindowFocusedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::WindowUnfocused:
                if (const auto* e = event->GetIf<WindowUnfocusedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::KeyPressed:
                if (const auto* e = event->GetIf<KeyPressedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::KeyReleased:
                if (const auto* e = event->GetIf<KeyReleasedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::MouseMoved:
                if (const auto* e = event->GetIf<MouseMovedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::MouseButtonPressed:
                if (const auto* e = event->GetIf<MouseButtonPressedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::MouseButtonReleased:
                if (const auto* e = event->GetIf<MouseButtonReleasedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::MouseScrolled:
                if (const auto* e = event->GetIf<MouseScrolledEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::TouchBegan:
                if (const auto* e = event->GetIf<TouchBeganEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::TouchMoved:
                if (const auto* e = event->GetIf<TouchMovedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            case EventType::TouchEnded:
                if (const auto* e = event->GetIf<TouchEndedEvent>()) {
                    CallCallbacks(*e);
                }
                break;
                
            default:
                break;
        }
    }
    
    /**
     * @brief Gestion d'événements avec callbacks spécifiques (syntaxe simple)
     */
    void EventManager::HandleEvents(
        std::function<void(const WindowClosedEvent&)> onClose,
        std::function<void(const KeyPressedEvent&)> onKeyPressed,
        std::function<void(const KeyReleasedEvent&)> onKeyReleased,
        std::function<void(const MouseMovedEvent&)> onMouseMoved,
        std::function<void(const MouseButtonPressedEvent&)> onMousePressed,
        std::function<void(const MouseButtonReleasedEvent&)> onMouseReleased,
        std::function<void(const MouseScrolledEvent&)> onMouseScrolled,
        std::function<void(const WindowResizedEvent&)> onResized,
        std::function<void(const WindowFocusedEvent&)> onFocused,
        std::function<void(const WindowUnfocusedEvent&)> onUnfocused
    ) {
        // Utiliser l'API Track() pour une syntaxe plus propre
        auto tracker = PollEvent();
        
        while (tracker) {
            Event* event = &(*tracker); // Obtenir l'événement du tracker
            
            // Traiter chaque type d'événement avec le callback approprié
            if (const auto* closedEvent = event->GetIf<WindowClosedEvent>()) {
                if (onClose) onClose(*closedEvent);
            }
            else if (const auto* keyPressedEvent = event->GetIf<KeyPressedEvent>()) {
                if (onKeyPressed) onKeyPressed(*keyPressedEvent);
            }
            else if (const auto* keyReleasedEvent = event->GetIf<KeyReleasedEvent>()) {
                if (onKeyReleased) onKeyReleased(*keyReleasedEvent);
            }
            else if (const auto* mouseMovedEvent = event->GetIf<MouseMovedEvent>()) {
                if (onMouseMoved) onMouseMoved(*mouseMovedEvent);
            }
            else if (const auto* mousePressedEvent = event->GetIf<MouseButtonPressedEvent>()) {
                if (onMousePressed) onMousePressed(*mousePressedEvent);
            }
            else if (const auto* mouseReleasedEvent = event->GetIf<MouseButtonReleasedEvent>()) {
                if (onMouseReleased) onMouseReleased(*mouseReleasedEvent);
            }
            else if (const auto* mouseScrolledEvent = event->GetIf<MouseScrolledEvent>()) {
                if (onMouseScrolled) onMouseScrolled(*mouseScrolledEvent);
            }
            else if (const auto* resizedEvent = event->GetIf<WindowResizedEvent>()) {
                if (onResized) onResized(*resizedEvent);
            }
            else if (const auto* focusedEvent = event->GetIf<WindowFocusedEvent>()) {
                if (onFocused) onFocused(*focusedEvent);
            }
            else if (const auto* unfocusedEvent = event->GetIf<WindowUnfocusedEvent>()) {
                if (onUnfocused) onUnfocused(*unfocusedEvent);
            }
            
            event->SetHandled(true);
            
            // Passer à l'événement suivant
            ++tracker;
        }
    }

} // namespace nkentseu