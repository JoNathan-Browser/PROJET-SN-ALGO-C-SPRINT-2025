#ifndef patient_H
    #define patient_H
 
    #include "includes.hpp"
    //#include "medecin.hpp" //car medecin est un ami de patient
    class medecin;


    struct feuille_medicale //represente la structure du dossier medical du patient
    {
        std::string nom_medecin;
        std::string date_heure; 
        std::string diagnostique;
        double facture;
    };



    class patient
    {
        friend class medecin; // medecin pourra acceder aux propriete private de patient
        private:
            double facture=0;
            std::vector<std::variant<std::string, int , char ,feuille_medicale>> dossier_medical; //permet de faire un tableau qui peut acceullir un de ces types 
            
        public:
            std::stack<std::string>rappels; // une liste de tous les rappels envoyés par le centre de sante car les rappels peuvent contenir des messages
            std::string matricule_patient;
            patient();
            patient(std::string nom_patient, int age_patient,char sexe_patient ,std::string nom_medecin, std::string etat_sante);
            std::string definir_date();//methode pour rentrer automatiquement la date de consultation
            std::stack<std::string> consulter_rappels(); //<<<<<<<<<<<---------------------------
            void payer_facture(double Facture);
            double consulter_facture();
            void definir_facture(double Facture);
            void definir_matricule();
            std::vector<std::variant<std::string, int , char ,feuille_medicale>>  get_dossier_medical();
            void consulter_dossier_patient();
            std::string get_nom_patient();
            void supprimer_rappel();
    };


#endif