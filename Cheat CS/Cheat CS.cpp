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
        "3.Transparent Walls / Murallas Transparentes\n"
        "4.Enable traced models / Activar modelos trazados\n"
        "5.Disable traced models / Desactivar modelos trazado\n"
        "6.Bug all weas / Bugear toda la weaxd\n"
        "7.Debug / Desbugear xd\n"
        "8.Quit / Salir\n";
}

/* I covered with "?" the secrets parts that you have to learn how they work and why they are there and I left some for clues, when you understand how to manage the process memory
this is gonna be very easy, and to understand it isn't very difficult, you need some skills on assembler/debugger programs like ollydbg cheat engine
if you have that you are very close to understand how to complete this code and learn how the wall cheats are made in opengl in this example with
cs 1.6 if you have problems understanding how to create opcodes it's not very complicated it's like creating little-endian the difficulty is that you need
know how to make references to the different functions that exist in assembly language to interact with memory, good luck :) (I suggest to learn some opengl functions)*/

/*  cubrí con "?" las partes secretas que tienes que aprender cómo funcionan y por qué están ahí y dejo algunas como pistas, cuando entiendes cómo administrar la memoria del proceso
esto va a ser muy fácil, y para entenderlo no es muy difícil, necesitas algunas habilidades en programas ensambladores/depuradores como ollydbg cheat engine
si tienes eso estas muy cerca de entender como completar este codigo y aprender como se hacen los trucos de wall en opengl en este ejemplo con
CS 1.6 si tienes problemas entiendiendo como crear opcodes no es muy complicado es como crear little-endian la dificultad es que necesitas 
saber como hacer referencias a las distintas funciones que hay en lenguaje ensamblador para interactuar con la memoria suerte :) (sugiero aprender como funcionan algunas funciones en opengl)*/

int main()
{
    //direcciones de memoria a modificar
    int GlBeginaddss = 0x0; /* I'm not going to upload this because you have to learn
                                    how to manage system memory processes on your own sorry! I know that if you want to learn you will know how to*/

    int GlBeginWalladds = 0x0;

    int ModelsTexturesGLVERTEX = 0x0; /*No voy a subir esto porque tienes que aprender a administrar los procesos de memoria del sistema por tu cuenta
                                            perdon pero, sé que si quieres aprender lo podras hacer.*/
    int WallsTexturesGLVERTEX = 0x0;
    int count = 0;
    // guarda la info del proceso
    PROCESS_INFORMATION proceso;
    // hace una limpieza para evitar valores basura
    ZeroMemory(&proceso, sizeof(PROCESS_INFORMATION));
    // almacenara la cantidad de bytes escritos
    SIZE_T byteWritten = 0;
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

        //prender
        if (opcion == "1")
        {

            int bufglbegin = 0x0;
            unsigned int subroutineAddress1 = 0x01CF707E;
            unsigned char buffer1[] = { 0xE8, 0x00, 0x00, 0x00, 0x00 };
            unsigned int relativeAddress1 = subroutineAddress1 - (bufglbegin + sizeof(buffer1));

            memcpy(buffer1 + 1, &relativeAddress1, sizeof(relativeAddress1));
            if (!WriteProcessMemory(proceso.hProcess, (LPVOID)bufglbegin, buffer1, sizeof(buffer1), &byteWritten)) { //CALL xxxxx..
                std::cerr << "Couldn't write process memory: " << GetLastError() << std::endl;
            }

            int bufferLength = sizeof(buffer1);

            unsigned char nop[] = { 0x90 }; //NOP
            int bgbufmemoria2 = 0x01D90D23;
            bufferLength = sizeof(nop);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria2,
                nop,
                bufferLength,
                &byteWritten);

            int bgbufmemoria3 = 0x01D90D24;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria3,
                nop,
                bufferLength,
                &byteWritten);
            int bgbufmemoria4 = 0x01D90D25;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria4,
                nop,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl = 0x01CF707E;
            unsigned char buffer3[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; //PUSH 0B71
            bufferLength = sizeof(buffer3);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl,
                buffer3,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl2 = 0x01CF7083;
            unsigned char buffer4[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // gl disable
            bufferLength = sizeof(buffer4);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl2,
                buffer4,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl3 = 0x01CF7088;
            unsigned char buffer5[] = { 0x6A, 0x05 }; //PUSH 5
            bufferLength = sizeof(buffer5);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl3,
                buffer5,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl4 = 0x01CF708A;
            unsigned char buffer6[] = { 0xFF, 0x15, 0xEC, 0x89, 0x7E, 0x02 }; // CALL DWORD PTR DS:[27E89EC]
            bufferLength = sizeof(buffer6);
            WriteProcessMemory(proceso.hProcess, (LPVOID)funcbufmemoriahl4, buffer6, bufferLength, &byteWritten);

            int funcbufmemoriahl5 = 0x01CF7090;
            unsigned char buffer7[] = { 0x?? }; //RETN
            bufferLength = sizeof(buffer7);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl5,
                buffer7,
                bufferLength,
                &byteWritten);

            int bufglend = 0x01D90E1B;
            unsigned int subroutineAddress = 0x01CF70BB;
            unsigned char buffer8[] = { 0xE8, 0x00, 0x00, 0x00, 0x00 };
            unsigned int relativeAddress = subroutineAddress - (bufglend + sizeof(buffer8));

            memcpy(buffer8 + 1, &relativeAddress, sizeof(relativeAddress));
            if (!WriteProcessMemory(proceso.hProcess, (LPVOID)bufglend, buffer8, sizeof(buffer8), &byteWritten)) //CALL hl.01CF70BB
            {
                std::cerr << "No se pudo escribir en la memoria :| " << GetLastError() << std::endl;
            }

            int bufglendNOP = 0x01D90E20;
            bufferLength = sizeof(nop);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bufglendNOP,
                nop,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl1 = 0x01CF70BB;
            unsigned char buffer9[] = { 0x??, 0x??, 0x??, 0x??, 0x??, 0x?? }; // CALL DWORD PTR DS:[27E81B4]
            bufferLength = sizeof(buffer9);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl1,
                buffer9,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl2 = 0x01CF70C1;
            unsigned char buffer10[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // PUSH 0B71
            bufferLength = sizeof(buffer10);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl2,
                buffer10,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl3 = 0x01CF70C6;
            unsigned char buffer11[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; //CALL opengl32.glEnable
            bufferLength = sizeof(buffer11);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl3,
                buffer11,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl4 = 0x01CF70CB;
            unsigned char buffer12[] = { 0xC3 }; //RETN
            bufferLength = sizeof(buffer12);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl4,
                buffer12,
                bufferLength,
                &byteWritten);

            std::cout << "\n[+] Wall On / Prendido\n";
        }
        //apagar
        else if (opcion == "2")
        {
            int bufglbegin = 0x0; //discover it your self :) | descubrelo tu mismo :)
            unsigned char buff[] = { 0x??, 0x?? }; //PUSH 5
            int bufferLength = sizeof(buff);
            if (!WriteProcessMemory(proceso.hProcess, (LPVOID)bufglbegin, buff, sizeof(buff), &byteWritten)) {
                std::cerr << "Couldn't write process memory: " << GetLastError() << std::endl;
            }


            unsigned char glbeginreturn[] = { 0xFF, 0x15, 0xEC, 0x89, 0x7E, 0x02 }; //CALL DWORD PTR DS:[27E89EC]
            int bgbufmemoria2 = 0x01D90D20;
            bufferLength = sizeof(glbeginreturn);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria2,
                glbeginreturn,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl = 0x01CF707E;
            unsigned char buffer3[] = { 0x00, 0x00 }; // liberar memoria / borrar y dejarla como estaba
            bufferLength = sizeof(buffer3);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl,
                buffer3,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl2 = 0x01CF7083;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl2,
                buffer3,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl3 = 0x01CF7088;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl3,
                buffer3,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl4 = 0x01CF708A;
            WriteProcessMemory(proceso.hProcess, (LPVOID)funcbufmemoriahl4, buffer3, bufferLength, &byteWritten);

            int funcbufmemoriahl5 = 0x01CF7090;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl5,
                buffer3,
                bufferLength,
                &byteWritten);

            int bufglend = 0x01D90E1B;
            unsigned char buffer8[] = { 0xFF, 0x15, 0xB4, 0x81, 0x7E, 0x02 };
            bufferLength = sizeof(buffer8);
            if (!WriteProcessMemory(proceso.hProcess, (LPVOID)bufglend, buffer8, sizeof(buffer8), &byteWritten)) //CALL DWORD PTR DS:[27E81B4]
            {
                std::cerr << "No se pudo escribir en la memoria :| " << GetLastError() << std::endl;
            }

            int funcglendfmemoriahl1 = 0x01CF70BB;
            unsigned char buffer9[] = { 0x00, 0x00 }; //libera la memoria, establece en 0
            bufferLength = sizeof(buffer9);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl1,
                buffer9,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl2 = 0x01CF70C1;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl2,
                buffer9,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl3 = 0x01CF70C6;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl3,
                buffer9,
                bufferLength,
                &byteWritten);

            int funcglendfmemoriahl4 = 0x01CF70CB;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcglendfmemoriahl4,
                buffer9,
                bufferLength,
                &byteWritten);

            std::cout << "\n[-] Wall OFF / Apagado\n";
        }
        //MURALLAS TRANSPARENTES
        else if (opcion == "3")
        {
            int bufglbegin = 0x01D486A7;
            unsigned char buffer1[] = { 0xE8, 0x5C, 0xE9, 0xFA, 0xFF };

            if (!WriteProcessMemory(proceso.hProcess, (LPVOID)bufglbegin, buffer1, sizeof(buffer1), &byteWritten)) { //CALL xxxxx..
                std::cerr << "No pudo escribir en la memoria :| " << GetLastError() << std::endl;
            }

            int bufferLength = sizeof(buffer1);

            unsigned char nop[] = { 0x90 }; //NOP deja un espacio vacio en la memoria
            int bgbufmemoria2 = 0x01D486AC;
            bufferLength = sizeof(nop);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria2,
                nop,
                bufferLength,
                &byteWritten);

            int bgbufmemoria3 = 0x01D486AD;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria3,
                nop,
                bufferLength,
                &byteWritten);

            int bgbufmemoria4 = 0x01D486AE;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria4,
                nop,
                bufferLength,
                &byteWritten);

            int bgbufmemoria5 = 0x01D486AF;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)bgbufmemoria5,
                nop,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl = 0x01CF7008;
            unsigned char buffer3[] = { 0x50 }; //PUSH EAX
            bufferLength = sizeof(buffer3);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl,
                buffer3,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl2 = 0x01CF7009;
            unsigned char buffer4[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // CALL xxxx...
            bufferLength = sizeof(buffer4);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl2,
                buffer4,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl3 = 0x01CF700E;
            unsigned char buffer5[] = { 0x??, 0x??, 0x? }; //ADD ESP,4
            bufferLength = sizeof(buffer5);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl3,
                buffer5,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl4 = 0x01CF7011;
            unsigned char buffer6[] = { 0x?? }; // PUSHAD
            bufferLength = sizeof(buffer6);
            WriteProcessMemory(proceso.hProcess, (LPVOID)funcbufmemoriahl4, buffer6, bufferLength, &byteWritten);

            int funcbufmemoriahl5 = 0x01CF7012;
            unsigned char buffer7[] = { 0x68, 0x03, 0x03, 0x00, 0x00 }; // PUSH 303
            bufferLength = sizeof(buffer7);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl5,
                buffer7,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl6 = 0x01CF7017;
            unsigned char buffer8[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // PUSH 302
            bufferLength = sizeof(buffer8);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl6,
                buffer8,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl7 = 0x01CF701C;
            unsigned char buffer9[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // CALL opengl32.glBlendFunc
            bufferLength = sizeof(buffer9);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl7,
                buffer9,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl8 = 0x01CF7021;
            unsigned char buffer10[] = { 0x68, 0x71, 0x0B, 0x00, 0x00 }; // PUSH 0B71
            bufferLength = sizeof(buffer10);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl8,
                buffer10,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl9 = 0x01CF7026;
            unsigned char buffer11[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // CALL opengl32.glDisable
            bufferLength = sizeof(buffer11);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl9,
                buffer11,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl10 = 0x01CF702B;
            unsigned char buffer12[] = { 0x68, 0xE2, 0x0B, 0x00, 0x00 }; // PUSH 0BE2
            bufferLength = sizeof(buffer12);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl10,
                buffer12,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl11 = 0x01CF7030;
            unsigned char buffer13[] = { 0x??, 0x??, 0x??, 0x??, 0x?? }; // CALL opengl32.glEnable
            bufferLength = sizeof(buffer13);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl11,
                buffer13,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl12 = 0x01CF7035;
            unsigned char buffer14[] = { 0x68, 0x66, 0x66, 0xE6, 0x3E }; // PUSH 3EE66666
            bufferLength = sizeof(buffer14);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl12,
                buffer14,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl13 = 0x01CF703A;
            unsigned char buffer15[] = { 0x68, 0x66, 0x66, 0x66, 0x3F }; // PUSH 3F666666
            bufferLength = sizeof(buffer15);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl13,
                buffer15,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl14 = 0x01CF703F;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl14,
                buffer15,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl15 = 0x01CF7044;
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl15,
                buffer15,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl16 = 0x01CF7049;
            unsigned char buffer16[] = { 0xE8, 0x54, 0x9F, 0xE6, 0x5F }; // CALL opengl32.glColor4f
            bufferLength = sizeof(buffer16);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl16,
                buffer16,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl17 = 0x01CF704E;
            unsigned char buffer17[] = { 0x61 }; // POPAD
            bufferLength = sizeof(buffer17);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl17,
                buffer17,
                bufferLength,
                &byteWritten);

            int funcbufmemoriahl18 = 0x01CF704F;
            unsigned char buffer18[] = { 0xC3 }; // RETN
            bufferLength = sizeof(buffer18);
            WriteProcessMemory(
                proceso.hProcess,
                (LPVOID)funcbufmemoriahl18,
                buffer18,
                bufferLength,
                &byteWritten);
            std::cout << "\n[+] Transparent Walls ON / Murallas Transparentes Activado\n";
        }
        else if (opcion == "4")
        {
            byte buffermodel = 2;
            WriteProcessMemory(proceso.hProcess, (LPVOID)ModelsTexturesGLVERTEX, &buffermodel, 1, &byteWritten);
            std::cout << "\n[+] Models/os trazados On / Prendido\n";
        }
        else if (opcion == "5")
        {
            byte buffermodel = 5;
            WriteProcessMemory(proceso.hProcess, (LPVOID)ModelsTexturesGLVERTEX, &buffermodel, 1, &byteWritten);
            std::cout << "\n[-] Models/os destrazados Off / Apagado\n";
        }
        else if (opcion == "6")
        {
            byte bufferwallvertice = 2;
            WriteProcessMemory(proceso.hProcess, (LPVOID)WallsTexturesGLVERTEX, &bufferwallvertice, 1, &byteWritten);
            std::cout << "\n[+] All weas are bugged xd/ Se bugeo toda la wea xd\n";
        }
        else if (opcion == "7")
        {
            byte bufferwallvertice = 9;
            WriteProcessMemory(proceso.hProcess, (LPVOID)WallsTexturesGLVERTEX, &bufferwallvertice, 1, &byteWritten);
            std::cout << "\n[-] Debuged / Se desbugeo\n";
        }
        else if (opcion == "8")
        {
            std::cout << "[*] Quitting..\nSaliendo..";
            Sleep(100);
            salir = false;
        }

    } while (salir);
}