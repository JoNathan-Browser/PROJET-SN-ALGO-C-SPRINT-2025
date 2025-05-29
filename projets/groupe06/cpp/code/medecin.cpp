#include "medecin.hpp"
#include "includes.hpp"
#include "patient.hpp" //c'est donc a partir d'ici que le compilateur va prendre les informations pour ma methode




medecin::medecin(std::string nom_medecin)
{
    this->nom=nom_medecin;
}


void medecin::envoyer_rappel(patient& p,std::string message)
{
    if(message.empty())
    {
        auto a=p.dossier_medical.size()-1; //avoir la dernière consultation pour le message par defaut
        message="Cher client nous vous prions d'honorer votre prochain rendez-vous dans notre etablissement a la date du "+ std::get<feuille_medicale>(p.dossier_medical[a]).date_heure;
        //envoyer un message par defaut si le personnel n'as pas de chose a dire 
    }
    p.rappels.push(message); //placer le message dans la pile des rappels du patient
}





void medecin::consulter_dossier_patient(patient& p)
{
    if(!p.dossier_medical.empty()){p.consulter_dossier_patient();}
}



void medecin::consulter_dossier_patient(std::string matricule="")
{
    std::string chemin = R"(C:\Users\Raoul\Desktop\c++_project\patients\)" + matricule +".txt";
    std::ifstream f{chemin}; 
    if(f.is_open())
    {
        std::string ligne;
        while (std::getline(f, ligne)) 
        {
            std::cout << ligne << std::endl;  // afficher la ligne
        }
    }
    f.close();//pas besoin de fermer le fichier mais ca derange pas
}









void medecin::poser_diagnostique(patient& p,std::string diagnos,double facture)
{
    feuille_medicale f{this->nom,p.definir_date(),diagnos,facture};
    p.dossier_medical.push_back(f);
    p.facture=p.facture+facture;
}


void medecin::poser_diagnostique(std::vector<std::variant<std::string, int , char ,feuille_medicale>> dossier_medical , patient& p)
{
    p.dossier_medical=dossier_medical;  //aller redefinir ca dans persinnel admministratif
}

//commenter avec ctrl+k+C
