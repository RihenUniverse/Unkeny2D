// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Events/EventManager.h
// DESCRIPTION: Gestionnaire global d'événements avec système de callbacks,
//              file d'attente thread-safe et itérateur RAII (EventTracker).
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Nkentseu/Config/Export.h"
#include "Event.h"
#include <queue>
#include <memory>
#include <mutex>
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <algorithm>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: EventTracker
    // DESCRIPTION: Objet RAII pour l'itération sécurisée des événements.
    //              Permet une syntaxe de type "while (auto event = Track())"
    // -------------------------------------------------------------------------
    class EventTracker {
        public:
            /**
             * @brief Constructeur - commence le tracking des événements
             */
            EventTracker();
            
            /**
             * @brief Opérateur de conversion pour utilisation dans les boucles
             * @return true si un événement est disponible, false sinon
             */
            operator bool() const {
                return m_CurrentEvent != nullptr;
            }
            
            /**
             * @brief Opérateur flèche pour accès aux membres de l'événement
             * @return Pointeur vers l'événement courant
             */
            Event* operator->() {
                return m_CurrentEvent;
            }
            
            /**
             * @brief Opérateur d'indirection pour accès direct à l'événement
             * @return Référence à l'événement courant
             */
            Event& operator*() {
                return *m_CurrentEvent;
            }
            
            /**
             * @brief Passe à l'événement suivant dans la file
             * @return Référence à l'EventTracker (pour chaînage)
             */
            EventTracker& operator++();

        private:
            /// Événement courant en cours de traitement
            Event* m_CurrentEvent;
    };

    // -------------------------------------------------------------------------
    // CLASSE: ICallbackWrapper
    // DESCRIPTION: Interface de base pour les wrappers de callbacks typés
    // -------------------------------------------------------------------------
    class ICallbackWrapper {
        public:
            virtual ~ICallbackWrapper() = default;
            
            /**
             * @brief Appelle le callback avec l'événement spécifié
             * @param event Événement à passer au callback
             */
            virtual void Call(const Event* event) = 0;
            
            /**
             * @brief Obtient le type d'événement géré par ce wrapper
             * @return Type index de l'événement
             */
            virtual std::type_index GetEventType() const = 0;
    };

    // -------------------------------------------------------------------------
    // CLASSE TEMPLATE: CallbackWrapper
    // DESCRIPTION: Wrapper typé pour les callbacks d'événements spécifiques
    // -------------------------------------------------------------------------
    template<typename EventType>
    class CallbackWrapper : public ICallbackWrapper {
        public:
            /**
             * @brief Constructeur du wrapper de callback
             * @param callback Fonction callback à wrapper
             */
            explicit CallbackWrapper(std::function<void(const EventType&)> callback)
                : m_Callback(std::move(callback)) {}
            
            /**
             * @brief Appelle le callback si l'événement est du bon type
             * @param event Événement à traiter
             */
            void Call(const Event* event) override {
                if (event && event->IsType<EventType>()) {
                    m_Callback(event->As<EventType>());
                }
            }
            
            /**
             * @brief Obtient le type d'événement géré
             * @return Type index de l'événement template
             */
            std::type_index GetEventType() const override {
                return typeid(EventType);
            }
            
        private:
            /// Callback typé stocké
            std::function<void(const EventType&)> m_Callback;
    };

    // -------------------------------------------------------------------------
    // CLASSE: EventManager
    // DESCRIPTION: Gestionnaire global singleton d'événements avec file
    //              d'attente thread-safe et système de callbacks
    // -------------------------------------------------------------------------
    class NK_API EventManager {
        public:
            // ---------------------------------------------------------------------
            // API RAII POUR ITÉRATION
            // ---------------------------------------------------------------------
            
            /**
             * @brief Commence le tracking des événements disponibles
             * @return EventTracker pour itération RAII
             * 
             * @code
             * // Utilisation 1: Boucle while
             * while (auto event = EventManager::PollEvent()) {
             *     if (const auto* keyEvent = event->GetIf<KeyPressedEvent>()) {
             *         // Traitement...
             *     }
             *     ++event; // Passe à l'événement suivant
             * }
             * 
             * // Utilisation 2: Boucle for
             * for (auto& event : EventManager::PollEvent()) {
             *     // Traitement...
             * }
             * @endcode
             */
            static EventTracker PollEvent();
            
            /**
             * @brief Récupère le prochain événement de la file
             * @return Pointeur vers l'événement ou nullptr si vide
             * 
             * @attention La mémoire est gérée par EventManager.
             *            NE PAS appeler delete sur le résultat.
             *            Le pointeur reste valide jusqu'au prochain appel.
             */
            static Event* GetNextEvent();
            
            // ---------------------------------------------------------------------
            // GESTION DE LA FILE D'ÉVÉNEMENTS
            // ---------------------------------------------------------------------
            
            /**
             * @brief Ajoute un événement à la file de traitement
             * @param event Événement à ajouter (propriété transférée)
             */
            static void PushEvent(Event* event);
            
            /**
             * @brief Récupère le prochain événement de la file
             * @param outEvent Référence pour recevoir le pointeur d'événement
             * @return true si un événement a été récupéré, false si file vide
             */
            static bool PollEvent(Event*& outEvent);
            
            /**
             * @brief Vide complètement la file d'événements
             */
            static void ClearEvents();
            
            /**
             * @brief Obtient le nombre d'événements en attente
             * @return Nombre d'événements dans la file
             */
            static size_t GetEventCount();
            
            // ---------------------------------------------------------------------
            // API DE CALLBACKS GLOBALE
            // ---------------------------------------------------------------------
            
            /**
             * @brief Enregistre un callback pour un type d'événement spécifique
             * @tparam EventType Type d'événement à écouter
             * @param callback Fonction à appeler lorsque l'événement se produit
             */
            template<typename EventType>
            static void RegisterCallback(std::function<void(const EventType&)> callback);
            
            /**
             * @brief Désenregistre tous les callbacks pour un type d'événement
             * @tparam EventType Type d'événement à désenregistrer
             */
            template<typename EventType>
            static void UnregisterAllCallbacks();
            
            // ---------------------------------------------------------------------
            // API FLEXIBLE POUR LE TRAITEMENT D'ÉVÉNEMENTS
            // ---------------------------------------------------------------------
            
            /**
             * @brief Traite tous les événements avec les callbacks globaux
             */
            static void ProcessAllEvents();
            
            /**
             * @brief Gestion d'événements avec callbacks spécifiques (syntaxe simple)
             * @param onClose Callback pour fermeture de fenêtre
             * @param onKeyPressed Callback pour appui sur touche
             * @param onKeyReleased Callback pour relâchement de touche
             * @param onMouseMoved Callback pour mouvement de souris
             * @param onMousePressed Callback pour appui sur bouton souris
             * @param onMouseReleased Callback pour relâchement bouton souris
             * @param onMouseScrolled Callback pour défilement molette
             * @param onResized Callback pour redimensionnement fenêtre
             * @param onFocused Callback pour focus fenêtre
             * @param onUnfocused Callback pour perte de focus fenêtre
             */
            static void HandleEvents(
                std::function<void(const WindowClosedEvent&)> onClose = nullptr,
                std::function<void(const KeyPressedEvent&)> onKeyPressed = nullptr,
                std::function<void(const KeyReleasedEvent&)> onKeyReleased = nullptr,
                std::function<void(const MouseMovedEvent&)> onMouseMoved = nullptr,
                std::function<void(const MouseButtonPressedEvent&)> onMousePressed = nullptr,
                std::function<void(const MouseButtonReleasedEvent&)> onMouseReleased = nullptr,
                std::function<void(const MouseScrolledEvent&)> onMouseScrolled = nullptr,
                std::function<void(const WindowResizedEvent&)> onResized = nullptr,
                std::function<void(const WindowFocusedEvent&)> onFocused = nullptr,
                std::function<void(const WindowUnfocusedEvent&)> onUnfocused = nullptr
            );
            
            /**
             * @brief Pattern visitor pour traiter plusieurs types d'événements
             * @tparam Visitor Type du visitor (doit gérer tous les types d'événements)
             * @param visitor Objet visitor à appliquer à chaque événement
             */
            template<typename Visitor>
            static void VisitEvents(Visitor&& visitor);
            
            /**
             * @brief Traite un seul événement avec les callbacks appropriés
             * @param event Événement à traiter
             */
            static void ProcessEvent(Event* event);

        private:
            // ---------------------------------------------------------------------
            // VARIABLES STATIQUES PRIVÉES
            // ---------------------------------------------------------------------
            
            /// File d'attente thread-safe des événements
            static std::queue<std::unique_ptr<Event>> s_EventQueue;
            
            /// Mutex pour la synchronisation thread-safe
            static std::mutex s_Mutex;
            
            /// Événement courant en cours de traitement
            static std::unique_ptr<Event> s_CurrentEvent;
            
            /// Registre des callbacks organisés par type d'événement
            static std::unordered_map<std::type_index, std::vector<std::unique_ptr<ICallbackWrapper>>> s_Callbacks;
            
            // ---------------------------------------------------------------------
            // MÉTHODES TEMPLATE PRIVÉES
            // ---------------------------------------------------------------------
            
            /**
             * @brief Appelle tous les callbacks enregistrés pour un type d'événement
             * @tparam EventType Type d'événement à traiter
             * @param event Événement à passer aux callbacks
             */
            template<typename EventType>
            static void CallCallbacks(const EventType& event);
    };

    // =========================================================================
    // IMPLÉMENTATION DES MÉTHODES TEMPLATE
    // =========================================================================

    /**
     * @brief Enregistre un callback pour un type d'événement spécifique
     * @tparam EventType Type d'événement à écouter
     * @param callback Fonction à appeler lorsque l'événement se produit
     */
    template<typename EventType>
    void EventManager::RegisterCallback(std::function<void(const EventType&)> callback) {
        std::lock_guard<std::mutex> lock(s_Mutex);
        auto& callbacks = s_Callbacks[typeid(EventType)];
        callbacks.push_back(std::make_unique<CallbackWrapper<EventType>>(std::move(callback)));
    }

    /**
     * @brief Désenregistre tous les callbacks pour un type d'événement
     * @tparam EventType Type d'événement à désenregistrer
     */
    template<typename EventType>
    void EventManager::UnregisterAllCallbacks() {
        std::lock_guard<std::mutex> lock(s_Mutex);
        s_Callbacks.erase(typeid(EventType));
    }

    /**
     * @brief Appelle tous les callbacks enregistrés pour un type d'événement
     * @tparam EventType Type d'événement à traiter
     * @param event Événement à passer aux callbacks
     */
    template<typename EventType>
    void EventManager::CallCallbacks(const EventType& event) {
        auto it = s_Callbacks.find(typeid(EventType));
        if (it != s_Callbacks.end()) {
            for (auto& wrapper : it->second) {
                wrapper->Call(&event);
            }
        }
    }

    /**
     * @brief Pattern visitor pour traiter plusieurs types d'événements
     * @tparam Visitor Type du visitor
     * @param visitor Objet visitor à appliquer à chaque événement
     */
    template<typename Visitor>
    void EventManager::VisitEvents(Visitor&& visitor) {
        Event* event = nullptr;
        while (PollEvent(event)) {
            if (!event) continue;
            
            // Visiter l'événement avec le visitor selon son type
            switch (event->GetType()) {
                case EventType::WindowClosed:
                    if (const auto* e = event->GetIf<WindowClosedEvent>()) visitor(*e);
                    break;
                case EventType::WindowResized:
                    if (const auto* e = event->GetIf<WindowResizedEvent>()) visitor(*e);
                    break;
                case EventType::WindowFocused:
                    if (const auto* e = event->GetIf<WindowFocusedEvent>()) visitor(*e);
                    break;
                case EventType::WindowUnfocused:
                    if (const auto* e = event->GetIf<WindowUnfocusedEvent>()) visitor(*e);
                    break;
                case EventType::KeyPressed:
                    if (const auto* e = event->GetIf<KeyPressedEvent>()) visitor(*e);
                    break;
                case EventType::KeyReleased:
                    if (const auto* e = event->GetIf<KeyReleasedEvent>()) visitor(*e);
                    break;
                case EventType::MouseMoved:
                    if (const auto* e = event->GetIf<MouseMovedEvent>()) visitor(*e);
                    break;
                case EventType::MouseButtonPressed:
                    if (const auto* e = event->GetIf<MouseButtonPressedEvent>()) visitor(*e);
                    break;
                case EventType::MouseButtonReleased:
                    if (const auto* e = event->GetIf<MouseButtonReleasedEvent>()) visitor(*e);
                    break;
                case EventType::MouseScrolled:
                    if (const auto* e = event->GetIf<MouseScrolledEvent>()) visitor(*e);
                    break;
                case EventType::TouchBegan:
                    if (const auto* e = event->GetIf<TouchBeganEvent>()) visitor(*e);
                    break;
                case EventType::TouchMoved:
                    if (const auto* e = event->GetIf<TouchMovedEvent>()) visitor(*e);
                    break;
                case EventType::TouchEnded:
                    if (const auto* e = event->GetIf<TouchEndedEvent>()) visitor(*e);
                    break;
                default:
                    break;
            }
            
            event->SetHandled(true);
        }
    }

} // namespace nkentseu