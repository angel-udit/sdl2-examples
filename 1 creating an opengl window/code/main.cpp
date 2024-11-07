//
// Este código es de dominio público
// angel.rodriguez@udit.es
//

#include <SDL.h>
#include <SDL_opengl.h>

int main (int , char * [])
{
    constexpr int window_width  = 1024;
    constexpr int window_height =  576;

    // Se hace inicializa SDL:

    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        SDL_Log ("Error initializing SDL2.");
    }
    else
    {
        // Se preconfigura el contexto de OpenGL:

        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER,          1);

        // Se crea la ventana activando el soporte para OpenGL:

        SDL_Window * window = SDL_CreateWindow
        (
           "SDL2 OpenGL Window Example",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if (not window)
        {
            SDL_Log ("Error creating the window.");
        }
        else
        {
            // Se toma el buffer de la ventana para dibujar en él:

            SDL_GLContext gl_context = SDL_GL_CreateContext (window);

            if (not gl_context)
            {
                SDL_Log ("Error creating the OpenGL context.");
            }
            else
            {
                // Se activa la sincronización vertical con el display:

                SDL_GL_SetSwapInterval (1);

                // ALERTA: se usa OpenGL clásico solo porque el código es mucho más compacto:

                glMatrixMode   (GL_PROJECTION);
                glLoadIdentity ();
                glOrtho        (0, GLdouble(window_width), 0, GLdouble(window_height), +1, -1);
                glViewport     (0, 0, window_width, window_height);
                glMatrixMode   (GL_MODELVIEW);

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

                    // Se borra la ventana (buffer oculto) para luego dibujar un triángulo:

                    glClear (GL_COLOR_BUFFER_BIT);

                    // ALERTA: se usa OpenGL clásico solo porque el código es mucho más compacto:

                    glLoadIdentity ();
                    glTranslatef   (512.f, 300.f, 0.f);

                    glBegin (GL_TRIANGLES);
                    {
                        glColor3f  (   1.f,    0.f, 0.f);
                        glVertex3f (-200.f, -200.f, 0.f);
                        glColor3f  (   0.f,    1.f, 0.f);
                        glVertex3f (+200.f, -200.f, 0.f);
                        glColor3f  (   0.f,    0.f, 1.f);
                        glVertex3f (   0.f,  200.f, 0.f);
                    }
                    glEnd ();

                    // Se actualiza el contenido de la ventana:

                    SDL_GL_SwapWindow (window);
                }
                while (not exit);

                SDL_GL_DeleteContext (gl_context);
            }

            SDL_DestroyWindow (window);
        }

        SDL_Quit ();
    }

    return 0;
}
