// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Unkeny.h
// DESCRIPTION: Point d'entrée principal du framework Unkeny. Définit les
//              fonctions d'entrée spécifiques à chaque plateforme.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

/**
 * @brief Fonction d'entrée principale de l'application
 * @param argc Nombre d'arguments
 * @param argv Tableau d'arguments
 * @return Code de retour de l'application
 */
extern int nkmain(int argc, char* argv[]);

// -----------------------------------------------------------------------------
// POINTS D'ENTRÉE SPÉCIFIQUES À LA PLATEFORME
// -----------------------------------------------------------------------------

#if defined(NK_PLATFORM_WINDOWS)
    /**
     * @brief Point d'entrée Windows
     */
    int main(int argc, char* argv[]) {
        return nkmain(argc, argv);
    }
#elif defined(NK_PLATFORM_LINUX) || defined(NK_PLATFORM_EMSCRIPTEN)
    /**
     * @brief Point d'entrée Linux/Emscripten
     */
    int main(int argc, char* argv[]) {
        return nkmain(argc, argv);
    }
#elif defined(NK_PLATFORM_ANDROID)
    #include <android_native_app_glue.h>
    
    /**
     * @brief Point d'entrée Android
     * @param app Structure d'application Android
     */
    void android_main(struct android_app* app) {
        // TODO: Implémenter l'entrée Android
    }
#endif