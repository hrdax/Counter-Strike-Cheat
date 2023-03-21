/*You can find the .exe and more here
Github Repositry: https://github.com/hrdax/Counter-Strike-Cheat 
Thanks for your interest on learning from my code*/
#include <iostream>
#include <Windows.h>
#include <psapi.h>

//menu
void opciones()
{
    std::cout << "\n1.Enable wallcheat / Activar wallcheat\n"
        "2.Disable wallcheat / Desactivar wallcheat\n"
        "3.Enable traced models / Activar modelos trazados\n"
        "4.Disable traced models / Desactivar modelos trazado\n"
        "5.Bug all weas / Bugear toda la weaxd\n"
        "6.Debug / Desbugear xd\n"
        "7.Quit / Salir\n";
}



int main()
{
    //direcciones de memoria a modificar
    int WallsTexturesGLDepth = 0x0; /* I'm not going to upload this because you have to learn
                                    how to manage system memory processes on your own sorry! I know that if you want to learn you will know how to*/
                                    
    int ModelsTexturesGLVERTEX = 0x0; /*No voy a subir esto porque tienes que aprender a administrar los procesos de memoria del sistema por tu cuenta
                                            perdon pero, sé que si quieres aprender lo podras hacer.*/
    int WallsTexturesGLVERTEX = 0x0;
    int count = 0;
    // guarda la info del proceso
    PROCESS_INFORMATION proceso;
    // hace una limpieza para evitar valores basura
    ZeroMemory(&proceso, sizeof(PROCESS_INFORMATION));
    // almacenara la cantidad de bytes escritos
    SIZE_T byteWritten = NULL;
    bool juego = true;
    
    
    while (juego)
    {
        if (count <= 3)
        {
            count++;
        }

        // Nombre dek proceso
        const wchar_t* nombre_proceso = L"hl";
        // Obteniene una lista de ids de procesos
        DWORD IdsP[1024], bytes_retornados;
        // en caso de error imprime lo que paso
        if (!EnumProcesses(IdsP, sizeof(IdsP), &bytes_retornados))
        {
            std::cout << "Error al llamar a EnumProcesses" << std::endl;
            return 1;
        }
        // Calcula cuantos procesos hay
        DWORD cant_procesos = bytes_retornados / sizeof(DWORD);

        for (DWORD i = 0; i < cant_procesos; i++)
        {
            // Abre el proceso
            HANDLE hProceso = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, IdsP[i]);
            if (hProceso != NULL)
            {
                // Obteniene el nombre del proceso
                wchar_t nombre_arch_proceso[MAX_PATH];
                if (GetProcessImageFileName(hProceso, nombre_arch_proceso, MAX_PATH) > 0)
                {
                    // Compara el nombre del proceso con el nombre buscado
                    if (wcsstr(nombre_arch_proceso, nombre_proceso) != NULL)
                    {
                        juego = false;
                        std::cout << "\nOpenGL Cheat pal counter by hrdax\n";
                        std::cout << "\nV 1.0 testing wall\n";
                        // Obtiene el handle del proceso y lo guarda en proceso.hProceso
                        proceso.hProcess = hProceso;
                        break;
                    }
                }
                
            }
        }
        if (count == 3)
        {
            std::cout << "\nOe ya po no tengo todo el dia, tengo cosas que chitear -.-\n" << std::endl;
        }
        else if (count == 1)
        {
            std::cout << "\n[*] Launch the game\n[*] Abre el juego\n" <<
               "\nEsperando que lo abras... ;...;\n"
                "\n[*] If you are not seeing and you did open the game maybe you just need to type something here\n"
                "\n[*] Si no te carga nada y ya abriste el juego tal vez deberias apretar una tecla\n";
            Sleep(7000);
        }
}

    bool salir = true;
    
    do
    {

        opciones();
        std::cout << "Opcion:";
        std::string opcion;
        std::cin >> opcion;

        if (opcion == "1")
        {
            byte bufferwall = 7;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)WallsTexturesGLDepth,
                &bufferwall,
                1,
                &byteWritten);
            std::cout << "\n[+] Wall On / Prendido\n";
        }
        else if (opcion == "2")
        {
            byte bufferwall = 3;
            WriteProcessMemory(proceso.hProcess, (LPVOID)WallsTexturesGLDepth, &bufferwall, 1, &byteWritten);
            std::cout << "\n[-] Wall Off / Apagado\n";
        }
        else if (opcion == "3")
        {
            byte buffermodel = 2;
            WriteProcessMemory(proceso.hProcess, (LPVOID)ModelsTexturesGLVERTEX, &buffermodel, 1, &byteWritten);
            std::cout << "\n[+] Models/os trazados On / Prendido\n";
        }
        else if (opcion == "4")
        {
            byte buffermodel = 5;
            WriteProcessMemory(proceso.hProcess, (LPVOID)ModelsTexturesGLVERTEX, &buffermodel, 1, &byteWritten);
            std::cout << "\n[-] Models/os destrazados Off / Apagado\n";
        }
        else if (opcion == "5")
        {
            byte bufferwallvertice = 2;
            WriteProcessMemory(proceso.hProcess, (LPVOID)WallsTexturesGLVERTEX, &bufferwallvertice, 1, &byteWritten);
            std::cout << "\n[+] All weas are bugged xd/ Se bugeo toda la wea xd\n";
        }
        else if (opcion == "6")
        {
            byte bufferwallvertice = 9;
            WriteProcessMemory(proceso.hProcess, (LPVOID)WallsTexturesGLVERTEX, &bufferwallvertice, 1, &byteWritten);
            std::cout << "\n[-] Debuged / Se desbugeo\n";
        }
        else if (opcion == "7")
        {
            std::cout << "[*] Quitting..\nSaliendo..";
            Sleep(100);
            salir = false;
        }
    } while (salir);
}
