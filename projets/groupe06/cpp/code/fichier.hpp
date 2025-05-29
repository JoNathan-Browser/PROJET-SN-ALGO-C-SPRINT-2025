#ifndef fichier_H
    #define fichier_H
 

    #include "includes.hpp"
    #include "patient.hpp"





    struct limit
    {
        int limit_X_debut;
        int limit_X_fin;
        int limit_Y_debut;
        int limit_Y_fin;
    }; //sera utile pour marquer les zonnes d'action dans cmd nous avons prefere faire une structure pour cela

    /*
      Le principe est d'utiliser les positions des cliques de la souris pour verifier
      dans quelle zonne le clique a ete fais cessi en se mettant des conditions sur les 
      coordonnés en x et en y du point cliqué
    */


    extern limit limit_presentation1; 
    extern limit limit_presentation2;
    extern limit limit_presentation3;
    extern limit limit_presentation4;
    extern limit limit_patient1;
    extern limit limit_patient2;
    extern limit limit_patient3;
    extern limit limit_patient4;
    extern limit limit_patient5;
    extern limit limit_patient6;

    extern limit limit_retour;
    extern limit limit_quiter;

    extern std::vector<limit> LIMIT_presentation;
    extern std::vector<limit> LIMIT_patient;
    extern std::vector <limit> LIMIT; 

    extern std::list<patient> liste_patient;




    void presentation();

    void effacer_ecran();

    void interface_patient();
    void interface_patient1();
    void interface_consulter_rappels(patient p);

    void interface_medecin(std::string matricule);
    void interface_medecin1();
    void mettre_a_position(patient p, size_t index);

    void interface_personnel_administratif();
    patient retrouve(size_t index);
    void afficher_liste_patients();

    patient charger_patient_depuis_fichier(const std::string& matricule_patient); 

    int detecter_interface(MOUSE_EVENT_RECORD mer);
    void dessiner_menu();

    void interface_Quitter();

    void afficher_progression();


#endif
