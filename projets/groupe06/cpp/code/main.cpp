#include "includes.hpp"
#include "patient.hpp"
#include "medecin.hpp"
#include "personnel_administratif.hpp"
#include "fichier.hpp"
#include <array>

using namespace std;



int main()
{
    using namespace std;


    std::string matricule;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode_original;
    GetConsoleMode(hIn, &mode_original);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input;
    DWORD count;
    bool quitter = false;


    while (!quitter) {
        effacer_ecran();
        presentation(); // Affiche le menu UNE FOIS à chaque boucle
        // Réactiver la gestion souris AVANT d'attendre un clic
        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);


        // Attente d'un clic souris
        while (true) {
            ReadConsoleInput(hIn, &input, 1, &count);
            if (input.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;

                if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    int action = detecter_interface(mer);

                    if (action == 0) break; // clic hors zone
                    switch (action) {
                        case 1:
                            interface_patient();
                        break;

                        case 2:
                            effacer_ecran();
                            std::cout << "Bonjour medecin : ";

                            // Remettre le mode standard pour pouvoir faire un std::cin
                            SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            
                            std::cin.ignore();
                            
                            std::getline(std::cin, matricule);
                            if (matricule.empty()) {break;}
                            interface_medecin(matricule);//reutilisation de matricule pour ne pas declarer une autre variable du meme type 
                        break;

                        case 3:
                            interface_personnel_administratif();
                        break;

                        case 4:
                            interface_Quitter();
                            quitter = true;
                        break;
                    }
                    break; // pour sortir de la boucle d'attente clic et redessiner
                }
                if (mer.dwMousePosition.X == 0) break;
            }
        }
    }

    SetConsoleMode(hIn, mode_original); // restaurer mode original à la fin

    CloseHandle(hIn);//libere le handle
    return 0;
}
