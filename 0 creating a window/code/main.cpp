//
// Este código es de dominio público
// angel.rodriguez@udit.es
//

#include <SDL.h>

int main (int , char ** )
{
    // Se hace inicializa el subsistema de vídeo de SDL:

    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        SDL_Log ("Error initializing SDL2.");
    }
    else
    {
        // Se crea una ventana:

        SDL_Window * window = SDL_CreateWindow
        (
            "SDL2 window example", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            800, 
            600, 
            SDL_WINDOW_SHOWN
        );

        if (not window)
        {
            SDL_Log ("Error creating the window.");
        }
        else
        {
            // Se toma el buffer de la ventana para dibujar en él:

            SDL_Surface * surface = SDL_GetWindowSurface (window);

            if (not surface)
            {
                SDL_Log ("Error acessing the window surface.");
            }
            else
            {
                bool exit = false;

                do
                {
                    // Se procesan los eventos acumulados:

                    SDL_Event event;

                    while (SDL_PollEvent (&event) > 0)
                    {
                        if (event.type == SDL_QUIT)
                        {
                            exit = true;
                        }
                    }

                    // Se rellena el fondo de la ventana de color gris:

                    static int8_t counter = 0;

                    uint8_t intensity = counter++ > 0 ? 200 - counter : 200 + counter;

                    SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, intensity, intensity, intensity));

                    SDL_UpdateWindowSurface (window);

                    SDL_Delay (10);
                }
                while (not exit);
            }

            SDL_DestroyWindow (window);
        }

        SDL_Quit ();
    }

    return 0;
}
