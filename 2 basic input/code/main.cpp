//
// Este código es de dominio público
// angel.rodriguez@udit.es
//

#include <SDL.h>

int main (int , char * [])
{
    // Se hace inicializa SDL:

    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        SDL_Log ("Error initializing SDL2.");
    }
    else
    {
        // Se crea la ventana:

        SDL_Window * window = SDL_CreateWindow
        (
            "SDL2 basic input example", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            1024, 
            576, 
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
                SDL_Log ("Error accessing the window surface.");
            }
            else
            {
                bool exit = false;

                // Se rellena el fondo de la ventana de color gris:

                SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, 225, 225, 225));

                do
                {
                    // Se procesan los eventos acumulados desde el fotograma anterior:

                    SDL_Event event;

                    while (SDL_PollEvent (&event) > 0)
                    {
                        switch (event.type)
                        {
                            case SDL_KEYDOWN:
                            {
                                // Si se pulsan ciertas teclas se borra el contenido de la ventana:

                                switch (event.key.keysym.sym)
                                {
                                    case SDLK_SPACE:
                                    case SDLK_ESCAPE:
                                    case SDLK_RETURN:
                                    case SDLK_KP_ENTER:
                                    {
                                        SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, 225, 225, 225));
                                    }
                                }

                                break;
                            }

                            case SDL_MOUSEBUTTONDOWN:
                            case SDL_MOUSEMOTION:
                            {
                                // Si se mueve el ratón mientras se mantiene presionado alguno de sus tres
                                // botones principales se dibuja un pequeño rectángulo de color:

                                int mouse_x = 0, mouse_y = 0;

                                uint32_t buttons = SDL_GetMouseState (&mouse_x, &mouse_y);

                                uint8_t  left    = buttons & SDL_BUTTON(SDL_BUTTON_LEFT  ) ? 255 : 0;
                                uint8_t  middle  = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE) ? 255 : 0;
                                uint8_t  right   = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT ) ? 255 : 0;

                                if (left || middle || right)
                                {
                                    SDL_Rect cursor_area = { mouse_x - 1, mouse_y - 1, 3, 3 };

                                    SDL_FillRect (surface, &cursor_area, SDL_MapRGB (surface->format, right, middle, left));
                                }

                                break;
                            }

                            case SDL_QUIT:
                            {
                                exit = true;
                                break;
                            }
                        }
                    }

                    SDL_UpdateWindowSurface (window);
                }
                while (not exit);
            }

            SDL_DestroyWindow (window);
        }

        SDL_Quit ();
    }

    return 0;
}
