#ifndef personnel_administratif_H
    #define personnel_administratif_H
    class patient;
 
    #include "includes.hpp"
    #include "medecin.hpp"

    class personnel_administratif :public medecin
    {
        private:
        using medecin::poser_diagnostique;
        //pas de overriade puisque ce n'est pas une redefinition identique 

        public:
            personnel_administratif(std::string nom);

            void marquer_facture_paye( patient& p, double facture);

            void sauvegarder_donne_patient(patient p);

            void enregistrer_patient(patient p,std::list<patient>& liste_patients);

            //void planifier_redv(patient& p,std::list<std::string> liste_rdv);
            //envoyer rappel
            //void enregistrer_patient(patient& p,std::list<patient> liste_patients);
            
    };  

#endif