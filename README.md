# 🪟 nkentseu - Cross-Platform Window System

Système de fenêtrage cross-platform en C++ pur, style SFML.

## ✨ Fonctionnalités

- ✅ **6 Plateformes**: Windows, Linux, macOS, Android, iOS, Emscripten
- ✅ **Détection automatique**: Plateforme, Architecture, Compilateur
- ✅ **Multi-fenêtres**: Gestionnaire global avec IDs uniques
- ✅ **Événements typés**: WindowClosed, KeyPressed, MouseMoved, Touch...
- ✅ **Sleep haute précision**: Nano/Micro/Milliseconde
- ✅ **Boucle classique**: `while (running) { PollEvent(); Update(); Render(); }`
- ✅ **Software rendering**: Clear() et SwapBuffers() intégrés

## 🏗️ Structure

```
nkentseu_system/
├── Core/              # Bibliothèque (static lib)
│   ├── include/       # Headers publics
│   └── src/           # Implémentations
└── Sandbox/           # Application de test
```

## 🚀 Build

### Windows
```bash
python jenga.py build --platform Windows --config Release
```

### Linux
```bash
python jenga.py build --platform Linux --config Release
```

### Android
```bash
python jenga.py build --platform Android --config Release
```

### Emscripten
```bash
python jenga.py build --platform Emscripten --config Release
```

## 💻 Utilisation (style SFML)

```cpp
#include <nkentseu/Window/Window.h>
#include <nkentseu/Events/EventManager.h>
#include <nkentseu/Core/Sleep.h>

using namespace nkentseu;

int nkmain(int argc, char* argv[]) {
    Window* window = Window::Create("My App", 1280, 720);
    window->Initialize();
    window->Show();
    
    bool running = true;
    
    while (running) {
        // Poll events
        Event* event = nullptr;
        while (EventManager::PollEvent(&event)) {
            if (event->IsType<WindowClosedEvent>()) {
                running = false;
            }
            if (event->IsType<KeyPressedEvent>()) {
                auto& e = event->As<KeyPressedEvent>();
                if (e.GetKeyCode() == KeyCode::Escape) {
                    running = false;
                }
            }
        }
        
        // Render
        window->Clear({0.2f, 0.3f, 0.4f, 1.0f});
        window->SwapBuffers();
        
        // Sleep optionnel
        SleepMilli(1);
    }
    
    delete window;
    return 0;
}
```

## 📝 API Principale

### Window
```cpp
Window* window = Window::Create("Title", 1280, 720);
window->Initialize();
window->Show();
window->Clear(Color(r, g, b, a));
window->SwapBuffers();
uint32 id = window->GetID();
```

### Events
```cpp
Event* event;
while (EventManager::PollEvent(&event)) {
    if (event->IsType<WindowClosedEvent>()) { ... }
    if (event->IsType<KeyPressedEvent>()) { ... }
    if (event->IsType<MouseMovedEvent>()) { ... }
    if (event->IsType<TouchBeganEvent>()) { ... }
}
```

### Sleep
```cpp
SleepNano(1000);     // 1 microseconde
SleepMicro(1000);    // 1 milliseconde
SleepMilli(16);      // ~60 FPS
Sleep(1);            // 1 seconde
```

## 🎯 Corrections Jenga pour Android/Emscripten

Le système Jenga doit être modifié pour gérer correctement les entry points :

1. **Android**: Utiliser `android_main()` au lieu de `main()`
2. **Emscripten**: Ajouter flags `-s WASM=1 -s USE_SDL=2`

Voir `JENGA_FIXES.md` pour les détails.

## 📄 Licence

Copyright © 2026 nkentseu. Tous droits réservés.
