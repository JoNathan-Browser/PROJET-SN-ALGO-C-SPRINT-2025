#include "includes.hpp"
#include "fichier.hpp"
#include "includes.hpp"
#include "patient.hpp"
#include "medecin.hpp"
#include "personnel_administratif.hpp"
#include "fichier.hpp"
#include <array>
#include <iterator> 
    


limit limit_presentation1{44,106,1,6}; 
limit limit_presentation2{44,106,9,15};
limit limit_presentation3{44,106,19,24};
limit limit_presentation4{44,106,27,33};
limit limit_patient1{45,101,1,5}; 
limit limit_patient2{45,101,8,12};
limit limit_patient3{45,101,15,19};
limit limit_patient4{45,101,22,25};

limit limit_patient5{40,70,29,32};
limit limit_patient6{80,110,28,30};

limit limit_retour{40,69,15,18};
limit limit_quiter{82,111,15,18};



std::vector<limit> LIMIT_presentation{limit_presentation1, limit_presentation2, limit_presentation3, limit_presentation4};

std::vector<limit> LIMIT_patient{limit_patient1, limit_patient2 , limit_patient3, limit_patient4 ,limit_patient5,limit_patient6};

std::vector <limit> LIMIT = LIMIT_presentation;


std::list<patient> liste_patient; //liste des patients 

 




void effacer_ecran() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// On récupère un handle (identifiant) vers la console de sortie standard (celle qu'on voit à l'écran).
    CONSOLE_SCREEN_BUFFER_INFO csbi; //Variable qui va contenir les infos sur la taille et l’état actuel du buffer console.
    DWORD written; //savoir combien de caractères on a effacés/écrits,
    DWORD cells; //nombre total de caractères à effacer (largeur × hauteur).

    GetConsoleScreenBufferInfo(hConsole, &csbi); // Remplit csbi avec des infos sur la taille de la console, la position du curseur, etc.
    cells = csbi.dwSize.X * csbi.dwSize.Y; //Calcule le nombre total de "cellules" (caractères affichables) dans la console.

    FillConsoleOutputCharacter(hConsole, ' ', cells, {0, 0}, &written); //Remplit toute la console avec des espaces (' ') à partir du coin haut gauche (0, 0).
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, {0, 0}, &written); //Remet les couleurs d'origine dans toute la console.
    SetConsoleCursorPosition(hConsole, {0, 0}); // Replace le curseur en haut à gauche après avoir effacé.
}




void presentation()
{
    effacer_ecran();
    std::cout<<"                                            ###############################################################"<<std::endl;
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##            Se connecter en tant que patient               ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ###############################################################"<<std::endl;

    std::cout<<"                                            \n\n";

    std::cout<<"                                            ###############################################################"<<std::endl;
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##           Se connecter en tant que medecin                ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ###############################################################"<<std::endl;

    std::cout<<"                                            \n\n";

    std::cout<<"                                            ###############################################################"<<std::endl;
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##     Se connecter en tant que personnel administratif      ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ###############################################################"<<std::endl;

    std::cout<<"                                            \n\n";

    std::cout<<"                                            ###############################################################"<<std::endl;
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ##                         Quitter                           ##"<<std::endl; 
    std::cout<<"                                            ##                                                           ##"<<std::endl; 
    std::cout<<"                                            ###############################################################"<<std::endl;

    
}





patient charger_patient_depuis_fichier(const std::string& matricule_patient) {
    std::string chemin = R"(.\patients\)" + matricule_patient + ".txt";
    std::ifstream file(chemin);

    patient p{};
    p.matricule_patient = matricule_patient;

    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier.\n";
        return p;
    }

    std::string ligne;
    std::getline(file, ligne);  // ligne contenant nom, age et sexe

    // Récupération des champs
    std::string nom_patient = ligne.substr(ligne.find(":") + 1, ligne.find(" age:") - ligne.find(":") - 1);
    size_t pos_age = ligne.find("age:") + 5;
    size_t pos_sexe = ligne.find("sexe:");
    int age = std::stoi(ligne.substr(pos_age, pos_sexe - pos_age - 1));
    char sexe = ligne[pos_sexe + 6];  // attention à l'espace, vérifie s'il y a un espace en trop

    // Dossier médical de base
    std::vector<std::variant<std::string, int , char ,feuille_medicale>> dossier_medical;
    dossier_medical.push_back(nom_patient);
    dossier_medical.push_back(age);
    dossier_medical.push_back(sexe);

    feuille_medicale fm;
    bool dans_rappels = false;

    while (std::getline(file, ligne)) {
        if (ligne.find("CONSULTATION NUMERO") != std::string::npos) {
            // On lit les 4 lignes suivantes
            std::getline(file, ligne);
            fm.nom_medecin = ligne.substr(ligne.find(":") + 2);

            std::getline(file, ligne);
            fm.date_heure = ligne.substr(ligne.find(":") + 2);

            std::getline(file, ligne);
            fm.diagnostique = ligne.substr(ligne.find(":") + 2);

            std::getline(file, ligne);
            fm.facture = std::stoi(ligne.substr(ligne.find(":") + 2));

            dossier_medical.push_back(fm);

        } else if (ligne.find("vos rappels:") != std::string::npos) {
            dans_rappels = true;
        } else if (dans_rappels && ligne.find("             ") == 0) {
            p.rappels.push(ligne.substr(13));  // retirer l'indentation
        }
        else if (ligne.find("Facture a payer en tout:") != std::string::npos) 
        {
            double facture_finale = std::stof(ligne.substr(ligne.find(":") + 2));
            p.definir_facture(facture_finale); // à condition d’avoir une méthode pour ça
        }

    }

    // Une fois tout lu, on ajoute le dossier médical au patient
    medecin m{"alain"}; // ou un médecin par défaut si besoin
    m.poser_diagnostique(dossier_medical, p);

    file.close();
    liste_patient.push_back(p); //charger le patient dans la liste de patient 
    return p;
}







void interface_patient1()
{

    std::cout<<"\n";
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                 Consulter mes rappels                 ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;

    std::cout<<"\n\n";

    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                 Consulter ma facture                  ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;

    std::cout<<"\n\n";

    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                  Supprimer des rappels                ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
    
    std::cout<<"\n\n";

    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##            Consulter mon dossier medical              ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
    
    std::cout<<"\n\n";

    std::cout<<"                                       ################################          ################################"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ##           Retour           ##          ##             EXIT           ##"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ################################          ################################"<<std::endl;


}

void interface_patient()
{
    bool quitter = false;
    int i=0;
    size_t index;
    std::string matricule;
    patient p;
    std::list<patient>listspeudo=liste_patient;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode_original;
    GetConsoleMode(hIn, &mode_original);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input;
    DWORD count;

    effacer_ecran();
    if(liste_patient.empty())
    {
        SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        std::cout << "Entrez votre matricule cher patient : "; 

        std::getline(std::cin, matricule);
        
        if (matricule.empty()) {
            return;
        }
        p=charger_patient_depuis_fichier(matricule);
        
        if(p.get_dossier_medical().empty())
        {
            std::cout<<"le patient n'existe pas \n";
            system("pause");
            return;
        }
    }
    else{
        SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        while(!listspeudo.empty())
        {
            std::cout<<"indice ["<<i<<"] --->"<<listspeudo.front().matricule_patient<<" " <<"\n";
            i+=1;
            listspeudo.pop_front();
        }
        std::cout << "Entrez l'indice de votre matricule cher patient: ";
        std::cin>>index;
        std::cin.ignore();
        if(index>=liste_patient.size())
        {
            std::cout<<"indice incorrect ";
            system("pause");
            return;
        }
        p=retrouve(index); 
    }

    while (!quitter) {
        effacer_ecran();
        interface_patient1(); // Affiche le menu UNE FOIS à chaque boucle
        // Réactiver la gestion souris AVANT d'attendre un clic
        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);


        // Attente d'un clic souris
        while (true) {
            ReadConsoleInput(hIn, &input, 1, &count);
            if (input.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;

                if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    int action;
                    for (size_t j = 0; j < LIMIT_patient.size(); ++j) {
                        limit l = LIMIT_patient[j];
                        if (l.limit_X_debut <= mer.dwMousePosition.X && mer.dwMousePosition.X <= l.limit_X_fin &&
                            l.limit_Y_debut <= mer.dwMousePosition.Y && mer.dwMousePosition.Y <= l.limit_Y_fin) {
                            action= (int)j + 1;
                        }
                    }

                    if (action == 0) break; // clic hors zone
                    switch (action) {
                        case 1:
                            interface_consulter_rappels(p);
                            system("pause");
                        break;

                        case 2:
                            std::cout<<"Votre facture est de : " <<p.consulter_facture() <<std::endl;
                            system("pause");
                        break;

                        case 3:
                            p.supprimer_rappel();
                            mettre_a_position(p,index);
                            system("pause");
                        break;

                        case 4:
                            p.consulter_dossier_patient();
                            system("pause");
                        break;

                        case 5:
                            quitter = true;
                            effacer_ecran();
                            break;
                            return;
                        break;
                        case 6:
                            exit(-1);
                        break;
                    }
                    break; // pour sortir de la boucle d'attente clic et redessiner
                }
            }
        }
    }

    SetConsoleMode(hIn, mode_original); // restaurer mode original à la fin
   
}
   




void interface_consulter_rappels(patient p)
{
    if(p.rappels.empty())
    {
        std::cout<<"vous n'avez pas de rappels   "<<std::endl;
    }
    else{
        std::stack rapples{p.rappels};
        while ((!rapples.empty()))
        {
            std::cout<<rapples.top();
            rapples.pop();
        }
        
    }

}








void interface_medecin1()
{
    std::cout<<"\n";
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##               Consulter le dossier du patient         ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;

    std::cout<<"\n\n";

    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                Poser un diagnostique                  ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;

    std::cout<<"\n\n";

    std::cout<<"                                       ################################          ################################"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ##           Retour           ##          ##            QUITTER         ##"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ################################          ################################"<<std::endl;

}





patient retrouve(size_t index)
{
    int i{0};
    std::list<patient>tmp{liste_patient};
    while(!tmp.empty() && i!=(int)index)
    {
        tmp.pop_front();
        i++;
    }
    return tmp.front();
}




void mettre_a_position(patient p, size_t index)
{
    if (liste_patient.empty()) return;

    // Supprimer le patient existant (même matricule)
    for (auto it = liste_patient.begin(); it != liste_patient.end(); ++it)
    {
        if (it->matricule_patient == p.matricule_patient)
        {
            liste_patient.erase(it);
            break;
        }
    }

    if (index == 0)
    {
        // Insertion en tête
        liste_patient.push_front(p);
    }
    else
    {
        // Insertion à l’index donné (remplacement logique)
        auto it = liste_patient.begin();
        std::advance(it, index - 1); // on se place avant la position cible
        liste_patient.insert(++it, p); // insert après => écrase la place précédente
    }
}








void interface_medecin(std::string name)
{
    using namespace std;
    medecin mede{name};
    patient p;
    string matricule;
    list<patient> listspeudo{liste_patient};
    int i{0};
    double facture;
    size_t index;
    vector<limit> tmp{limit_patient1,limit_patient2,limit_retour,limit_quiter};
    std::string diagnos;


    

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode_original;
    GetConsoleMode(hIn, &mode_original);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input;
    DWORD count;
    bool quitter = false;


    effacer_ecran();
    if(liste_patient.empty())
    {
        std::cout << "Entrer le matricule du patient a consulter : "; 
        SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        std::getline(std::cin, matricule);
        if (matricule.empty()) {
            return;
        }
        p=charger_patient_depuis_fichier(matricule);
        
        //liste_patient.push_back(p);

        if(p.get_dossier_medical().empty())
        {
            std::cout<<"le patient n'existe pas \n";
            system("pause");
            return;
        }
    }
    else{
        SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        while(!listspeudo.empty())
        {
            std::cout<<"indice ["<<i<<"] --->"<<listspeudo.front().matricule_patient<<" " <<"\n";
            i+=1;
            listspeudo.pop_front();
        }
        std::cout << "Entrer l'indice du patient a consulter dans la liste de patient: ";
        std::cin>>index;
        std::cin.ignore();
        if(index>=liste_patient.size())
        {
            std::cout<<"indice incorrect ";
            system("pause");
            return;
        }
        p=retrouve(index); 
    }
                            

    //SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    while (!quitter) {
        effacer_ecran();
        interface_medecin1(); // Affiche le menu UNE FOIS à chaque boucle
        // Réactiver la gestion souris AVANT d'attendre un clic
        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);


        // Attente d'un clic souris
        while (true) {
            ReadConsoleInput(hIn, &input, 1, &count);
            if (input.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;

                if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    int action;
                    for (size_t j = 0; j < tmp.size(); ++j) {
                        limit l = tmp[j];
                        if (l.limit_X_debut <= mer.dwMousePosition.X && mer.dwMousePosition.X <= l.limit_X_fin &&
                            l.limit_Y_debut <= mer.dwMousePosition.Y && mer.dwMousePosition.Y <= l.limit_Y_fin) {
                            action= (int)j + 1;
                        }
                    }

                    if (action == 0) break; // clic hors zone
                    switch (action) {
                        case 1:
                           p.consulter_dossier_patient();
                           system("pause");
                        break;
                        
                        case 2:
                            effacer_ecran();
                            std::cout << "Vous voulez poser un diagnostique sur ce patient veuillez entrer le diagnostique : \n    ";

                            SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            cin.ignore();
                            std::getline(std::cin, diagnos);
                            std::cout<<"entrer la facture de la consultation : ";
                            std::cin>>facture;
                            mede.poser_diagnostique(p,diagnos,facture);
                            mettre_a_position(p,index);
                            std::cout<<"\n\n              Veuillez ne pas oublier de sauvegarder les données chez le personnel administratif sinon elle seront perdues  ";
                            system("pause");

                        break;

                        case 3:
                            quitter = true;
                            effacer_ecran();
                            break;
                            return;
                        break;

                        case 4:
                            std::cout<<" ~VOUS VENEZ DE QUITTER LE PROGRAMME DE FORCE Les donnes non suavegardee seront perdues~";
                            exit(-1);
                        break;

                        default:break;
                    }
                    break; // pour sortir de la boucle d'attente clic et redessiner
                }
            }
        }
    }

    SetConsoleMode(hIn, mode_original);
}







int detecter_interface(MOUSE_EVENT_RECORD mer) {
    for (size_t i = 0; i < LIMIT.size(); ++i) {
        limit l = LIMIT[i];
        if (l.limit_X_debut <= mer.dwMousePosition.X && mer.dwMousePosition.X <= l.limit_X_fin &&
            l.limit_Y_debut <= mer.dwMousePosition.Y && mer.dwMousePosition.Y <= l.limit_Y_fin) {
            return (int)i + 1;
        }
    }
    return 0;
}


void dessiner_menu()
{
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                enregistrer un patient                 ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
            
    std::cout<<"\n\n";
            
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##              envoyer un rappel a un patient           ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
            
    std::cout<<"\n\n";
            
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##         marquer une facture comme payee               ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
            
    std::cout<<"\n\n";
            
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##          sauvegarder les donnees des patients         ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
            
    std::cout<<"\n\n";
            
    std::cout<<"                                            ###########################################################"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ##                planifier un rendez-vous               ##"<<std::endl;
    std::cout<<"                                            ##                                                       ##"<<std::endl;
    std::cout<<"                                            ###########################################################"<<std::endl;
            
    std::cout<<"\n\n";
            
    std::cout<<"                                       ################################          ################################"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ##           Retour           ##          ##           QUITTER          ##"<<std::endl;
    std::cout<<"                                       ##                            ##          ##                            ##"<<std::endl;
    std::cout<<"                                       ################################          ################################"<<std::endl;
}




void afficher_liste_patients()
{
    std::list<patient>listspeudo{liste_patient};
    int i{0};
    while(!listspeudo.empty())
    {
        std::cout<<"indice ["<<i<<"] --->"<<listspeudo.front().matricule_patient<<" :" <<listspeudo.front().get_nom_patient()<<"\n";
        i+=1;
        listspeudo.pop_front();
    }
}



void interface_personnel_administratif()
{
    using namespace std;
    size_t index;
    std::string nom_patient, etat_sante,message;
    int age_patient;
    double montant;
    char sexe_patient;
    patient p;
    personnel_administratif perr{"alain"};
    std::list<patient>tmp=liste_patient;
    
    limit l1{45,101,28,32};
    limit l2{40,69,35,39};
    limit l3{82,111,35,39};
    std::vector<limit>limit_personnel={limit_patient1,limit_patient2,limit_patient3,limit_patient4,l1,l2,l3};


    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode_original;
    GetConsoleMode(hIn, &mode_original);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input;
    DWORD count;
    bool quitter = false;

    while (!quitter) {
        effacer_ecran();
        dessiner_menu(); // Affiche le menu UNE FOIS à chaque boucle
        // Réactiver la gestion souris AVANT d'attendre un clic
        SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);


        // Attente d'un clic souris
        while (true) {
            ReadConsoleInput(hIn, &input, 1, &count);
            if (input.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;

                if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    int action;
                    for (size_t i = 0; i < limit_personnel.size(); ++i) {
                        limit l = limit_personnel[i];
                        if (l.limit_X_debut <= mer.dwMousePosition.X && mer.dwMousePosition.X <= l.limit_X_fin &&
                            l.limit_Y_debut <= mer.dwMousePosition.Y && mer.dwMousePosition.Y <= l.limit_Y_fin) {
                            action= (int)i + 1;
                        }
                    }

                    if (action == 0) break; // clic hors zone
                    switch (action) {
                        case 1:
                            SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            effacer_ecran();
                            cout << "Enregistrement d'un patient entrer son nom\n";
                            std::getline(std::cin,nom_patient);
                            cout << "Age : "; cin >> age_patient;
                            cout << "Sexe : "; cin >> sexe_patient;
                            std::cin.ignore();
                            cout << "Antecedents : "; getline(cin, etat_sante);

                            p = patient{nom_patient, age_patient, sexe_patient, "", etat_sante};
                            perr.enregistrer_patient(p, liste_patient);
                            cout << "Patient enregistre   ";

                            SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
                            system("pause");
                        break;

                        case 2:
                            SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            effacer_ecran();
                            if(liste_patient.empty()){std::cout<<"vous devez enregistrer un patient d'abord "; system("pause"); break;}

                            afficher_liste_patients();

                            std::cout << "Entrer l'indice du patient a qui envoyer le rappel: ";
                            std::cin>>index;
                            std::cin.ignore();
                            if(index>=liste_patient.size())
                            {
                                std::cout<<"indice incorrect ";
                                system("pause");
                                break;
                            }

                            p=retrouve(index);
                            std::cout<<"Si vous avez un message pour le rappel entrer le sinon un message par defaut est utilise:\n";
                            std::getline(std::cin,message);
                            perr.envoyer_rappel(p,message);
                            mettre_a_position(p,index); //les modifications ont ete faites sur p pas sur ca valeur dans le tableau donc le replacer dans le tableau apres modifications
                            std::cout<<"Le rappel a bien ete envoyé  ";
                            system("pause");
                        break;

                        case 3:
                            SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            effacer_ecran();
                            if(liste_patient.empty()){break;}

                            afficher_liste_patients();

                            std::cout << "Entrer l'indice du patient dont vous voulez payer la facture: ";
                            std::cin>>index;
                            if(index>=liste_patient.size())
                            {
                                std::cout<<"indice incorrect ";
                                system("pause");
                                break;
                            }

                            p=retrouve(index);
                            std::cout<<"La facture du client "<<p.get_nom_patient()<<" "<<p.consulter_facture()<<std::endl;
                            std::cout<<"Entrer le montant de la somme a payer:\n";
                            cin>>montant;
                            p.payer_facture(montant);
                            mettre_a_position(p,index);
                            std::cout<<"facture payée avec success  ";
                            std::cin.ignore();
                            system("pause");
                        break;

                        case 4:
                            if(liste_patient.empty()){break;}
                            for (auto m : liste_patient)
                            {
                                perr.sauvegarder_donne_patient(m);
                            }
                            afficher_progression();
                            cout << "Donnees sauvegardees.      ";
                            system("pause");
                        break;

                        case 5:
                           //planifier un rendez vous consiste a modifier la liste de patient et de mettre les patient qui ont des rendez vous en tete de la liste afin que le medecin les consultes dans l'ordre s'il y'a pas de rdv le medecin le fera au comme il veut
                           SetConsoleMode(hIn, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
                            effacer_ecran();
                            if(liste_patient.empty()){std::cout<<"vous devez enregistrer un patient d'abord "; system("pause"); break;}

                            afficher_liste_patients();

                            std::cout << "Entrer l'indice du patient qui veut programmer un rendez-vous: ";
                            std::cin>>index;
                            std::cin.ignore();
                            if(index>=liste_patient.size())
                            {
                                std::cout<<"indice incorrect ";
                                system("pause");
                                break;
                            }

                            mettre_a_position(p,0); //mettre les patients qui veulent un rdv en tete de la liste des patients 
                            std::cout<<"Le rendez-vous a ete programme :";
                            system("pause");
                        break;
                        case 6:
                            quitter = true;
                            effacer_ecran();
                            return;
                        break;
                        case 7:
                            std::cout<<"VOUS VENEZ DE QUITTER LE PROGRAMME PAR FORCE LES DONNES NON SAUVEGARDEES ONT ETE PERDUES";
                            exit(-1);
                        break;
                    }
                    break; // pour sortir de la boucle d'attente clic et redessiner
                }
            }
        }
    }

    SetConsoleMode(hIn, mode_original); // restaurer mode original à la fin
}







void interface_Quitter()
{

    std::cout<<"FIN DU PROGRAMME NOUS VOUS SOUHAITONS UNE BONNE CONTINUATION";
}





void afficher_progression() {
    effacer_ecran();
    std::cout<<"\n\n\n       ";
    for (int i = 0; i <= 100; ++i) {
        std::cout << "\r            Sauvegarde en cours: " << i << "%            " << std::flush; // le \r pour afficher sur la meme ligne ecraser a chaque fois
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // pause pour voir la progression
    }
    std::cout << "   "; 
}


