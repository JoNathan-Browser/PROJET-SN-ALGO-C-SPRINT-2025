#ifndef medecin_H
    #define medecin_H
    
    #include "includes.hpp"
    #include "patient.hpp"
    class patient; // déclaration anticipée 
    /*
      c'est pour eviter d'inclure le fichier qui contient la classe patient(pateint.hpp)
      car ce fichier inclu deja le fichier medecin.hpp(parceque medecin est un amis de lac classe patient) 
      donc in utilise une declaration anticipée pour aller faire des inclusion dans le fichier d'implementation
       des methode qui est le fichier medecin.cpp ici et ainsi eviter les une iinclusion en rond 
    */
   

    class medecin
    {
        public:
            medecin(std::string nom_medecin);
            virtual void poser_diagnostique(patient& p,std::string diagnos,double facture);
            virtual void poser_diagnostique(std::vector<std::variant<std::string, int , char ,feuille_medicale>> dossier_medical , patient& p);
            void envoyer_rappel(patient& p,std::string message);
        
        private:
            void consulter_dossier_patient(patient& p);
            void consulter_dossier_patient(std::string matricule); //surcharger la fonction pour pouvoir lire des donnés dans le fichier du patient directement
            
        protected: //pour que les heritiers de medecin puissent utiliser
            std::string nom;
    };


#endif
