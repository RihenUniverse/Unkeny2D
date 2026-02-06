# 🎯 Sandbox - Application de Démonstration

**Sandbox** est l'application de test et de démonstration du framework Unkeny2D, servant à valider les fonctionnalités et à fournir des exemples d'utilisation.

## 🎯 Objectif

- **Valider** le fonctionnement du framework sur toutes les plateformes
- **Démontrer** les capacités et l'API d'Unkeny2D
- **Servir** de base pour le développement et les tests
- **Fournir** un exemple concret d'application complète

## 📋 Fonctionnalités Démonstrées

### 🪟 Système de Fenêtrage
- Création et gestion de fenêtre principale
- Traitement des événements (clavier, souris, fenêtre)
- Boucle de rendu classique SFML-style
- Gestion propre de la fermeture

### 📝 Logging Avancé
- Initialisation et configuration du logger
- Utilisation de tous les niveaux de log
- Formatage personnalisé des messages
- Logging contextuel (fichier, ligne, fonction)

### 🔍 Détection de Plateforme
- Affichage des informations système
- Détection automatique OS/Architecture/Compiler
- Comportement adaptatif selon la plateforme

### ⏱️ Timing et Performance
- Boucle de jeu à 60 FPS approximatifs
- Mesure du nombre de frames rendues
- Gestion du temps et de la synchronisation

## 🏗️ Architecture

```
Sandbox/
├── src/
│   └── Main.cpp                 # Point d'entrée principal
└── Sandbox.jenga               # Configuration build
```

## 💻 Code Source

### Point d'Entrée Principal
```cpp
#include <Unkeny2D/Window/Window.h>
#include <Unkeny2D/Events/EventManager.h>
#include <Nkentseu/Sleep.h>
#include <Nkentseu/Config/Platform.h>
#include <Nkentseu/Config/Compiler.h>
#include <Nkentseu/Config/Architecture.h>
#include <Unkeny2D/Unkeny.h>
#include <Logger/Log.h>
#include <Logger/Sinks/ConsoleSink.h>
#include <Logger/Sinks/FileSink.h>

int nkmain(int argc, char* argv[]) {
    // Initialisation complète du logging
    nkentseu::logger::NkentseuLogger::Initialize(
        "SandboxApp", 
        "[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] [%s] [%#] [%F] -> %v", 
        nkentseu::logger::LogLevel::Trace
    );
    
    // Affichage des informations système
    LOG_INFO("======================================");
    LOG_INFO("  Unkeny2D - Cross-Platform Window");
    LOG_INFO("  Platform: %s", GetPlatformName());
    LOG_INFO("  Architecture: %s", GetArchitectureName());
    LOG_INFO("  Compiler: %s", GetCompilerName());
    LOG_INFO("======================================");
    
    // Création de la fenêtre
    LOG_DEBUG("Creating window...");
    nkentseu::Window* window = nkentseu::Window::Create("Unkeny2D Demo", 1280, 720);
    
    if (!window->Initialize()) {
        LOG_ERROR("Failed to initialize window");
        LOG_CRITICAL("Critical error - cannot continue");
        return -1;
    }
    
    window->Show();
    LOG_INFO("Window created successfully (ID: %u)", window->GetID());
    
    // Boucle principale
    LOG_INFO("Entering main loop...");
    bool running = true;
    uint64 frameCount = 0;
    nkentseu::Color clearColor(0.2f, 0.3f, 0.4f, 1.0f);
    
    while (running) {
        // Traitement des événements
        nkentseu::Event* event;
        while (nkentseu::EventManager::PollEvent(&event)) {
            if (event->IsType<nkentseu::WindowClosedEvent>()) {
                auto* closeEvent = static_cast<nkentseu::WindowClosedEvent*>(event);
                if (closeEvent->GetWindowID() == window->GetID()) {
                    LOG_INFO("Window closed event received");
                    running = false;
                }
            }
            else if (event->IsType<nkentseu::WindowResizedEvent>()) {
                auto* resizeEvent = static_cast<nkentseu::WindowResizedEvent*>(event);
                LOG_INFO("Window resized to %ux%u", 
                         resizeEvent->GetWidth(), resizeEvent->GetHeight());
            }
            else if (event->IsType<nkentseu::KeyPressedEvent>()) {
                auto* keyEvent = static_cast<nkentseu::KeyPressedEvent*>(event);
                LOG_DEBUG("Key pressed: %d", keyEvent->GetKeyCode());
            }
            else if (event->IsType<nkentseu::MouseMovedEvent>()) {
                auto* mouseEvent = static_cast<nkentseu::MouseMovedEvent*>(event);
                LOG_TRACE("Mouse moved to (%.1f, %.1f)", 
                          mouseEvent->GetX(), mouseEvent->GetY());
            }
        }
        
        // Rendu
        window->Clear(clearColor);
        window->SwapBuffers();
        
        frameCount++;
        
        // Timing approximatif pour ~60 FPS
        nkentseu::SleepMilli(16);
    }
    
    // Nettoyage
    LOG_INFO("Exiting main loop");
    LOG_INFO("Total frames rendered: %llu", frameCount);
    
    delete window;
    
    LOG_INFO("Application shutdown complete");
    LOG_INFO("======================================");
    
    return 0;
}
```

## 🚀 Exécution

### Build et Exécution
```bash
# Build en mode Debug
jenga build --config Debug

# Exécution
jenga run --config Debug

# Build en mode Release  
jenga build --config Release
jenga run --config Release
```

### Comportement Attendu
1. **Démarrage** : Affichage des informations système
2. **Fenêtre** : Création d'une fenêtre 1280x720
3. **Logging** : Messages de tous niveaux dans la console
4. **Événements** : Capture clavier/souris/fenêtre
5. **Rendu** : Fond bleu-vert avec double buffering
6. **Fermeture** : Nettoyage propre à la fermeture

## 🔧 Personnalisation

### Modifier la Résolution
```cpp
// Dans Main.cpp, ligne ~49
nkentseu::Window* window = nkentseu::Window::Create("Unkeny2D Demo", 1920, 1080);
```

### Changer la Couleur de Fond
```cpp
// Dans Main.cpp, ligne ~55
nkentseu::Color clearColor(0.8f, 0.2f, 0.1f, 1.0f); // Rouge
```

### Ajuster le Framerate
```cpp
// Dans Main.cpp, ligne ~84
nkentseu::SleepMilli(33); // ~30 FPS au lieu de 60
```

### Modifier le Niveau de Log
```cpp
// Dans Main.cpp, ligne ~26
nkentseu::logger::NkentseuLogger::Initialize(
    "SandboxApp", 
    "[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] [%s] [%#] [%F] -> %v", 
    nkentseu::logger::LogLevel::Info // Seulement INFO et supérieur
);
```

## 🧪 Validation par Plateforme

### Windows ✅
- [x] Fenêtre Win32 fonctionnelle
- [x] Événements clavier/souris
- [x] Rendu software
- [x] Logging console

### Linux ✅  
- [x] Fenêtre XCB fonctionnelle
- [x] Événements X11
- [x] Compatibilité multi-desktop

### Android ✅
- [x] Native Activity
- [x] Événements tactiles
- [x] Integration système

### Emscripten ✅
- [x] Compilation WebAssembly
- [x] Canvas HTML5
- [x] Événements navigateur

### macOS 🔄
- [ ] Implémentation Cocoa en cours
- [ ] Événements macOS

### iOS 🔄
- [ ] Implémentation UIKit en cours
- [ ] Événements iOS

## 📊 Métriques de Performance

### Sur Windows (Debug)
- **Framerate** : ~60 FPS stable
- **Mémoire** : < 10MB RAM
- **CPU** : < 1% en idle
- **Démarrage** : < 100ms

### Logging Typique
```
[2026-02-05 21:28:02.824] [INF] [SandboxApp] [Main.cpp] [38] [nkmain] -> ======================================
[2026-02-05 21:28:02.825] [INF] [SandboxApp] [Main.cpp] [39] [nkmain] ->   Unkeny2D - Cross-Platform Window
[2026-02-05 21:28:02.825] [INF] [SandboxApp] [Main.cpp] [40] [nkmain] ->   Platform: Windows
...
[2026-02-05 21:28:21.468] [INF] [SandboxApp] [Main.cpp] [83] [nkmain] -> Window closed event received
[2026-02-05 21:28:21.469] [INF] [SandboxApp] [Main.cpp] [144] [nkmain] -> Exiting main loop
[2026-02-05 21:28:21.470] [INF] [SandboxApp] [Main.cpp] [145] [nkmain] -> Total frames rendered: 17620
```

## 🔮 Extensions Possibles

### Court Terme
- [ ] Ajout de rendu OpenGL de base
- [ ] Affichage de formes géométriques simples
- [ ] Système de particules basique
- [ ] Interface texte minimaliste

### Moyen Terme
- [ ] Éditeur de scène simple
- [ ] Chargement d'images/textures
- [ ] Système d'animation sprite
- [ ] Audio basique

### Long Terme
- [ ] Jeu de démonstration complet
- [ ] Interface utilisateur avancée
- [ ] Système de plugins
- [ ] Multiples exemples spécialisés

---

**Sandbox** - Votre terrain de jeu pour explorer Unkeny2D ! 🎯